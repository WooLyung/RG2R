#include "stdafx.h"
#include "PlayerData.h"
#include <fstream>

PlayerData* PlayerData::GetInstance()
{
	static auto pd = PlayerData();
	return &pd;
}

PlayerData::PlayerData()
{
	std::string data;
	std::ifstream in("Datas/stageData.txt");
	int i = 0;
	
	while (getline(in, data)) {
		i++;
		
		if (i == 1)
			chapter = std::stoi(data);
		else if (i == 2)
			stage = std::stoi(data);
	}
}