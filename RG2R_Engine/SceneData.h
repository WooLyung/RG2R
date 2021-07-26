#pragma once

class SceneData
{
public:
	bool isFirst = true;
	int inGameCode = 0;

	static SceneData* GetInstance();
};