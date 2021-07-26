#include "stdafx.h"
#include "Dust.h"
#include "RandomGenerator.h"
#include "Engine.h"

Dust::Dust()
{
}

Dust::~Dust()
{
}

void Dust::OnStart()
{
	float size = RandomGenerator::GetInstance()->GetFloat(0.5f, 0.9f);

	transform = GetComponent<Transform>()
		->SetAnchor(32, 32)
		->SetScale(size, size);
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Effects/dust.png");
	spriteRenderer->SetZ_index(4.5f);

	effect = AttachComponent<Effect>();

	angle = RandomGenerator::GetInstance()->GetFloat(0, 360);
	speed = RandomGenerator::GetInstance()->GetFloat(0.8f, 1.5f);
}

void Dust::OnUpdate()
{
	speed -= RG2R_TimeM->GetDeltaTime() * 1.2f;
	if (speed <= 0)
	{
		Destroy();
		return;
	}

	transform->Translate(cos(angle / 180.f * PI) * speed * RG2R_TimeM->GetDeltaTime(),
		sin(angle / 180.f * PI) * speed * RG2R_TimeM->GetDeltaTime());
	effect->ClearEffectInfo()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, speed > 1 ? 1 : speed)));
}