#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Settings.h"
#include "Math.h"
#include "ViewRenderData.h"

class ViewRenderer :
	public Renderer
{
private:
	ViewRenderData renderData;

public:
	ViewRenderer();
	~ViewRenderer();

	std::type_index GetID(void) override { return typeid(ViewRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Render(ViewRenderData&);
	void Draw();
	void Draw(ViewRenderData&);

	ViewRenderData* GetRenderData();
	ViewRenderer* SetCamera(Camera*);
	ViewRenderer* SetSize(Size2U);
	ViewRenderer* SetSizeX(UINT);
	ViewRenderer* SetSizeY(UINT);
	ViewRenderer* SetBackgroundColor(D2D1_COLOR_F);

	Camera* GetCamera();
	Size2U GetSize();
	D2D1_COLOR_F GetBackgroundColor();
};