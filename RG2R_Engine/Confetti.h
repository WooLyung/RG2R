#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class Confetti :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Vec2F velocity;
	int type;

public:
	Confetti(int);
	~Confetti();

	void OnStart();
	void OnUpdate();
};