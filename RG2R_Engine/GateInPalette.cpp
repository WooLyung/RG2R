#include "stdafx.h"
#include "GateInPalette.h"
#include "Engine.h"

GateInPalette::GateInPalette()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Gates/addGate.png");
	transform = AttachComponent<Transform>()
		->SetAnchor(64, 64);

	auto battery = new Object();
	batteryOutline = battery->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Gates/battery_uncolored.png");
	battery->GetComponent<Transform>()
		->SetAnchor(64, 64);
	AttachChild(battery);
}

GateInPalette::~GateInPalette()
{
}

void GateInPalette::OnStart()
{
}

bool GateInPalette::CheckHover()
{
	Vec2F vec = RG2R_InputM->GetMousePos() - (transform->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
	if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.6f)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			return true;
		}
	}

	return false;
}

Transform* GateInPalette::GetTransform()
{
	return transform;
}

SpriteRenderer* GateInPalette::GetSpriteRenderer()
{
	return spriteRenderer;
}

void GateInPalette::Done()
{
	batteryOutline->SetIsEnable(type == "battery");
}