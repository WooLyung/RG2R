#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "Transform.h"
#include "Gate.h"

class Gate;

class Line :
	public Object
{
private:
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;

private:
	CommandList* changeColor;
	Color nowColor = { 0.8f, 0.8f, 0.8f, 1 };
	Color toColor = { 0.8f, 0.8f, 0.8f, 1 };
	Color8 color;

public:
	Line(long, long);
	~Line();

	void OnStart();
	void OnDestroy();
	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void SetSprite();
	void SetColor(Color8);
	void SetColor(Color);
	Color8 GetColor() { return color; }

	Vec2L tilePos;
	Vec2L input = Vec2L(0, 0);
	Vec2L output = Vec2L(0, 0);
};