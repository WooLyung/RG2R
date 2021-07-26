#pragma once
#include "Object.h"
#include "InGameScene.h"

class SceneChangeManager :
	public Object
{
private:
	InGameScene* scene;

	CommandList* toInGameScene;
	CommandList* toStageScene;
	CommandList* toEditScene;
	CommandList* toGetMapScene;

public:
	SceneChangeManager(InGameScene*);
	~SceneChangeManager();

	void Reset();
	void Back();
	void Diff();
	void Edit();
	void GetMap();
};