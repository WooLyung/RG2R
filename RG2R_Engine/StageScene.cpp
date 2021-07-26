#include "stdafx.h"
#include "StageScene.h"
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
#include "Cursor.h"

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}

void StageScene::OnStart()
{
	AttachObject(new Cursor);

	auto chapterObj = CreateObject();
	auto spriteRenderer = chapterObj->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Chapters/chapter1.png")
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

	goToInGame = new CommandList;
	goToInGame->PushCommand([=]() {
		SceneData::GetInstance()->inGameCode = 0;
		RG2R_SceneM->ChangeScene(new InGameScene, true);
		}, 1);
	chapterObj->commandLists.push_back(goToInGame);

	goToChapter = new CommandList;
	goToChapter->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}, 1);
	chapterObj->commandLists.push_back(goToChapter);

	switch (StageData::GetInstance()->chapter)
	{
		case 1:
			spriteRenderer->SetTexture("Resources/Sprites/UIs/Chapters/chapter1.png");
			break;
		case 2:
			spriteRenderer->SetTexture("Resources/Sprites/UIs/Chapters/chapter2.png");
			break;
		case 3:
			spriteRenderer->SetTexture("Resources/Sprites/UIs/Chapters/chapter3.png");
			break;
		case 4:
			spriteRenderer->SetTexture("Resources/Sprites/UIs/Chapters/chapter4.png");
			break;
		case 5:
			spriteRenderer->SetTexture("Resources/Sprites/UIs/Chapters/chapter5.png");
			break;
		case 6:
			spriteRenderer->SetTexture("Resources/Sprites/UIs/Chapters/chapter6.png");
			break;
	}

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));

	stages.push_back(new StageChoice(7, "Resources/Sprites/UIs/Stages/stage7.png", this, Vec2F(2.5f, -0.5f)));
	stages.push_back(new StageChoice(8, "Resources/Sprites/UIs/Stages/stage8.png", this, Vec2F(4.f, -0.5f)));
	stages.push_back(new StageChoice(5, "Resources/Sprites/UIs/Stages/stage5.png", this, Vec2F(2.5f, 1.5f)));
	stages.push_back(new StageChoice(6, "Resources/Sprites/UIs/Stages/stage6.png", this, Vec2F(4.f, 1.5f)));
	stages.push_back(new StageChoice(2, "Resources/Sprites/UIs/Stages/stage2.png", this, Vec2F(-2.5f, 0.5f)));
	stages.push_back(new StageChoice(1, "Resources/Sprites/UIs/Stages/stage1.png", this, Vec2F(-4.f, 0.5f)));
	stages.push_back(new StageChoice(4, "Resources/Sprites/UIs/Stages/stage4.png", this, Vec2F(-2.5f, -1.5f)));
	stages.push_back(new StageChoice(3, "Resources/Sprites/UIs/Stages/stage3.png", this, Vec2F(-4.f, -1.5f)));

	for (auto iter : stages)
	{
		AttachObject(iter);
	}
}

void StageScene::ChoiceStage()
{
	if (!isFinish)
	{
		isFinish = true;

		for (auto iter : stages)
		{
			iter->Disappear();
			goToInGame->Start();
			appearWait->Start();
		}
	}
}

void StageScene::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER)
	{
		Back();
	}
}

void StageScene::Back()
{
	if (!isFinish)
	{
		isFinish = true;

		for (auto iter : stages)
		{
			iter->Disappear();
			goToChapter->Start();
			appearWait->Start();
			moveFlag = -1;
		}
	}
}