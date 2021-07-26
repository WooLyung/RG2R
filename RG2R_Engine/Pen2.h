#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"

class Pen2 :
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
	Pen2(bool);
	~Pen2();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};