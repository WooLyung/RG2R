#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Effect.h"
#include <string>

class GateF :
	public Object
{
private:
	SpriteRenderer* spriteRenderer;
	Transform* transform;
	Effect* effect;
	SpriteRenderer* staticObj;

	bool isStatic = false;
	CommandList* changeColor;

public:
	Vec2L pos;
	std::string dir = "right";
	std::string color = "white";
	std::string type = "";
	std::string texture = "";
	Color nowColor = { 1, 1, 1, 1 };
	Color toColor = { 1, 1, 1, 1 };

	SpriteRenderer* outline;

	SpriteRenderer* GetSpriteRenderer();
	Transform* GetTransform();
	Effect* GetEffect();

	void SetPos(Vec2L);
	void SetIsStatic(bool);
	void SetColor(std::string);
	bool GetIsStatic() { return isStatic; }

	GateF();
	~GateF();
};