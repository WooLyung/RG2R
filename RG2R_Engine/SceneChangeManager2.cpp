#include "stdafx.h"
#include "SceneChangeManager2.h"
#include "Engine.h"
#include "ChapterScene.h"
#include "SceneData.h"
#include "InGameScene.h"
#include "MapEditData.h"

SceneChangeManager2::SceneChangeManager2(MapCreateScene* scene)
{
	this->scene = scene;

	toInGameScene = new CommandList;
	toInGameScene->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new InGameScene, true);
		}, 1.2f);
	commandLists.push_back(toInGameScene);

	toStageScene = new CommandList;
	toStageScene->PushCommand([=]() {
		SceneData::GetInstance()->isFirst = false;
		RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}, 1.2f);
	commandLists.push_back(toStageScene);

	toMapCreateScene = new CommandList;
	toMapCreateScene->PushCommand([=]() {
		SceneData::GetInstance()->isFirst = false;
		MapEditData::GetInstance()->gates.clear();
		RG2R_SceneM->ChangeScene(new MapCreateScene, true);
		}, 1.2f);
	commandLists.push_back(toMapCreateScene);
}

SceneChangeManager2::~SceneChangeManager2()
{
}

void SceneChangeManager2::Reset()
{
	toMapCreateScene->Start();
}

void SceneChangeManager2::Back()
{
	toStageScene->Start();
}

void SceneChangeManager2::Try()
{
	toInGameScene->Start();
}