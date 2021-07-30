#include "stdafx.h"
#include "TestObject.h"
#include "Engine.h"
#include "Textures.h"

void TestObject::OnStart()
{
	renderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/test.png");
	transform = GetComponent<Transform>();
	transform->SetAnchor(32, 32);

	CommandList* anim = new CommandList;
	anim->PushCommand([&]() {
		if (transform->GetRot() == 45)
		{
			transform->SetRot(45);
			anim->Stop();
		}
		else
			transform->SetRot(transform->GetRot() + 1);
		}, 0.1f);
}

void TestObject::OnUpdate()
{
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KEYSTATE_STAY)
	{

	}
	else
	{

	}
}