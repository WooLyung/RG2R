#include"stdafx.h"
#include"WrappedEngine.h"
#include "Scene.h"
#include "IntroScene.h"

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	WrappedEngine()
		.SetFirstScene(new IntroScene)
		.Start();
}