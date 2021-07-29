#include "stdafx.h"
#include "IntroScene.h"
#include "IntroManager.h"
#include "Cursor.h"
#include "Engine.h"
#include "SettingData.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::OnStart()
{
	ShowCursor(false);
	SettingData::GetInstance();
	AttachObject(new IntroManager);
}