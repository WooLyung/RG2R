#pragma once
#include "Math.h"
#include "Texture.h"

class BitmapRenderData
{
private:
	ID2D1Bitmap1* bitmap;
	Rect visibleArea = { 0, 0, 0, 0 };
	Size2U size;

public:
	BitmapRenderData();
	~BitmapRenderData();

	ID2D1Bitmap1*& GetBitmap();
	Rect GetVisibleArea();
	Size2U GetSize();

	BitmapRenderData* SetBitmap(ID2D1Bitmap1*);
	BitmapRenderData* SetVisibleArea(Rect);
	BitmapRenderData* SetSize(Size2U);
	BitmapRenderData* SetSizeX(UINT);
	BitmapRenderData* SetSizeY(UINT);
};