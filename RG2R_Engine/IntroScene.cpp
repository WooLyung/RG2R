#include "stdafx.h"
#include "IntroScene.h"
#include "IntroManager.h"
#include "Cursor.h"
#include "Engine.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::OnStart()
{
	AttachObject(new IntroManager);
}