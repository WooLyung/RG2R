#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "BitmapRenderData.h"
#include "Camera.h"
#include "ViewRenderData.h"
#include <map>

class BitmapRenderData;
class ViewRenderData;

class BitmapRenderer :
	public Renderer
{
private:
	std::map<Camera*, BitmapRenderData> datas;
	BitmapRenderData defaultData;

public:
	BitmapRenderer();
	~BitmapRenderer();

	std::type_index GetID(void) override { return typeid(BitmapRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Render(ViewRenderData&);
	void Draw();
	void Draw(ViewRenderData&);

	std::map<Camera*, BitmapRenderData>* GetDatas();
	BitmapRenderData* GetDefaultData();

	ID2D1Bitmap1* GetBitmap();
	Rect GetVisibleArea();
	Size2U GetSize();

	BitmapRenderer* SetBitmap(ID2D1Bitmap1*);
	BitmapRenderer* SetVisibleArea(Rect);
	BitmapRenderer* SetSize(Size2U);
	BitmapRenderer* SetSizeX(UINT);
	BitmapRenderer* SetSizeY(UINT);
};