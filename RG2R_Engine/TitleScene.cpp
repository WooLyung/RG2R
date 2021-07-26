#include "stdafx.h"
#include "TitleScene.h"
#include "Transform.h"
#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"
#include "Engine.h"
#include "ChapterScene.h"
#include "TextRenderer.h"
#include "Cursor.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::OnStart()
{
	AttachObject(new Cursor);
	AttachObject(new Pen1(true));
	AttachObject(new Pen2(true));
	AttachObject(new Pen3(true));
	AttachObject(new Ruler1(true));
	AttachObject(new Ruler2(true));

	title = new Title;
	AttachObject(title);
	titleText = new TitleText;
	AttachObject(titleText);
}

void TitleScene::OnUpdate()
{
	time += RG2R_TimeM->GetDeltaTime();

	if (time >= 1 && RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		title->NextScene();
		titleText->NextScene();
	}
}