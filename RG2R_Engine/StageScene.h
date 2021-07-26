#pragma once
#include "Scene.h"
#include "StageChoice.h"
#include "CommandList.h"

class StageChoice;

class StageScene :
	public Scene
{
private:
	std::list<StageChoice*> stages;
	bool isFinish = false;

	CommandList* appearWait;
	CommandList* appear;
	CommandList* goToInGame;
	CommandList* goToChapter;
	float animTime = 0;
	int moveFlag = 1;

public:
	StageScene();
	~StageScene();

	void OnStart();
	void OnUpdate();
	void ChoiceStage();
	void Back();
};