#include "stdafx.h"
#include "WrappedEngine.h"
#include "Scene.h"
#include "TestScene.h"
#include "Engine.h"

void PreSetting()
{
	RG2R_WindowM->SetFullscreen(true);
}

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	WrappedEngine()
		.SetFirstScene(new TestScene)
		.SetSetting(PreSetting)
		.Start();
}