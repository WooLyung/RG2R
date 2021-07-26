#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "TextRenderer.h"
#include "InGameScene.h"
#include "StageClearObj.h"

class InGameScene;
class StageClearObj;

class ToMenuButton :
	public Object
{
private:
	enum InputState {
		hover, click, none, end
	};

	Transform* transform;
	SpriteRenderer* spriteRenderer;
	InputState inputState = InputState::none;
	InGameScene* scene;
	StageClearObj* clearObj;

	float changeTime = -1;

	// animations
	float animTime = 0;
	int hoverFlag = 1, sizeFlag = 1;
	CommandList* hoverAnim;
	CommandList* changeScale;

public:
	ToMenuButton(InGameScene*, StageClearObj*);
	~ToMenuButton();

	Transform* parentTransform;
	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Input();
};