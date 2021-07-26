#include "stdafx.h"
#include "SoundManager.h"
#include "Engine.h"
#include <process.h>
#include <map>

SoundManager::SoundManager()
{
	DirectSoundCreate8(NULL, &dsound_, NULL);

	if (dsound_ != nullptr)
	{
		dsound_->Initialize(NULL);
		dsound_->SetCooperativeLevel(RG2R_WindowM->GetHwnd(), DSSCL_PRIORITY);
	}
}

SoundManager::~SoundManager()
{
	if (dsound_ != nullptr)
		dsound_->Release();
}

SoundResource* SoundManager::Load(const path& filePath)
{
	if (dsound_ != nullptr)
	{
		if (soundSources.find(filePath) == soundSources.end())
		{
			if (filePath.extension() == ".ogg")
			{
				auto soundResource = new SoundResource();
				soundSources.insert(std::pair<const path&, SoundResource*>(filePath, soundResource));
				soundResource->type = ST_Ogg;

				LPDIRECTSOUNDBUFFER pTemp;

				FILE *f;
				fopen_s(&f, filePath.string().c_str(), "rb");

				if (!f) return nullptr;

				ov_open(f, &oggVorbisFile_, NULL, 0);

				vorbis_info *vi = ov_info(&oggVorbisFile_, -1);
				WAVEFORMATEX        wfm;

				memset(&wfm, 0, sizeof(wfm));
				wfm.cbSize = sizeof(wfm);
				wfm.nChannels = vi->channels;
				wfm.wBitsPerSample = 16;
				wfm.nSamplesPerSec = vi->rate;
				wfm.nAvgBytesPerSec = wfm.nSamplesPerSec*wfm.nChannels * 2;
				wfm.nBlockAlign = 2 * wfm.nChannels;
				wfm.wFormatTag = 1;

				DSBUFFERDESC desc;

				desc.dwSize = sizeof(desc);
				desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
				desc.lpwfxFormat = &wfm;
				desc.dwReserved = 0;
				desc.dwBufferBytes = BUFSIZE;

				dsound_->CreateSoundBuffer(&desc, &pTemp, NULL);

				DWORD   size = BUFSIZE;
				DWORD   pos = 0;
				int     sec = 0;
				int     ret = 1;
				char    *buf;
				char    *buf2;

				pTemp->Lock(0, size, (LPVOID*)&buf, &size, NULL, NULL, DSBLOCK_ENTIREBUFFER);

				while (ret && pos < size)
				{
					ret = ov_read(&oggVorbisFile_, buf + pos, size - pos, 0, 2, 1, &sec);
					pos += ret;
				}

				pTemp->Unlock(buf, size, NULL, NULL);
				desc.dwBufferBytes = pos;

				dsound_->CreateSoundBuffer(&desc, &soundSources[filePath]->buffer, NULL);
				soundSources[filePath]->buffer->Lock(0, pos, (LPVOID*)&buf2, &pos, NULL, NULL, DSBLOCK_ENTIREBUFFER);
				CopyMemory(buf2, buf, pos);
				soundSources[filePath]->buffer->Unlock(buf2, size, NULL, NULL);
				pTemp->Release();

				ov_clear(&oggVorbisFile_);
				fclose(f);

				buf = NULL;
			}
			else if (filePath.extension() == ".wav")
			{
				auto soundResource = new WaveSoundResource();
				soundSources.insert(std::pair<const path&, SoundResource*>(filePath, soundResource));
				soundResource->type = ST_Wave;

				HMMIO wavefile;
				wavefile = mmioOpenA(const_cast<LPSTR>(filePath.string().c_str()), 0, MMIO_READ | MMIO_ALLOCBUF);

				if (wavefile == NULL)
				{
					return nullptr;
				}

				MMCKINFO parent;
				memset(&parent, 0, sizeof(MMCKINFO));
				parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
				if (mmioDescend(wavefile, &parent, 0, MMIO_FINDRIFF))
				{
					mmioClose(wavefile, 0);
					return nullptr;
				}

				MMCKINFO child;
				memset(&child, 0, sizeof(MMCKINFO));
				child.fccType = mmioFOURCC('f', 'm', 't', ' ');
				if (mmioDescend(wavefile, &child, &parent, 0))
				{
					mmioClose(wavefile, 0);
					return nullptr;
				}

				mmioRead(wavefile, (char*)&soundResource->format, sizeof(WAVEFORMATEX));

				if (soundResource->format.wFormatTag != WAVE_FORMAT_PCM)
				{
					mmioClose(wavefile, 0);
					return nullptr;
				}

				mmioAscend(wavefile, &child, 0);
				child.ckid = mmioFOURCC('d', 'a', 't', 'a');
				if (mmioDescend(wavefile, &child, &parent, MMIO_FINDCHUNK))
				{
					mmioClose(wavefile, 0);
					return nullptr;
				}

				soundResource->dwSize = child.cksize;
				soundResource->pData = (BYTE*)malloc(soundResource->dwSize);

				if (soundResource->pData == NULL)
				{
					mmioClose(wavefile, 0);
					return nullptr;
				}

				DSBUFFERDESC bufdesc;
				memset(&bufdesc, 0, sizeof(DSBUFFERDESC));
				bufdesc.dwSize = sizeof(DSBUFFERDESC);
				bufdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
				bufdesc.dwBufferBytes = soundResource->dwSize;
				bufdesc.lpwfxFormat = &soundResource->format;

				if ((dsound_->CreateSoundBuffer(&bufdesc, &soundResource->buffer, NULL)) != DS_OK)
				{
					mmioClose(wavefile, 0);
					return nullptr;
				}

				void *write1 = 0, *write2 = 0;
				unsigned long length1, length2;
				soundResource->buffer->Lock(0, soundResource->dwSize, &write1, &length1, &write2, &length2, 0);
				if (write1 > 0)
					mmioRead(wavefile, (char*)write1, length1);
				if (write2 > 0)
					mmioRead(wavefile, (char*)write1, length2);
				soundResource->buffer->Unlock(write1, length1, write2, length2);

				mmioClose(wavefile, 0);
			}
		}

		return soundSources[filePath];
	}
	else
	{
		return nullptr;
	}
}

