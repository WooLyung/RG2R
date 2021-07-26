#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"

class Pen3 :
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
	Pen3(bool);
	~Pen3();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};