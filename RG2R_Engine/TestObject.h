#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"

class TestObject
	: public Object
{
	Transform* transform;
	SpriteRenderer* renderer;

	void OnStart();
	void OnUpdate();
};