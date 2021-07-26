#include "stdafx.h"
#include "SoundMaster.h"
#include "Engine.h"
#include "SettingData.h"

SoundMaster* SoundMaster::GetInstance()
{
	static auto sceneData = SoundMaster();
	return &sceneData;
}

void SoundMaster::PlayEffectSound(SoundID id)
{
	if (SettingData::GetInstance()->sound_effect == 1)
	{
		if (id == SoundID::LINE_CONNECT)
		{
			SoundOptions options;
			options.volume = 0.8f;
			RG2R_SoundM->Play("Resources/Sounds/line_connect.wav", options);
		}
		else if (id == SoundID::DROP)
		{
			SoundOptions options;
			options.volume = 0.95f;
			RG2R_SoundM->Play("Resources/Sounds/drop.wav", options);
		}
		else if (id == SoundID::CLICK)
		{
			SoundOptions options;
			options.volume = 0.65f;
			options.pitch = 1.35f;
			RG2R_SoundM->Play("Resources/Sounds/click.wav", options);
		}
		else if (id == SoundID::LIFT)
		{
			SoundOptions options;
			options.volume = 0.8f;
			options.pitch = 1.2f;
			RG2R_SoundM->Play("Resources/Sounds/lift.wav", options);
		}
		else if (id == SoundID::SLIDE)
		{
			SoundOptions options;
			options.volume = 0.8f;
			RG2R_SoundM->Play("Resources/Sounds/slide.wav", options);
		}
	}
}

void SoundMaster::PlayBGM()
{
	std::cout << bgmid << std::endl;

	if (bgmid == -1)
	{
		SoundOptions options;
		options.volume = 0.8f;
		options.isLoop = true;
		if (SettingData::GetInstance()->sound_bgm == 0)
			options.isMute = true;

		bgmid = RG2R_SoundM->Play("Resources/Sounds/bgm.ogg", options);
	}
	else
	{
		SoundOptions options;
		options.volume = 0.8f;
		options.isLoop = true;
		if (SettingData::GetInstance()->sound_bgm == 0)
			options.isMute = true;

		std::cout << options.isMute << std::endl;

		RG2R_SoundM->SetOptions(bgmid, options);
	}
}