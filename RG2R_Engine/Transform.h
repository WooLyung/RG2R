#pragma once
#include "Component.h"
#include "ViewRenderData.h"

class ViewRenderData;

class Transform :
	public Component
{
private:
	Vec2F pos = { 0, 0 };
	Vec2F scale = { 1, 1 };
	float rot = 0;

	Vec2F anchor = { 0, 0 };

	bool isRelative = true;

public:
	Transform();
	~Transform();

	std::type_index GetID(void) { return typeid(Transform); }
	static std::type_index GetFamilyID(void) { return typeid(Transform); }

	void Update();
	void Render();
	void Render(ViewRenderData&);

	Vec2F GetPos();
	Vec2F GetWorldPos();
	Vec2F GetScreenPos();
	Vec2F GetScale();
	Vec2F GetAnchor();
	float GetRot();
	bool GetIsRelative();

	Transform* SetPos(Vec2F);
	Transform* SetScale(Vec2F);
	Transform* SetAnchor(Vec2F);
	Transform* SetPos(float, float);
	Transform* SetScale(float, float);
	Transform* SetAnchor(float, float);
	Transform* SetRot(float);
	Transform* SetPosX(float);
	Transform* SetPosY(float);
	Transform* SetScaleX(float);
	Transform* SetScaleY(float);
	Transform* SetAnchorX(float);
	Transform* SetAnchorY(float);
	Transform* SetIsRelative(bool);

	Transform* Translate(float, float);
	Transform* Translate(Vec2F);
	Transform* Rotate(float);
};