#include "stdafx.h"
#include "Battery.h"

Battery::Battery(long x, long y, Dir dir, Color8 color)
	: Gate(x, y, dir)
{
	auto uncolored = new Object;
	uncoloredSpriteRenderer = uncolored->AttachComponent<SpriteRenderer>();
	uncoloredSpriteRenderer->SetZ_index(6);
	uncolored->GetComponent<Transform>()->SetAnchor(64, 64);
	uncolored->ChangeParent(this);

	spriteRenderer->SetTexture("Resources/Sprites/Gates/battery.png");
	uncoloredSpriteRenderer->SetTexture("Resources/Sprites/Gates/battery_uncolored.png");
	this->color = color;
	toColor = Color(color.r, color.g, color.b, 1);
	nowColor = Color(color.r, color.g, color.b, 1);
	effect->ClearEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(toColor));

	output.push_back(Vec2L(1, 0));

	SetRot(dir);
}

Battery::~Battery()
{
}

SpriteRenderer* Battery::GetUncoloredRenderer()
{
	return uncoloredSpriteRenderer;
}