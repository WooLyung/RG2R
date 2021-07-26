#include "stdafx.h"
#include "SpriteRenderData.h"
#include "Engine.h"

SpriteRenderData::SpriteRenderData()
{
}

SpriteRenderData::~SpriteRenderData()
{
}

Texture* SpriteRenderData::GetTexture()
{
	return texture;
}

Rect& SpriteRenderData::GetVisibleArea()
{
	return visibleArea;
}

Rect SpriteRenderData::GetRealArea()
{
	return realArea;
}

SpriteRenderData* SpriteRenderData::SetTexture(const std::string& path)
{
	texture = RG2R_TextureM->Load(path);
	visibleArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);
	realArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);

	return this;
}

SpriteRenderData* SpriteRenderData::SetTexture(Texture* texture)
{
	this->texture = texture;
	visibleArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);
	realArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);

	return this;
}

SpriteRenderData* SpriteRenderData::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}

SpriteRenderData* SpriteRenderData::SetVisibleArea(float a, float b, float c, float d)
{
	visibleArea = Rect(a, b, c, d);

	return this;
}

EnlargementType SpriteRenderData::GetEnlargementType()
{
	switch (enlargementType)
	{
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_ANISOTROPIC:
		return EnlargementType::ANISOTROPIC;
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_CUBIC:
		return EnlargementType::CUBIC;
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_FORCE_DWORD:
		return EnlargementType::FORCE_DWORD;
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC:
		return EnlargementType::HIGH_QUALITY_CUBIC;
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_LINEAR:
		return EnlargementType::LINEAR;
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR:
		return EnlargementType::MULTI_SAMPLE_LINEAR;
	case D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR:
		return EnlargementType::PIXEL;
	default:
		return EnlargementType::LINEAR;
	}
}

SpriteRenderData* SpriteRenderData::SetEnlargementType(EnlargementType type)
{
	switch (type)
	{
	case EnlargementType::ANISOTROPIC:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_ANISOTROPIC;
		break;
	case EnlargementType::CUBIC:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_CUBIC;
		break;
	case EnlargementType::FORCE_DWORD:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_FORCE_DWORD;
		break;
	case EnlargementType::HIGH_QUALITY_CUBIC:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC;
		break;
	case EnlargementType::LINEAR:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_LINEAR;
		break;
	case EnlargementType::MULTI_SAMPLE_LINEAR:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR;
		break;
	case EnlargementType::PIXEL:
		enlargementType = D2D1_INTERPOLATION_MODE::D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
		break;
	}

	return this;
}

D2D1_INTERPOLATION_MODE SpriteRenderData::GetInterpolationMode()
{
	return enlargementType;
}