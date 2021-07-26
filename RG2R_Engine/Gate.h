#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "Transform.h"
#include "Line.h"
#include "CommandList.h"

class Line;

class Gate :
	public Object
{
private:
	CommandList* changeColor;

protected:
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;

	bool isStatic;
	Color8 color;
	Color nowColor = { 0.8f, 0.8f, 0.8f, 1 };
	Color toColor = { 0.8f, 0.8f, 0.8f, 1 };

	Dir dir = Dir::RIGHT;

public:
	Gate(long, long, Dir);
	~Gate();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();
	Vec2L tilePos;
	Dir GetDir();
	Color8 GetColor() { return color; }

	void SetDir(Dir);
	void SetPos(int, int);
	void SetRot(Dir);
	void SetStatic(bool);
	bool GetStatic();

	void SetColor(Color8);
	void SetColor(Color);

	std::vector<Vec2L> input;
	std::vector<Vec2L> output;

	virtual std::type_index GetID(void) = 0;
};