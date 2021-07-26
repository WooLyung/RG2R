#include "stdafx.h"
#include "Light3.h"

Light3::Light3(long x, long y, Dir dir)
	: Light(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light3.png");

	input.push_back(Vec2L(-1, 0));
	input.push_back(Vec2L(1, 0));

	SetRot(dir);
}

Light3::~Light3()
{
}