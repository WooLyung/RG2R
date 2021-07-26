#pragma once

class StageData
{
public:
	int chapter = 1;
	int stage = 1;

	static StageData* GetInstance();
};