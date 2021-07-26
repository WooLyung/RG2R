#include "stdafx.h"
#include "AndGate.h"

AndGate::AndGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/andGate.png");

	input.push_back(Vec2L(0, 1));
	input.push_back(Vec2L(0, -1));
	output.push_back(Vec2L(1, 0));

	SetRot(dir);
}

AndGate::~AndGate()
{
}