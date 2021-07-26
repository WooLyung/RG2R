#pragma once
#include "Scene.h"
#include "ChapterChoice.h"
#include "GoMapEditor.h"
#include "SettingBoard.h"

class ChapterChoice;
class GoMapEditor;
class SettingBoard;

class ChapterScene :
	public Scene
{
private:
	std::list<ChapterChoice*> chapters;
	GoMapEditor* goMapEditor = nullptr;
	float time = 0;

public:
	SettingBoard* settingBoard;
	bool isFinish = false;

	ChapterScene();
	~ChapterScene();

	void OnStart();
	void OnUpdate();
	void MapEditor();
	void ChoiceChapter();
};