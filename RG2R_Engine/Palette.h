#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "GateInPalette.h"
#include "MapCreateScene.h"
#include "GateF.h"
#include <vector>
#include <string>

class MapCreateScene;

class Palette :
	public Object
{
private:
	enum InputState {
		LIFT, NONE, MOVE
	};

	MapCreateScene* scene;

	Transform* transform;
	SpriteRenderer* spriteRenderer;

	std::vector<GateInPalette*> gates;
	std::vector<std::string> gateTypes;

	// animations
	float animTime = 0;
	CommandList* appearAnim;
	CommandList* disappearAnim;

	int maxPage = 1;
	int nowPage = 0;
	int nowIndex = 0;
	std::string gateData[2][6][2];
	GateF* moveGate = nullptr;

	InputState inputState = NONE;
	Object* liftGate;
	Object* liftGateOutline;

	void ChangePage();

public:
	Palette(MapCreateScene* scene);
	~Palette();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Disappear();
	void Input();
};