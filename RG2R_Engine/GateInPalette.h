#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include <string>

class GateInPalette :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

public:
	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();
	SpriteRenderer* batteryOutline;

	std::string type;

	GateInPalette();
	~GateInPalette();

	void OnStart();
	void Done();
	bool CheckHover();
};