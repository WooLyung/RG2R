#pragma once
#include "Object.h"
#include "TextRenderer.h"
#include "Effect.h"

class IntroManager :
	public Object
{
private:
	Object* black;
	TextRenderer* textRenderer;
	Effect* effect;

	enum IntroState {
		sans,
		firstWait,
		appear1, wait1, disappear1,
		textWait,
		appear2, wait2, disappear2,
		nextWait
	};

	IntroState state = sans;
	float time = 0;

public:
	IntroManager();
	~IntroManager();

	void OnStart();
	void OnUpdate();
};