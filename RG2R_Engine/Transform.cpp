#include "stdafx.h"
#include "Transform.h"
#include "Settings.h"
#include "ViewRenderData.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Update()
{

}

void Transform::Render()
{

}

void Transform::Render(ViewRenderData&)
{

}

Vec2F Transform::GetPos()
{
	return pos;
}

Vec2F Transform::GetScale()
{
	return scale;
}

float Transform::GetRot()
{
	return rot;
}

Vec2F Transform::GetAnchor()
{
	return anchor;
}

Transform* Transform::SetPos(Vec2F pos)
{
	this->pos = pos;

	return this;
}

Transform* Transform::SetPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;

	return this;
}


Transform* Transform::SetScale(Vec2F scale)
{
	this->scale = scale;

	return this;
}

Transform* Transform::SetScale(float x, float y)
{
	this->scale.x = x;
	this->scale.y = y;

	return this;
}


Transform* Transform::SetRot(float rot)
{
	this->rot = rot;

	return this;
}

Transform* Transform::SetPosX(float x)
{
	this->pos.x = x;

	return this;
}

Transform* Transform::SetPosY(float y)
{
	this->pos.y = y;

	return this;
}

Transform* Transform::SetScaleX(float x)
{
	this->scale.x = x;

	return this;
}

Transform* Transform::SetScaleY(float y)
{
	this->scale.y = y;

	return this;
}

Transform* Transform::SetAnchor(Vec2F anchor)
{
	this->anchor = anchor;

	return this;
}

Transform* Transform::SetAnchor(float x, float y)
{
	this->anchor.x = x;
	this->anchor.y = y;

	return this;
}

Transform* Transform::SetAnchorX(float x)
{
	this->anchor.x = x;

	return this;
}

Transform* Transform::SetAnchorY(float y)
{
	this->anchor.y = y;

	return this;
}

bool Transform::GetIsRelative()
{
	return isRelative;
}

Transform* Transform::SetIsRelative(bool isRelative)
{
	this->isRelative = isRelative;

	return this;
}

Vec2F Transform::GetWorldPos()
{
	Vec2F worldPos = Vec2F(
		GetOwner()->GetNoCameraMatrix()._31 / INCH_PER_DISTANCE,
		-GetOwner()->GetNoCameraMatrix()._32 / INCH_PER_DISTANCE
	);

	return worldPos;
}

Vec2F Transform::GetScreenPos()
{
	Vec2F screenPos = Vec2F(
		GetOwner()->GetMatrix()._31,
		GetOwner()->GetMatrix()._32
	);

	return screenPos;
}

Transform* Transform::Translate(float x, float y)
{
	this->pos.x += x;
	this->pos.y += y;

	return this;
}

Transform* Transform::Translate(Vec2F pos)
{
	this->pos += pos;

	return this;
}

Transform* Transform::Rotate(float rot)
{
	this->rot += rot;

	return this;
}