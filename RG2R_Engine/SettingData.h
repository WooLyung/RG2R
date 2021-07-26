#pragma once

class SettingData
{
public:
	int effect = 1;
	int sound_bgm = 1;
	int sound_effect = 1;
	int fullscreen = 1;
	int resolution = 3;

	SettingData();
	void SetData(int, int);
	static SettingData* GetInstance();
};