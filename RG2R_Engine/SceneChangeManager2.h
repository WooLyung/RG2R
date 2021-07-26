#pragma once
#include "Object.h"
#include "MapCreateScene.h"

class MapCreateScene;

class SceneChangeManager2 :
	public Object
{
private:
	MapCreateScene* scene;

	CommandList* toInGameScene;
	CommandList* toStageScene;
	CommandList* toMapCreateScene;

public:
	SceneChangeManager2(MapCreateScene*);
	~SceneChangeManager2();

	void Reset();
	void Back();
	void Try();
};