#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderData.h"
#include "ViewRenderData.h"
#include "Effect.h"
#include "Camera.h"
#include <map>

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update()
{

}

void SpriteRenderer::Render()
{
	RG2R_GraphicM->PushRenderBuffer(this);
}

void SpriteRenderer::Render(ViewRenderData&)
{
	RG2R_GraphicM->PushViewRenderBuffer(this);
}

void SpriteRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(defaultData.GetTexture()->GetBitmap());

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
			defaultData.GetTexture()->GetBitmap(),
			nullptr,
			&defaultData.GetVisibleArea(),
			defaultData.GetInterpolationMode(),
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
}

void SpriteRenderer::Draw(ViewRenderData& viewRenderData)
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix_v());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (datas.find(viewRenderData.GetCamera()) != datas.end())
	{
		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(datas[viewRenderData.GetCamera()].GetTexture()->GetBitmap());

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
				datas[viewRenderData.GetCamera()].GetTexture()->GetBitmap(),
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
			ID2D1Image* image = effect->GetOutputImage(defaultData.GetTexture()->GetBitmap());

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
				defaultData.GetTexture()->GetBitmap(),
				nullptr,
				&defaultData.GetVisibleArea(),
				defaultData.GetInterpolationMode(),
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
	}
}

std::map<Camera*, SpriteRenderData>* SpriteRenderer::GetDatas()
{
	return &datas;
}

SpriteRenderData* SpriteRenderer::GetDefaultData()
{
	return &defaultData;
}

Texture* SpriteRenderer::GetTexture()
{
	return defaultData.GetTexture();
}

Rect SpriteRenderer::GetVisibleArea()
{
	return defaultData.GetVisibleArea();
}

Rect SpriteRenderer::GetRealArea()
{
	return defaultData.GetRealArea();
}

SpriteRenderer* SpriteRenderer::SetTexture(const std::string& str)
{
	defaultData.SetTexture(str);

	return this;
}

SpriteRenderer* SpriteRenderer::SetTexture(Texture* texture)
{
	defaultData.SetTexture(texture);

	return this;
}

SpriteRenderer* SpriteRenderer::SetVisibleArea(Rect rect)
{
	defaultData.SetVisibleArea(rect);

	return this;
}

SpriteRenderer* SpriteRenderer::SetVisibleArea(float a, float b, float c, float d)
{
	defaultData.SetVisibleArea(a, b, c, d);

	return this;
}

EnlargementType SpriteRenderer::GetEnlargementType()
{
	return defaultData.GetEnlargementType();
}

SpriteRenderer* SpriteRenderer::SetEnlargementType(EnlargementType type)
{
	defaultData.SetEnlargementType(type);

	return this;
}