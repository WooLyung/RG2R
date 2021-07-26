#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "TextRenderer.h"

class PostIt :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	TextRenderer* textRenderer;

	// animations
	bool isAnim = false;
	float animTime = 0;
	CommandList* appearAnim;
	CommandList* disappearAnim;

public:
	PostIt(bool);
	~PostIt();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();
	TextRenderer* GetTextRenderer();

	void OnStart();
	void OnUpdate();
	void Disappear();
};