#include "stdafx.h"
#include "AnimationRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "AnimationRenderData.h"
#include "ViewRenderData.h"
#include "Effect.h"
#include "Camera.h"
#include <map>

AnimationRenderer::AnimationRenderer()
{
}

AnimationRenderer::~AnimationRenderer()
{
}

void AnimationRenderer::Update()
{
	for (auto& iter : datas)
	{
		auto& sec = iter.second;
		float time = sec.GetTime() + RG2R_TimeM->GetDeltaTime();

		if (time >= sec.GetInterval())
		{
			time -= sec.GetInterval();
			sec.SetNowIndex(sec.GetNowIndex() + 1);
			if (sec.GetNowIndex() >= sec.GetAnimations()->operator[](sec.GetTargetAnim()).GetSize())
			{
				if (sec.GetIsLoop())
				{
					sec.SetNowIndex(0);
				}
				else
				{
					sec.SetNowIndex(sec.GetAnimations()->operator[](sec.GetTargetAnim()).GetSize() - 1);
				}
			}
		}
		sec.SetTime(time);
	}

	auto& sec = defaultData;
	float time = sec.GetTime() + RG2R_TimeM->GetDeltaTime();

	if (time >= sec.GetInterval())
	{
		time -= sec.GetInterval();
		sec.SetNowIndex(sec.GetNowIndex() + 1);
		if (sec.GetNowIndex() >= sec.GetAnimations()->operator[](sec.GetTargetAnim()).GetSize())
		{
			if (sec.GetIsLoop())
			{
				sec.SetNowIndex(0);
			}
			else
			{
				sec.SetNowIndex(sec.GetAnimations()->operator[](sec.GetTargetAnim()).GetSize() - 1);
			}
		}
	}
	sec.SetTime(time);
}

void AnimationRenderer::Render()
{
	RG2R_GraphicM->PushRenderBuffer(this);
}

void AnimationRenderer::Render(ViewRenderData&)
{
	RG2R_GraphicM->PushViewRenderBuffer(this);
}

void AnimationRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(defaultData.GetAnimations()->operator[](defaultData.GetTargetAnim()).GetTexture(defaultData.GetNowIndex())->GetBitmap());

		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			image,
			nullptr,
			&defaultData.GetVisibleArea(),
			defaultData.GetInterpolationMode(),
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
	else
	{
		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			defaultData.GetAnimations()->operator[](defaultData.GetTargetAnim()).GetTexture(defaultData.GetNowIndex())->GetBitmap(),
			nullptr,
			&defaultData.GetVisibleArea(),
			defaultData.GetInterpolationMode(),
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
}

void AnimationRenderer::Draw(ViewRenderData& viewRenderData)
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix_v());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (datas.find(viewRenderData.GetCamera()) != datas.end())
	{
		auto& data = datas[viewRenderData.GetCamera()];

		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(data.GetAnimations()->operator[](data.GetTargetAnim()).GetTexture(data.GetNowIndex())->GetBitmap());

			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				image,
				nullptr,
				&datas[viewRenderData.GetCamera()].GetVisibleArea(),
				datas[viewRenderData.GetCamera()].GetInterpolationMode(),
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
		else
		{
			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				data.GetAnimations()->operator[](data.GetTargetAnim()).GetTexture(data.GetNowIndex())->GetBitmap(),
				nullptr,
				&datas[viewRenderData.GetCamera()].GetVisibleArea(),
				datas[viewRenderData.GetCamera()].GetInterpolationMode(),
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
	}
	else
	{
		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(defaultData.GetAnimations()->operator[](defaultData.GetTargetAnim()).GetTexture(defaultData.GetNowIndex())->GetBitmap());

			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				image,
				nullptr,
				&defaultData.GetVisibleArea(),
				defaultData.GetInterpolationMode(),
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
		else
		{
			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				defaultData.GetAnimations()->operator[](defaultData.GetTargetAnim()).GetTexture(defaultData.GetNowIndex())->GetBitmap(),
				nullptr,
				&defaultData.GetVisibleArea(),
				defaultData.GetInterpolationMode(),
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
	}
}

std::map<Camera*, AnimationRenderData>* AnimationRenderer::GetDatas()
{
	return &datas;
}

AnimationRenderData* AnimationRenderer::GetDefaultData()
{
	return &defaultData;
}

Rect AnimationRenderer::GetVisibleArea()
{
	return defaultData.GetVisibleArea();
}

std::vector<Textures>* AnimationRenderer::GetAnimations()
{
	return defaultData.GetAnimations();
}

int AnimationRenderer::GetTargetAnim()
{
	return defaultData.GetTargetAnim();
}

int AnimationRenderer::GetNowIndex()
{
	return defaultData.GetNowIndex();
}

float AnimationRenderer::GetInterval()
{
	return defaultData.GetInterval();
}

float AnimationRenderer::GetTime()
{
	return defaultData.GetTime();
}

bool AnimationRenderer::GetIsLoop()
{
	return defaultData.GetIsLoop();
}

AnimationRenderer* AnimationRenderer::SetVisibleArea()
{
	defaultData.SetVisibleArea();

	return this;
}

AnimationRenderer* AnimationRenderer::SetTargetAnim(int targetAnim)
{
	defaultData.SetTargetAnim(targetAnim);

	return this;
}

AnimationRenderer* AnimationRenderer::SetNowIndex(int nowIndex)
{
	defaultData.SetNowIndex(nowIndex);

	return this;
}

AnimationRenderer* AnimationRenderer::SetInterval(float interval)
{
	defaultData.SetInterval(interval);

	return this;
}

AnimationRenderer* AnimationRenderer::SetTime(float time)
{
	defaultData.SetTime(time);

	return this;
}

AnimationRenderer* AnimationRenderer::SetIsLoop(bool isLoop)
{
	defaultData.SetIsLoop(isLoop);

	return this;
}

AnimationRenderer* AnimationRenderer::SetVisibleArea(Rect rect)
{
	defaultData.SetVisibleArea(rect);

	return this;
}

AnimationRenderer* AnimationRenderer::SetVisibleArea(float a, float b, float c, float d)
{
	defaultData.SetVisibleArea(a, b, c, d);

	return this;
}

EnlargementType AnimationRenderer::GetEnlargementType()
{
	return defaultData.GetEnlargementType();
}

AnimationRenderer* AnimationRenderer::SetEnlargementType(EnlargementType type)
{
	defaultData.SetEnlargementType(type);

	return this;
}