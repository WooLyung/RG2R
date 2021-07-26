#include "stdafx.h"
#include "ChapterScene.h"
#include "TextRenderer.h"
#include "ChapterChoice.h"
#include "Transform.h"
#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"
#include "Engine.h"
#include "StageData.h"
#include "SceneData.h"
#include "PlayerData.h"
#include "Cursor.h"
#include "GoMapEditor.h"

ChapterScene::ChapterScene()
{
}

ChapterScene::~ChapterScene()
{
}

void ChapterScene::OnStart()
{
	if (PlayerData::GetInstance()->chapter >= 2)
	{
		goMapEditor = new GoMapEditor(this);
		AttachObject(goMapEditor);
		GetMainCamera()->SetPosX(-3.5f);
	}
	settingBoard = new SettingBoard(this);
	AttachObject(settingBoard);
	AttachObject(new Cursor);
	chapters.push_back(new ChapterChoice(1, std::string("Resources/Sprites/UIs/Chapters/chapter1.png"), this));
	chapters.push_back(new ChapterChoice(2, std::string("Resources/Sprites/UIs/Chapters/chapter2.png"), this));
	chapters.push_back(new ChapterChoice(3, std::string("Resources/Sprites/UIs/Chapters/chapter3.png"), this));
	chapters.push_back(new ChapterChoice(4, std::string("Resources/Sprites/UIs/Chapters/chapter4.png"), this));
	chapters.push_back(new ChapterChoice(5, std::string("Resources/Sprites/UIs/Chapters/chapter5.png"), this));
	chapters.push_back(new ChapterChoice(6, std::string("Resources/Sprites/UIs/Chapters/chapter6.png"), this));

	for (auto iter : chapters)
	{
		AttachObject(iter);
	}

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));
}

void ChapterScene::OnUpdate()
{
	time += RG2R_TimeM->GetDeltaTime();

	if (!isFinish && time >= 1.7f && settingBoard->boardState == SettingBoard::BoardState::top)
	{
		float max = RG2R_WindowM->GetSize().width;
		float now = RG2R_InputM->GetMousePos().x;

		if (now <= max * 0.3f)
		{
			float movePow = now / max;
			movePow = 0.3f - movePow;
			GetMainCamera()->Translate(movePow * -RG2R_TimeM->GetDeltaTime() * 30, 0);
		}
		if (now >= max * 0.7f)
		{
			float movePow = 1 - now / max;
			movePow = 0.3f - movePow;
			GetMainCamera()->Translate(movePow * RG2R_TimeM->GetDeltaTime() * 30, 0);
		}

		if (PlayerData::GetInstance()->chapter >= 2
			&& GetMainCamera()->GetPos().x <= -3.5f)
			GetMainCamera()->SetPosX(-3.5f);
		else if (
			PlayerData::GetInstance()->chapter == 1
			&& GetMainCamera()->GetPos().x <= 0)
			GetMainCamera()->SetPosX(0);

		if (GetMainCamera()->GetPos().x >= 3.5f * (6 - 3))
			GetMainCamera()->SetPosX(3.5f * (6 - 3));
	}
}

void ChapterScene::ChoiceChapter()
{
	if (!isFinish)
	{
		isFinish = true;
		settingBoard->changeScene->Start();

		for (auto iter : chapters)
		{
			if (iter->chapter != StageData::GetInstance()->chapter)
				iter->MoveDown();
			else
				iter->GoStageScene();
		}
		
		if (goMapEditor != nullptr)
		{
			goMapEditor->MoveDown();
		}
	}
}

void ChapterScene::MapEditor()
{
	if (!isFinish)
	{
		isFinish = true;
		settingBoard->changeScene->Start();

		for (auto iter : chapters)
		{
			iter->MoveDown();
		}

		goMapEditor->ChangeScene();
	}
}