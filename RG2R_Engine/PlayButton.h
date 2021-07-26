#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "TextRenderer.h"
#include "InGameScene.h"

class InGameScene;

class PlayButton :
	public Object
{
private:
	enum InputState {
		hover, click, none
	};

	Transform* transform;
	SpriteRenderer* spriteRenderer;
	InputState inputState = none;
	InGameScene* scene;

	// animations
	bool isAnim = false;
	float animTime = 0;
	int hoverFlag = 1, sizeFlag = 1;
	CommandList* appearAnim;
	CommandList* disappearAnim;
	CommandList* hoverAnim;
	CommandList* changeScale;

public:
	PlayButton(bool, InGameScene*);
	~PlayButton();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Input();
	void Disappear();
};