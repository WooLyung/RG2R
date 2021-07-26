#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "MapEditorScene.h"

class MapEditorScene;

class SizeChoice :
	public Object
{
private:
	enum InputState {
		hover, click, none
	};

	std::string path;
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	MapEditorScene* scene;
	Vec2F pos;

	InputState inputState = InputState::none;

	// animations
	float animTime = 0;
	int hoverFlag = 1;
	int sizeFlag = 1;
	CommandList* hoverAnim;
	CommandList* changeScale;

	void Input();

public:
	Vec2L size;

	SizeChoice(Vec2L, std::string, MapEditorScene*, Vec2F);
	~SizeChoice();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};