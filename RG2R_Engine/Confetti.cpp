#include "stdafx.h"
#include "Confetti.h"
#include "RandomGenerator.h"
#include "Engine.h"

Confetti::Confetti(int type)
	: type(type)
{
}

Confetti::~Confetti()
{
}

void Confetti::OnStart()
{
	float size = RandomGenerator::GetInstance()->GetFloat(0.2f, 0.5f);

	transform = GetComponent<Transform>()
		->SetAnchor(32, 32)
		->SetScale(size, size)
		->SetIsRelative(false);
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Effects/confetti.png");
	spriteRenderer->SetZ_index(6);

	effect = AttachComponent<Effect>();

	if (type == 0)
	{
		float angle = RandomGenerator::GetInstance()->GetFloat(30, 85);
		float speed = RandomGenerator::GetInstance()->GetFloat(3, 12);
		velocity = Vec2F(cos(angle / 180.f * PI), sin(angle / 180.f * PI)) * speed;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f);
	}
	else if (type == 1)
	{
		float angle = RandomGenerator::GetInstance()->GetFloat(95, 150);
		float speed = RandomGenerator::GetInstance()->GetFloat(3, 12);
		velocity = Vec2F(cos(angle / 180.f * PI), sin(angle / 180.f * PI)) * speed;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f);
	}
}

void Confetti::OnUpdate()
{
	velocity.y -= RG2R_TimeM->GetDeltaTime() * 15;

	if (velocity.x > 0)
	{
		velocity.x -= RG2R_TimeM->GetDeltaTime() * 2;
		if (velocity.x < 0)
		{
			velocity.x = 0;
		}
	}
	else if (velocity.x < 0)
	{
		velocity.x += RG2R_TimeM->GetDeltaTime() * 2;
		if (velocity.x > 0)
		{
			velocity.x = 0;
		}
	}

	effect->ClearEffectInfo()
		->PushEffectInfo(new TDRotationEffectInfo(D2D1::Vector3F(velocity.x * 10, velocity.y + velocity.x * 5, velocity.y * velocity.x)));

	transform->Translate(velocity.x * RG2R_TimeM->GetDeltaTime(), velocity.y * RG2R_TimeM->GetDeltaTime());
}