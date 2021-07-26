#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class Dust :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	float angle, speed;

public:
	Dust();
	~Dust();

	void OnStart();
	void OnUpdate();
};