#pragma once
#include "Math.h"
#include "Texture.h"
#include "Textures.h"
#include <vector>

class AnimationRenderData
{
private:
	std::vector<Textures> animations;
	Rect visibleArea = { 0, 0, 0, 0 };
	int targetAnim = 0;
	int nowIndex = 0;
	float interval = 1;
	bool isLoop = true;
	float time = 0;
	D2D1_INTERPOLATION_MODE enlargementType = D2D1_INTERPOLATION_MODE_LINEAR;

public:
	AnimationRenderData();
	~AnimationRenderData();

	std::vector<Textures>* GetAnimations();
	Rect& GetVisibleArea();
	int GetTargetAnim();
	int GetNowIndex();
	float GetInterval();
	float GetTime();
	bool GetIsLoop();
	EnlargementType GetEnlargementType();
	D2D1_INTERPOLATION_MODE GetInterpolationMode();

	AnimationRenderData* SetVisibleArea(Rect);
	AnimationRenderData* SetVisibleArea(float, float, float, float);
	AnimationRenderData* SetVisibleArea();
	AnimationRenderData* SetTargetAnim(int);
	AnimationRenderData* SetNowIndex(int);
	AnimationRenderData* SetInterval(float);
	AnimationRenderData* SetIsLoop(bool);
	AnimationRenderData* SetTime(float);
	AnimationRenderData* SetEnlargementType(EnlargementType);
};