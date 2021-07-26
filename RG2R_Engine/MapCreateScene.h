#pragma once
#include "Scene.h"
#include "SceneChangeManager2.h"
#include "Palette.h"
#include "GateF.h"
#include "Tiles.h"
#include "Cursor.h"
#include <list>

#include "MenuButtonM.h"
#include "ResetButtonM.h"
#include "TryButtonM.h"

class MenuButtonM;
class ResetButtonM;
class TryButtonM;
class SceneChangeManager2;
class Palette;

class MapCreateScene :
	public Scene
{
private:
	SceneChangeManager2* sceneChangeManager;

	Palette* palette;
	Tiles* tiles;
	MenuButtonM* menu;
	ResetButtonM* reset;
	TryButtonM* tryb;

	bool isFinish = false;

	void Load();

public:
	Cursor* cursor;
	std::list<GateF*> gates;

	MapCreateScene();
	~MapCreateScene();

	void OnStart();
	void OnUpdate();
	void Disappear(int);
	GateF* CreateGate(std::string, std::string, Vec2L);
	Vec2L GetTilePos();
};