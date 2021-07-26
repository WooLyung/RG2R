#pragma once
#include "Scene.h"
#include "Math.h"

class Scene;

class Camera
{
private:
	Scene* scene = nullptr;
	std::string name = "";
	bool isMain = false;
	bool isFlipX = false;
	bool isFlipY = false;

	Vec2F pos = { 0, 0 };
	Vec2F zoom = { 1, 1 };
	float rot = 0;

	void Update();

	friend class Scene;

public:
	Camera();
	~Camera();

	std::string GetName(); // 이름 얻기
	Scene* GetScene(); // 씬 얻기

	Vec2F GetPos();
	Vec2F GetZoom();
	float GetRot();
	Size2F GetCameraSize();
	Size2F GetCameraDefaultSize();

	Camera* SetPos(Vec2F);
	Camera* SetPos(float, float);
	Camera* SetZoom(Vec2F);
	Camera* SetZoom(float, float);
	Camera* SetRot(float);
	Camera* SetPosX(float);
	Camera* SetPosY(float);
	Camera* SetZoomX(float);
	Camera* SetZoomY(float);
	Camera* SetIsFlipX(bool);
	Camera* SetIsFlipY(bool);
	Camera* Translate(Vec2F);
	Camera* Translate(float, float);
	Camera* Rotate(float);

	bool GetIsMain() { return isMain; }
	bool GetIsFlipX() { return isFlipX; }
	bool GetIsFlipY() { return isFlipY; }
};