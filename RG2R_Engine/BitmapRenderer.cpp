#include "stdafx.h"
#include "BitmapRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "BitmapRenderData.h"
#include "ViewRenderData.h"
#include "Effect.h"
#include "Camera.h"
#include <map>

BitmapRenderer::BitmapRenderer()
{
}

BitmapRenderer::~BitmapRenderer()
{
}

void BitmapRenderer::Update()
{

}

void BitmapRenderer::Render()
{
	RG2R_GraphicM->PushRenderBuffer(this);
}

void BitmapRenderer::Render(ViewRenderData&)
{
	RG2R_GraphicM->PushViewRenderBuffer(this);
}

void BitmapRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(defaultData.GetBitmap());

		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			image,
			nullptr,
			&defaultData.GetVisibleArea(),
			D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
	else
	{
		RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
			defaultData.GetBitmap(),
			nullptr,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			&defaultData.GetVisibleArea());
	}
}

void BitmapRenderer::Draw(ViewRenderData& viewRenderData)
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix_v());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (datas.find(viewRenderData.GetCamera()) != datas.end())
	{
		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(datas[viewRenderData.GetCamera()].GetBitmap());

			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				image,
				nullptr,
				&datas[viewRenderData.GetCamera()].GetVisibleArea(),
				D2D1_INTERPOLATION_MODE_LINEAR,
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
		else
		{
			RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
				datas[viewRenderData.GetCamera()].GetBitmap(),
				nullptr,
				1.f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				&datas[viewRenderData.GetCamera()].GetVisibleArea());
		}
	}
	else
	{
		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(defaultData.GetBitmap());

			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				image,
				nullptr,
				&defaultData.GetVisibleArea(),
				D2D1_INTERPOLATION_MODE_LINEAR,
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
		else
		{
			RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
				defaultData.GetBitmap(),
				nullptr,
				1.f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				&defaultData.GetVisibleArea());
		}
	}
}

std::map<Camera*, BitmapRenderData>* BitmapRenderer::GetDatas()
{
	return &datas;
}

BitmapRenderData* BitmapRenderer::GetDefaultData()
{
	return &defaultData;
}

ID2D1Bitmap1* BitmapRenderer::GetBitmap()
{
	return defaultData.GetBitmap();
}

Rect BitmapRenderer::GetVisibleArea()
{
	return defaultData.GetVisibleArea();
}

BitmapRenderer* BitmapRenderer::SetBitmap(ID2D1Bitmap1* bitmap)
{
	defaultData.SetBitmap(bitmap);

	return this;
}

BitmapRenderer* BitmapRenderer::SetVisibleArea(Rect rect)
{
	defaultData.SetVisibleArea(rect);

	return this;
}

Size2U BitmapRenderer::GetSize()
{
	return defaultData.GetSize();
}

BitmapRenderer* BitmapRenderer::SetSize(Size2U size)
{
	defaultData.SetSize(size);

	return this;
}

BitmapRenderer* BitmapRenderer::SetSizeX(UINT x)
{
	defaultData.SetSizeX(x);

	return this;
}

BitmapRenderer* BitmapRenderer::SetSizeY(UINT y)
{
	defaultData.SetSizeX(y);

	return this;
}