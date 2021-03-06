#include "stdafx.h"
#include "WrappedEngine.h"
#include "Engine.h"

void WrappedEngine::Start()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	RG2R->Init(startScene);
	if (setting) setting();
	RG2R->MainLoop();
	RG2R->Release();
}

WrappedEngine& WrappedEngine::SetFirstScene(Scene* scene)
{
	this->startScene = scene;
	return *this;
}

WrappedEngine& WrappedEngine::SetSetting(FP setting)
{
	this->setting = setting;
	return *this;
}
