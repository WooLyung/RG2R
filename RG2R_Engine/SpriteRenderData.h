#pragma once
#include "Math.h"
#include "Texture.h"

class SpriteRenderData
{
private:
	Texture* texture;
	Rect visibleArea = { 0, 0, 0, 0 };
	Rect realArea = { 0, 0, 0, 0 };
	D2D1_INTERPOLATION_MODE enlargementType = D2D1_INTERPOLATION_MODE_LINEAR;

public:
	SpriteRenderData();
	~SpriteRenderData();

	Texture* GetTexture();
	Rect GetVisibleArea();
	Rect GetRealArea();
	EnlargementType GetEnlargementType();
	D2D1_INTERPOLATION_MODE GetInterpolationMode();

	SpriteRenderData* SetTexture(const std::string&);
	SpriteRenderData* SetTexture(Texture*);
	SpriteRenderData* SetVisibleArea(Rect);
	SpriteRenderData* SetVisibleArea(float, float, float, float);
	SpriteRenderData* SetEnlargementType(EnlargementType);
};