#include "stdafx.h"
#include "SettingData.h"
#include "Engine.h"
#include "SoundMaster.h"
#include <fstream>

SettingData* SettingData::GetInstance()
{
	static auto stageData = SettingData();
	return &stageData;
}

SettingData::SettingData()
{
	std::string data;
	std::ifstream in("Datas/settingData.txt");
	int i = 0;

	while (getline(in, data)) {
		i++;

		if (i == 1)
			sound_bgm = std::stoi(data);
		else if (i == 2)
			sound_effect = std::stoi(data);
		else if (i == 3)
			effect = std::stoi(data);
		else if (i == 4)
			fullscreen = std::stoi(data);
		else if (i == 5)
			resolution = std::stoi(data);
	}

	switch (resolution)
	{
	case 1:
		RG2R_WindowM->SetSize(Size2U(640, 360));
		break;
	case 2:
		RG2R_WindowM->SetSize(Size2U(960, 540));
		break;
	case 3:
		RG2R_WindowM->SetSize(Size2U(1280, 720));
		break;
	case 4:
		RG2R_WindowM->SetSize(Size2U(1980, 1080));
		break;
	}
	RG2R_WindowM->SetFullscreen(fullscreen);
}

void SettingData::SetData(int code, int data)
{
	if (code == 1)
	{
		sound_bgm = data;
		SoundMaster::GetInstance()->PlayBGM();
	}
	else if (code == 2)
		sound_effect = data;
	else if (code == 3)
		effect = data;
	else if (code == 4)
	{
		fullscreen = data;
		RG2R_WindowM->SetFullscreen(fullscreen);
	}
	else if (code == 5)
	{
		resolution = data;

		if (!fullscreen)
		{
			switch (resolution)
			{
			case 1:
				RG2R_WindowM->SetSize(Size2U(640, 360));
				break;
			case 2:
				RG2R_WindowM->SetSize(Size2U(960, 540));
				break;
			case 3:
				RG2R_WindowM->SetSize(Size2U(1280, 720));
				break;
			case 4:
				RG2R_WindowM->SetSize(Size2U(1980, 1080));
				break;
			}
		}
	}

	std::string out_line;
	std::ofstream out("Datas/settingData.txt");
	out << sound_bgm << std::endl;
	out << sound_effect << std::endl;
	out << effect << std::endl;
	out << fullscreen << std::endl;
	out << resolution << std::endl;
	out.close();
}