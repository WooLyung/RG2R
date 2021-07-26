#include "stdafx.h"
#include "Light2.h"

Light2::Light2(long x, long y, Dir dir)
	: Light(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light2.png");

	input.push_back(Vec2L(-1, 0));
	input.push_back(Vec2L(0, -1));

	SetRot(dir);
}

Light2::~Light2()
{
}