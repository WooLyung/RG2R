#include"stdafx.h"
#include"WrappedEngine.h"
#include "Scene.h"
#include "TestScene.h"

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	WrappedEngine()
		.SetFirstScene(new TestScene)
		.SetSetting([]() { std::cout << "미리 설정" << std::endl; })
		.Start();
}

