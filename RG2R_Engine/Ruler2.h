#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"

class Ruler2 :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	// animations
	bool isAnim = false;
	float animTime = 0;
	CommandList* appearAnim;

public:
	Ruler2(bool);
	~Ruler2();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};