#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "StageScene.h"

class StageScene;

class StageChoice :
	public Object
{
private:
	enum StageState {
		appear, wait, disappear, wait2
	};

	enum InputState {
		hover, click, none
	};

	std::string path;
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	StageScene* scene;
	Vec2F toPos;
	Object* lock = nullptr;

	StageState state = appear;
	InputState inputState = InputState::none;

	// animations
	float animTime = 0;
	int hoverFlag = 1;
	int sizeFlag = 1;
	CommandList* appearAnim;
	CommandList* disappearAnim;
	CommandList* hoverAnim;
	CommandList* changeScale;

	void Input();

public:
	int stage = 0;

	StageChoice(int, std::string, StageScene*, Vec2F);
	~StageChoice();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Disappear();
};