#pragma once
#include "Scene.h"
#include "Gate.h"
#include "Line.h"
#include "GameInputManager.h"
#include "ObjectManager.h"
#include "PlayManager.h"
#include "SceneChangeManager.h"
#include "Tiles.h"
#include "PlayButton.h"
#include "Popup.h"
#include "PostIt.h"
#include "PlayButton.h"
#include "ResetButton.h"
#include "MenuButton.h"
#include "EditButton.h"
#include "ToNextButton.h"
#include "ToMenuButton.h"
#include "StageClearObj.h"
#include "Cursor.h"
#include <map>

class InGameScene :
	public Scene
{
	friend class GameInputManager;
	friend class ObjectManager;
	friend class PlayManager;
	friend class SceneChangeManager;
	friend class PlayButton;
	friend class ResetButton;
	friend class MenuButton;
	friend class EditButton;
	friend class ToNextButton;
	friend class ToMenuButton;
	friend class StageClearObj;

private:
	GameInputManager* gameInputManager;
	ObjectManager* objectManager;
	PlayManager* playManager;
	SceneChangeManager* sceneChangeManager;

	Popup* popup;
	PostIt* postit;
	PlayButton* playButton;
	ResetButton* resetButton;
	MenuButton* menuButton;
	EditButton* editButton;

	Vec2L mapSize;
	Tiles* tiles;

	bool isFinish = false;

	void PushGate(Gate*);
	void Init();
	void CreateGate(std::map<std::string, std::string>);
	Vec2L GetTilePos();

public:
	Cursor* cursor;

	InGameScene();
	~InGameScene();

	void OnStart();
	void OnUpdate();
	void PopMsg(int);
	void Disappear(int);
};