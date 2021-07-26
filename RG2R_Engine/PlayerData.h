#pragma once

class PlayerData
{
private:
	PlayerData();

public:
	static PlayerData* GetInstance();

	int chapter;
	int stage;
};