#include "stdafx.h"
#include "TestScene.h"
#include "TestObject.h"

void TestScene::OnStart()
{
	AttachObject(new TestObject);
}