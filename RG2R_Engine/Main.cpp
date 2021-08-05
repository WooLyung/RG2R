#include "stdafx.h"
#include "Scene.h"
#include "WrappedEngine.h"
#include "TestScene.h"

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	WrappedEngine()
		.SetFirstScene(new TestScene)
		.Start();
}