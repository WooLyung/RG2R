#pragma once
#include "Scene.h"
#include "TextRenderer.h"

class GetMapScene :
	public Scene
{
private:
	TextRenderer* text;

	float animTime = 0;
	CommandList* appear;
	CommandList* disappear;

public:
	GetMapScene();
	~GetMapScene();

	void OnStart();
};