SoundCode SoundManager::Play(const path& filePath)
{
	if (dsound_ != nullptr)
	{
		Load(filePath);

		SoundCode code = -1, nowCode = 0;
		Sound* sound;

		while (code == -1)
		{
			code = nowCode;

			for (auto iter : sounds)
			{
				if (iter->id == nowCode)
				{
					code = -1;
				}
			}

			nowCode++;
		}

		if (soundSources[filePath]->type == ST_Ogg)
		{
			sound = new Sound(ST_Ogg);
			sound->id = code;
			sound->buffer = soundSources[filePath]->buffer;
			dsound_->DuplicateSoundBuffer(soundSources[filePath]->buffer, &sound->buffer);
			sound->source = soundSources[filePath];

			if (sound->options.isMute)
				sound->buffer->SetVolume(DSBVOLUME_MIN);
			else
				sound->buffer->SetVolume((sound->options.volume - 1) * 10000);
			sound->buffer->SetFrequency(sound->options.pitch * 44100);
			sound->buffer->SetPan(sound->options.dir * 10000);
			sound->buffer->Play(0, 0, sound->options.isLoop ? DSBPLAY_LOOPING : 0);
		}
		else if (soundSources[filePath]->type == ST_Wave)
		{
			sound = new Sound(ST_Wave);
			sound->id = code;
			sound->buffer = soundSources[filePath]->buffer;
			dsound_->DuplicateSoundBuffer(soundSources[filePath]->buffer, &sound->buffer);
			sound->source = soundSources[filePath];

			if (sound->options.isMute)
				sound->buffer->SetVolume(DSBVOLUME_MIN);
			else
				sound->buffer->SetVolume((sound->options.volume - 1) * 10000);
			sound->buffer->SetFrequency(sound->options.pitch * 44100);
			sound->buffer->SetPan(sound->options.dir * 10000);
			sound->buffer->Play(0, 0, sound->options.isLoop ? DSBPLAY_LOOPING : 0);
		}

		sounds.push_back(sound);

		return code;
	}

	return -1;
}

SoundCode SoundManager::Play(const path& filePath, SoundOptions soundOptions)
{
	if (dsound_ != nullptr)
	{
		Load(filePath);

		std::cout << "WOW" << std::endl;

		SoundCode code = -1, nowCode = 0;
		Sound* sound;

		while (code == -1)
		{
			code = nowCode;

			for (auto iter : sounds)
			{
				if (iter->id == nowCode)
				{
					code = -1;
				}
			}

			nowCode++;
		}

		if (soundSources[filePath]->type == ST_Ogg)
		{
			sound = new Sound(ST_Ogg, soundOptions);
			sound->id = code;
			sound->buffer = soundSources[filePath]->buffer;
			dsound_->DuplicateSoundBuffer(soundSources[filePath]->buffer, &sound->buffer);
			sound->source = soundSources[filePath];

			if (sound->options.isMute)
				sound->buffer->SetVolume(DSBVOLUME_MIN);
			else
				sound->buffer->SetVolume((sound->options.volume - 1) * 10000);
			sound->buffer->SetFrequency(sound->options.pitch * 44100);
			sound->buffer->SetPan(sound->options.dir * 10000);
			sound->buffer->Play(0, 0, sound->options.isLoop ? DSBPLAY_LOOPING : 0);
		}
		else if (soundSources[filePath]->type == ST_Wave)
		{
			sound = new Sound(ST_Wave, soundOptions);
			sound->id = code;
			sound->buffer = soundSources[filePath]->buffer;
			dsound_->DuplicateSoundBuffer(soundSources[filePath]->buffer, &sound->buffer);
			sound->source = soundSources[filePath];
			sound->options = soundOptions;

			if (sound->options.isMute)
				sound->buffer->SetVolume(DSBVOLUME_MIN);
			else
				sound->buffer->SetVolume((sound->options.volume - 1) * 10000);
			sound->buffer->SetFrequency(sound->options.pitch * 44100);
			sound->buffer->SetPan(sound->options.dir * 10000);
			sound->buffer->Play(0, 0, sound->options.isLoop ? DSBPLAY_LOOPING : 0);
		}
		sounds.push_back(sound);

		return code;
	}
	else
	{
		return -1;
	}
}

