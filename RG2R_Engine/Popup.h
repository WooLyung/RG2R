#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Texture.h"

class Popup
	: public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	// animations
	float animTime;
	CommandList* pop;

public:
	Popup();
	~Popup();

	void OnStart();
	void Pop(int);
};