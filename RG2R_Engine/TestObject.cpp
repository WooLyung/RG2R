#include "stdafx.h"
#include "TestObject.h"
#include "Engine.h"

void TestObject::OnStart()
{
	renderer = AttachComponent<SpriteRenderer>();
	transform = GetComponent<Transform>();

	renderer->SetTexture("Resources/test.png");
	transform->SetAnchor(32.f, 32.f);
}

void TestObject::OnUpdate()
{
	transform->SetRot(transform->GetRot() + 360.f * RG2R_TimeM->GetDeltaTime());

	if (RG2R_InputM->GetKeyState(KeyCode::KEY_SPACE) == KeyState::KEYSTATE_ENTER)
		Destroy();
}