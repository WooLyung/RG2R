#include "stdafx.h"
#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
	ApplyListener(onDestroyListener);
	OnDestroy();
}

void Component::SetIsEnable(bool flag)
{
	this->isEnable = flag;
}

bool Component::GetIsEnable()
{
	return isEnable;
}

bool Component::GetIsFirstUpdate()
{
	return isFirstUpdate;
}

Object* Component::GetOwner()
{
	return owner;
}