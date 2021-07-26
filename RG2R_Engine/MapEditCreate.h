#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "MapEditorScene.h"

class MapEditorScene;

class MapEditCreate :
	public Object
{
private:
	enum StageState {
		appear, wait, disappear, wait2
	};

	Transform* transform;
	SpriteRenderer* spriteRenderer;
	MapEditorScene* scene;

	StageState state = appear;

	// animations
	float animTime = 0;
	CommandList* appearAnim;
	CommandList* disappearAnim;

public:
	MapEditCreate(MapEditorScene*);
	~MapEditCreate();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Disappear();
};