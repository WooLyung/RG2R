#include "stdafx.h"
#include "MapEditorScene.h"
#include "TextRenderer.h"
#include "StageChoice.h"
#include "Transform.h"
#include "StageData.h"
#include "SceneData.h"
#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"
#include "Engine.h"
#include "InGameScene.h"
#include "ChapterScene.h"
#include "MapCreateScene.h"
#include "GetMapScene.h"
#include "MapEditData.h"
#include "Cursor.h"
#include "MapEditCreate.h"

MapEditorScene::MapEditorScene()
{
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::OnStart()
{
	AttachObject(new Cursor);

	auto chapterObj = CreateObject();
	auto spriteRenderer = chapterObj->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Chapters/map_editor.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(4);
	auto transform = chapterObj->GetComponent<Transform>()
		->SetScale(0.4f, 0.4f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearWait = new CommandList;
	appearWait->PushCommand([=]() {
		appear->Start();
		}, 0.3f);
	chapterObj->commandLists.push_back(appearWait);

	appear = new CommandList;
	appear->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2;
		transform->SetPosY(pow(animTime, 2) * 5 * moveFlag);

		if (animTime >= 1)
		{
			animTime = 0;
			appear->Stop();
		}
		}, 0);
	appear->SetIsLoop(true);
	chapterObj->commandLists.push_back(appear);

	goToChapter = new CommandList;
	goToChapter->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}, 1);
	chapterObj->commandLists.push_back(goToChapter);

	goToPlay = new CommandList;
	goToPlay->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new GetMapScene, true);
		}, 1);
	chapterObj->commandLists.push_back(goToPlay);

	goToMapEdit = new CommandList;
	goToMapEdit->PushCommand([=]() {
		MapEditData::GetInstance()->gates.clear();
		RG2R_SceneM->ChangeScene(new MapCreateScene, true);
		}, 1);
	chapterObj->commandLists.push_back(goToMapEdit);

	create = new MapEditCreate(this);
	play = new MapEditPlay(this);
	chapterObj->AttachChild(create);
	chapterObj->AttachChild(play);

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));
}

void MapEditorScene::ChoiceStage()
{
	if (!isFinish)
	{
		isFinish = true;

		create->Disappear();
		play->Disappear();
		appearWait->Start();
	}
}

void MapEditorScene::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER)
	{
		Back();
	}
}

void MapEditorScene::Back()
{
	if (!isFinish)
	{
		isFinish = true;

		create->Disappear();
		play->Disappear();
		appearWait->Start();
		goToChapter->Start();
		moveFlag = -1;
	}
}

void MapEditorScene::MapEdit()
{
	if (!isFinish)
	{
		isFinish = true;

		create->Disappear();
		play->Disappear();
		appearWait->Start();
		goToMapEdit->Start();
		moveFlag = -1;
	}
}

void MapEditorScene::MapPlay()
{
	if (!isFinish)
	{
		isFinish = true;

		create->Disappear();
		play->Disappear();
		appearWait->Start();
		goToPlay->Start();
		moveFlag = -1;
	}
}