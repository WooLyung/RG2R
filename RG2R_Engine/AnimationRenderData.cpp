#include "stdafx.h"
#include "AnimationRenderData.h"
#include "Engine.h"

AnimationRenderData::AnimationRenderData()
{
}

AnimationRenderData::~AnimationRenderData()
{
}

Rect AnimationRenderData::GetVisibleArea()
{
	return visibleArea;
}

AnimationRenderData* AnimationRenderData::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}

AnimationRenderData* AnimationRenderData::SetVisibleArea(float a, float b, float c, float d)
{
	visibleArea = Rect(a, b, c, d);

	return this;
}

AnimationRenderData* AnimationRenderData::SetVisibleArea()
{
	visibleArea = Rect(0, 0, animations[0].GetTexture(0)->GetSize().width, animations[0].GetTexture(0)->GetSize().height);

	return this;
}

std::vector<Textures>* AnimationRenderData::GetAnimations()
{
	return &animations;
}

int AnimationRenderData::GetTargetAnim()
{
	return targetAnim;
}

int AnimationRenderData::GetNowIndex()
{
	return nowIndex;
}

float AnimationRenderData::GetInterval()
{
	return interval;
}

float AnimationRenderData::GetTime()
{
	return time;
}

bool AnimationRenderData::GetIsLoop()
{
	return isLoop;
}

AnimationRenderData* AnimationRenderData::SetTargetAnim(int targetAnim)
{
	this->targetAnim = targetAnim;

	return this;
}

AnimationRenderData* AnimationRenderData::SetNowIndex(int nowIndex)
{
	this->nowIndex = nowIndex;

	return this;
}

AnimationRenderData* AnimationRenderData::SetInterval(float interval)
{
	this->interval = interval;

	return this;
}

AnimationRenderData* AnimationRenderData::SetTime(float time)
{
	this->time = time;

	return this;
}

AnimationRenderData* AnimationRenderData::SetIsLoop(bool isLoop)
{
	this->isLoop = isLoop;

	return this;
}

EnlargementType AnimationRenderData::GetEnlargementType()
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

AnimationRenderData* AnimationRenderData::SetEnlargementType(EnlargementType type)
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

D2D1_INTERPOLATION_MODE AnimationRenderData::GetInterpolationMode()
{
	return enlargementType;
}