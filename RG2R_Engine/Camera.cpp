#include "stdafx.h"
#include "Camera.h"
#include "Engine.h"
#include "Settings.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

std::string Camera::GetName()
{
	return name;
}

Scene* Camera::GetScene()
{
	return scene;
}

Vec2F Camera::GetPos()
{
	return pos;
}

Vec2F Camera::GetZoom()
{
	return zoom;
}

float Camera::GetRot()
{
	return rot;
}

Camera* Camera::SetIsFlipX(bool flag)
{
	isFlipX = flag;

	return this;
}

Camera* Camera::SetIsFlipY(bool flag)
{
	isFlipY = flag;

	return this;
}

Camera* Camera::SetPos(Vec2F pos)
{
	this->pos = pos;

	return this;
}

Camera* Camera::SetZoom(Vec2F zoom)
{
	this->zoom = zoom;

	return this;
}

Camera* Camera::SetPos(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;

	return this;
}

Camera* Camera::SetZoom(float x, float y)
{
	this->zoom.x = x;
	this->zoom.y = y;

	return this;
}

Camera* Camera::SetRot(float rot)
{
	this->rot = rot;

	return this;
}

Camera* Camera::SetPosX(float x)
{
	this->pos.x = x;

	return this;
}

Camera* Camera::SetPosY(float y)
{
	this->pos.y = y;

	return this;
}

Camera* Camera::SetZoomX(float x)
{
	this->zoom.x = x;

	return this;
}

Camera* Camera::SetZoomY(float y)
{
	this->zoom.y = y;

	return this;
}

void Camera::Update()
{

}

Size2F Camera::GetCameraDefaultSize()
{
	float diagonal = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height));

	return Size2F(RG2R_WindowM->GetSize().width * (DIAGONAL_LENGTH / diagonal), RG2R_WindowM->GetSize().height * (DIAGONAL_LENGTH / diagonal));
}

Size2F Camera::GetCameraSize()
{
	float diagonal = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height));

	return Size2F(RG2R_WindowM->GetSize().width * (DIAGONAL_LENGTH / diagonal) / zoom.x, RG2R_WindowM->GetSize().height * (DIAGONAL_LENGTH / diagonal) / zoom.y);
}

Camera* Camera::Translate(Vec2F vec)
{
	this->pos += vec;

	return this;
}

Camera* Camera::Translate(float x, float y)
{
	this->pos.x += x;
	this->pos.y += y;

	return this;
}

Camera* Camera::Rotate(float rot)
{
	this->rot += rot;

	return this;
}