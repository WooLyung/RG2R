#pragma once
#include "SoundManager.h"

enum SoundID {
	LIFT,
	DROP,
	CLICK,
	LINE_CONNECT,
	SLIDE
};

class SoundMaster
{
private:
	SoundCode bgmid = -1;

public:
	static SoundMaster* GetInstance();
	
	void PlayEffectSound(SoundID);
	void PlayBGM();
};