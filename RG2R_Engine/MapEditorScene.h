#pragma once
#include "Scene.h"
#include "CommandList.h"
#include "MapEditCreate.h"
#include "MapEditPlay.h"

class MapEditCreate;
class MapEditPlay;

class MapEditorScene :
	public Scene
{
private:
	bool isFinish = false;

	MapEditCreate* create;
	MapEditPlay* play;

	CommandList* appearWait;
	CommandList* appear;
	CommandList* goToChapter;
	CommandList* goToMapEdit;
	CommandList* goToPlay;
	float animTime = 0;
	int moveFlag = 1;

public:
	MapEditorScene();
	~MapEditorScene();

	void OnStart();
	void OnUpdate();
	void ChoiceStage();
	void Back();
	void MapEdit();
	void MapPlay();
};