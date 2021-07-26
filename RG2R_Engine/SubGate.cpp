#include "stdafx.h"
#include "SubGate.h"

SubGate::SubGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/subGate.png");

	input.push_back(Vec2L(-1, 0));
	input.push_back(Vec2L(0, -1));
	output.push_back(Vec2L(1, 0));

	SetRot(dir);
}

SubGate::~SubGate()
{
}