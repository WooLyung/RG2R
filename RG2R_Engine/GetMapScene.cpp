#include "stdafx.h"
#include "GetMapScene.h"
#include "Engine.h"
#include "Cursor.h"
#include "InGameScene.h"
#include "MapEditData.h"

#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"

GetMapScene::GetMapScene()
{
}

GetMapScene::~GetMapScene()
{
}

void GetMapScene::OnStart()
{
	AttachObject(new Cursor);

	Object* textObj = CreateObject();
	text = textObj->AttachComponent<TextRenderer>()
		->SetText("랜덤한 회로도를 가져오는 중입니다.")
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER)
		->SetTextColor(Color(1, 1, 1, 0))
		->SetSize(40);

	appear = new CommandList;
	appear->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 1.2f;
		text->SetTextColor(Color(1, 1, 1, animTime));

		if (animTime >= 1)
		{
			animTime = 0;
			text->SetTextColor(Color(1, 1, 1, 1));
			appear->Stop();
			WinExec("Resources\\Processes\\Get\\Get.exe", SW_HIDE);
			disappear->Start();
		}
		}, 0);
	appear->SetIsLoop(true);
	appear->Start();
	textObj->commandLists.push_back(appear);

	disappear = new CommandList;
	disappear->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 1.2f;
		text->SetTextColor(Color(1, 1, 1, 1 - animTime));

		if (animTime >= 1)
		{
			animTime = 1;
			text->SetTextColor(Color(1, 1, 1, 1 - animTime));
			disappear->Stop();

			MapEditData::GetInstance()->playType = 2;
			RG2R_SceneM->ChangeScene(new InGameScene);
		}
		}, 0);
	disappear->SetIsLoop(true);
	textObj->commandLists.push_back(disappear);

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));
}