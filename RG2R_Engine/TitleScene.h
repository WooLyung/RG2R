#pragma once
#include "Scene.h"
#include "Title.h"
#include "TitleText.h"

class TitleScene
	: public Scene
{
private:
	Title* title;
	TitleText* titleText;
	float time = 0;

public:
	TitleScene();
	~TitleScene();

	void OnStart();
	void OnUpdate();
};