void SoundManager::SetOptions(SoundCode code, SoundOptions options)
{
	if (dsound_ == nullptr)
		return;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			sound->options = options;

			if (sound->options.isMute)
				sound->buffer->SetVolume(DSBVOLUME_MIN);
			else
				sound->buffer->SetVolume((sound->options.volume - 1) * 10000);
			sound->buffer->SetFrequency(sound->options.pitch * 44100);
			sound->buffer->SetPan(sound->options.dir * 10000);

			return;
		}
	}
}

bool SoundManager::IsPlaying(SoundCode code)
{
	if (dsound_ == nullptr)
		false;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			if (sound->type == ST_Ogg)
			{
				DWORD dwStatus;
				sound->buffer->GetStatus(&dwStatus);
				if (dwStatus & DSBSTATUS_PLAYING)
				{
					return true;
				}
				return false;
			}
			else if (sound->type == ST_Wave)
			{
				DWORD dwStatus;

				sound->buffer->GetStatus(&dwStatus);

				if (dwStatus & DSBSTATUS_PLAYING)
				{
					return true;
				}
				return false;
			}
		}
	}

	return false;
}

bool SoundManager::IsPlaying(Sound* sound)
{
	if (dsound_ == nullptr)
		false;

	if (sound->type == ST_Ogg)
	{
		DWORD dwStatus;
		sound->buffer->GetStatus(&dwStatus);
		if (dwStatus & DSBSTATUS_PLAYING)
		{
			return true;
		}
		return false;
	}
	else if (sound->type == ST_Wave)
	{
		DWORD dwStatus;

		sound->buffer->GetStatus(&dwStatus);

		if (dwStatus & DSBSTATUS_PLAYING)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool SoundManager::UpdateSound(Sound* sound)
{
	if (dsound_ == nullptr)
		false;

	if (!IsPlaying(sound) && !sound->isPause)
	{
		if (sound->options.isLoop)
		{
			sound->buffer->Stop();
			sound->buffer->Play(0, 0, DSBPLAY_LOOPING);
		}
		else
		{
			if (sound->options.autoDelete)
			{
				return true;
			}
			else
			{
				sound->buffer->Stop();
			}
		}
	}

	return false;
}

void SoundManager::Stop(SoundCode code)
{
	if (dsound_ == nullptr)
		return;

	Sound* sound_ = nullptr;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			sound_ = sound;
		}
	}

	if (sound_ != nullptr)
	{
		if (sound_->options.autoDelete)
		{
			sound_->buffer->Release();
			sounds.remove(sound_);
		}
		else
		{
			sound_->buffer->Stop();
			sound_->options.isLoop = false;
		}
	}
}

void SoundManager::Pause(SoundCode code)
{
	if (dsound_ == nullptr)
		return;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			sound->isPause = true;
			DWORD dwPlayCursol;
			DWORD dwWriteCursol;
			sound->buffer->GetCurrentPosition(&dwPlayCursol, &dwWriteCursol);
			sound->lastPos = dwPlayCursol;
			sound->buffer->Stop();

			return;
		}
	}
}

Sound* SoundManager::GetSound(SoundCode code)
{
	if (dsound_ == nullptr)
		return nullptr;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			return sound;
		}
	}

	return nullptr;
}

void SoundManager::Start(SoundCode code)
{
	if (dsound_ == nullptr)
		return;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			sound->isPause = false;
			sound->buffer->Play(0, 0, sound->options.isLoop ? DSBPLAY_LOOPING : 0);
			sound->buffer->SetCurrentPosition(sound->lastPos);

			return;
		}
	}
}

void SoundManager::Delete(SoundCode code)
{
	if (dsound_ == nullptr)
		return;

	Sound* sound_ = nullptr;

	for (auto sound : sounds)
	{
		if (sound->id == code)
		{
			sound_ = sound;
		}
	}

	if (sound_ != nullptr)
	{
		sound_->buffer->Release();
		sounds.remove(sound_);
	}
}

void SoundManager::Clear()
{
	if (dsound_ == nullptr)
		return;

	for (auto sound : sounds)
	{
		sound->buffer->Release();
	}

	sounds.clear();
}

void SoundManager::Update()
{
	if (dsound_ == nullptr)
		return;

	vector<Sound*> deleteSounds;

	for (auto sound : sounds)
	{
		if (UpdateSound(sound))
		{
			deleteSounds.push_back(sound);
		}
	}

	for (auto sound : deleteSounds)
	{
		sound->buffer->Release();
		sounds.remove(sound);
	}
}