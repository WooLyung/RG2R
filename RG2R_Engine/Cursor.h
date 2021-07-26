#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"

class Cursor :
	public Object
{
private:
	SpriteRenderer* spriteRenderer;
	Transform* transform;

public:
	Cursor();
	~Cursor();

	void OnStart();
	void OnUpdate();
	void SetSpr(int);
};