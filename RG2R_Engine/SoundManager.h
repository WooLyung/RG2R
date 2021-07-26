#pragma once
#include <map>

using namespace std;
using namespace std::filesystem;
typedef int SoundCode;

#define     BUFSIZE    1048576*60

enum SoundType {
	ST_Wave,
	ST_Ogg,
};

struct SoundOptions {
	float pitch = 1;
	float volume = 1;
	float dir = 0;
	bool isLoop = false;
	bool autoDelete = true;
	bool isMute = false;
};

struct SoundResource {
	SoundType type;
	LPDIRECTSOUNDBUFFER	buffer = NULL;
};

struct WaveSoundResource : public SoundResource {
	DWORD dwSize;
	BYTE* pData;
	WAVEFORMATEX format;
};

struct Sound {
	SoundType type;
	SoundResource* source;
	LPDIRECTSOUNDBUFFER	buffer;
	SoundOptions options;
	int id;
	bool isPause = false;
	DWORD lastPos = 0;

	Sound(SoundType type) : type(type) {}
	Sound(SoundType type, SoundOptions options) : type(type), options(options) {}
	~Sound()
	{
		buffer->Release();
	}
};

class SoundManager
{
private:
	std::map<const path, SoundResource*> soundSources;
	list<Sound*> sounds;
	LPDIRECTSOUND8 dsound_ = nullptr;
	OggVorbis_File oggVorbisFile_;

	bool UpdateSound(Sound*);

public:
	SoundManager();
	~SoundManager();

	void Update();

	SoundCode Play(const path&);
	SoundCode Play(const path&, SoundOptions);
	SoundResource* Load(const path& filePath);
	Sound* GetSound(SoundCode);
	bool IsPlaying(SoundCode);
	bool IsPlaying(Sound*);
	void SetOptions(SoundCode, SoundOptions);
	void Pause(SoundCode);
	void Start(SoundCode);
	void Stop(SoundCode);
	void Delete(SoundCode);
	void Clear();
};