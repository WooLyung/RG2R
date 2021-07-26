#include "stdafx.h"
#include "ReverseGate.h"

ReverseGate::ReverseGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/reverseGate.png");

	input.push_back(Vec2L(-1, 0));
	output.push_back(Vec2L(1, 0));

	SetRot(dir);
}

ReverseGate::~ReverseGate()
{
}