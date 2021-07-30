#include "stdafx.h"
#include "TestScene.h"
#include "TestObject.h"
#include "Engine.h"
#include "Transform.h"

void TestScene::OnStart()
{
}

void TestScene::OnUpdate()
{
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		Object* obj = AttachObject(new TestObject);
		obj->GetComponent<Transform>()->SetPos(RG2R_InputM->GetMouseWorldPos());
	}
}