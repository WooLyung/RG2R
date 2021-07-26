#include "stdafx.h"
#include "SceneChangeManager.h"
#include "Engine.h"
#include "ChapterScene.h"
#include "MapCreateScene.h"
#include "SceneData.h"
#include "GetMapScene.h"

SceneChangeManager::SceneChangeManager(InGameScene* scene)
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

	toEditScene = new CommandList;
	toEditScene->PushCommand([=]() {
		SceneData::GetInstance()->isFirst = false;
		RG2R_SceneM->ChangeScene(new MapCreateScene, true);
		}, 1.2f);
	commandLists.push_back(toEditScene);

	toGetMapScene = new CommandList;
	toGetMapScene->PushCommand([=]() {
		SceneData::GetInstance()->isFirst = false;
		RG2R_SceneM->ChangeScene(new GetMapScene, true);
		}, 1.2f);
	commandLists.push_back(toGetMapScene);
}

SceneChangeManager::~SceneChangeManager()
{
}

void SceneChangeManager::Reset()
{
	toInGameScene->Start();
}

void SceneChangeManager::Back()
{
	toStageScene->Start();
}

void SceneChangeManager::Edit()
{
	toEditScene->Start();
}

void SceneChangeManager::Diff()
{
	toInGameScene->Start();
}

void SceneChangeManager::GetMap()
{
	toGetMapScene->Start();
}