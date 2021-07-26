#pragma once
#include "Camera.h"
#include "Math.h"

class Camera;

class ViewRenderData
{
private:
	Camera* targetCamera;
	ID2D1Bitmap1* bitmap;
	Size2U size;
	D2D1_COLOR_F backgroundColor;

public:
	ViewRenderData();
	~ViewRenderData();

	ViewRenderData* SetCamera(Camera*);
	ViewRenderData* SetSize(Size2U);
	ViewRenderData* SetSizeX(UINT);
	ViewRenderData* SetSizeY(UINT);
	ViewRenderData* SetBackgroundColor(D2D1_COLOR_F);
	Camera* GetCamera();
	Size2U GetSize();
	D2D1_COLOR_F GetBackgroundColor();
	ID2D1Bitmap1*& GetBitmap();
};