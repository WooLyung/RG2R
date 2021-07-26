#include "stdafx.h"
#include "BitmapRenderData.h"
#include "Engine.h"
#include "Settings.h"

BitmapRenderData::BitmapRenderData()
{
	size = Size2U(INCH_PER_DISTANCE * 4, INCH_PER_DISTANCE * 4);

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

BitmapRenderData::~BitmapRenderData()
{
}

ID2D1Bitmap1*& BitmapRenderData::GetBitmap()
{
	return bitmap;
}

Rect& BitmapRenderData::GetVisibleArea()
{
	return visibleArea;
}

BitmapRenderData* BitmapRenderData::SetBitmap(ID2D1Bitmap1* bitmap)
{
	this->bitmap = bitmap;

	return this;
}

BitmapRenderData* BitmapRenderData::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}

Size2U BitmapRenderData::GetSize()
{
	return size;
}

BitmapRenderData* BitmapRenderData::SetSize(Size2U size)
{
	if (this->size != size)
	{
		bitmap->Release();
		this->size = size;

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

BitmapRenderData* BitmapRenderData::SetSizeX(UINT x)
{
	return SetSize(Size2U(x, size.height));
}

BitmapRenderData* BitmapRenderData::SetSizeY(UINT y)
{
	return SetSize(Size2U(size.width, y));
}