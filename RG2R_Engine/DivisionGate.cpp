#include "stdafx.h"
#include "DivisionGate.h"

DivisionGate::DivisionGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/divisionGate.png");

	input.push_back(Vec2L(-1, 0));
	output.push_back(Vec2L(0, 1));
	output.push_back(Vec2L(0, -1));

	SetRot(dir);
}

DivisionGate::~DivisionGate()
{
}