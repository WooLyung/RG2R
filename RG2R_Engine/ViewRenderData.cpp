#include "stdafx.h"
#include "ViewRenderData.h"
#include "Settings.h"
#include "Engine.h"

ViewRenderData::ViewRenderData()
{
	size = Size2U(INCH_PER_DISTANCE * 4, INCH_PER_DISTANCE * 4);
	SetBackgroundColor(D2D1::ColorF(BACKGROUND_COLOR));

	const D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			96.f,
			96.f
		);

	RG2R_GraphicM->GetDeviceContext()->CreateBitmap(
		size,
		nullptr,
		0,
		&bitmapProperties,
		&bitmap
	);
}

ViewRenderData::~ViewRenderData()
{
}

ViewRenderData* ViewRenderData::SetCamera(Camera* cam)
{
	targetCamera = cam;

	return this;
}

ViewRenderData* ViewRenderData::SetSize(Size2U size)
{
	if (this->size != size)
	{
		this->size = size;
		bitmap->Release();

		const D2D1_BITMAP_PROPERTIES1 bitmapProperties =
			D2D1::BitmapProperties1(
				D2D1_BITMAP_OPTIONS_TARGET,
				D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
				96.f,
				96.f
			);

		RG2R_GraphicM->GetDeviceContext()->CreateBitmap(
			size,
			nullptr,
			0,
			&bitmapProperties,
			&bitmap
		);
	}

	return this;
}

ViewRenderData* ViewRenderData::SetSizeX(UINT x)
{
	return SetSize(Size2U(x, size.height));
}

ViewRenderData* ViewRenderData::SetSizeY(UINT y)
{
	return SetSize(Size2U(size.width, y));
}

ViewRenderData* ViewRenderData::SetBackgroundColor(D2D1_COLOR_F color)
{
	backgroundColor = color;

	return this;
}

Camera* ViewRenderData::GetCamera()
{
	return targetCamera;
}

Size2U ViewRenderData::GetSize()
{
	return size;
}

D2D1_COLOR_F ViewRenderData::GetBackgroundColor()
{
	return backgroundColor;
}

ID2D1Bitmap1*& ViewRenderData::GetBitmap()
{
	return bitmap;
}