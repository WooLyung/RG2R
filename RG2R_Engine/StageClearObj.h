#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "InGameScene.h"

class StageClearObj :
	public Object
{
	friend class ToNextButton;

private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	InGameScene* scene;

	// animations
	float animTime = 0;
	CommandList* appearAnim;
	CommandList* disappearAnim;

public:
	StageClearObj(InGameScene*);
	~StageClearObj();

	void OnStart();
	void OnUpdate();
	void Disappear();
};