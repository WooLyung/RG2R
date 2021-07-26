#include "stdafx.h"
#include "ViewRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderData.h"
#include "Effect.h"
#include "Camera.h"
#include <map>

ViewRenderer::ViewRenderer()
{
}

ViewRenderer::~ViewRenderer()
{
	renderData.GetBitmap()->Release();
}

void ViewRenderer::Update()
{

}

void ViewRenderer::Render(ViewRenderData&)
{

}

void ViewRenderer::Render()
{
	// 내장 비트맵에 출력
	RG2R_GraphicM->GetViewRenderBuffer()->clear();
	RG2R_SceneM->Render(renderData);

	RG2R_GraphicM->SetTargetBitmap(renderData.GetBitmap());
	RG2R_GraphicM->GetDeviceContext()->BeginDraw();
	RG2R_GraphicM->GetDeviceContext()->Clear(renderData.GetBackgroundColor());

	sort(RG2R_GraphicM->GetViewRenderBuffer()->begin(), RG2R_GraphicM->GetViewRenderBuffer()->end(), [](Renderer* renderer1, Renderer* renderer2) -> bool {
		return renderer1->GetZ_index() < renderer2->GetZ_index();
		});
	for_each(RG2R_GraphicM->GetViewRenderBuffer()->begin(), RG2R_GraphicM->GetViewRenderBuffer()->end(), [=](Renderer* renderer) -> void {
		renderer->Draw(renderData);
		});

	RG2R_GraphicM->GetDeviceContext()->EndDraw();

	// 실제 출력
	RG2R_GraphicM->PushRenderBuffer(this);
}

void ViewRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(renderData.GetBitmap());
		auto&& ref = Rect(0, 0, renderData.GetSize().width, renderData.GetSize().height);

		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			image,
			nullptr,
			&ref,
			D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
	else
	{
		auto&& ref = Rect(0, 0, renderData.GetSize().width, renderData.GetSize().height);
		RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
			renderData.GetBitmap(),
			nullptr,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			&ref);
	}
}

void ViewRenderer::Draw(ViewRenderData&)
{

}

ViewRenderer* ViewRenderer::SetCamera(Camera* camera)
{
	renderData.SetCamera(camera);

	return this;
}

ViewRenderer* ViewRenderer::SetSize(Size2U size)
{
	renderData.SetSize(size);

	return this;
}

ViewRenderer* ViewRenderer::SetSizeX(UINT x)
{
	renderData.SetSizeX(x);

	return this;
}

ViewRenderer* ViewRenderer::SetSizeY(UINT y)
{
	renderData.SetSizeY(y);

	return this;
}

ViewRenderer* ViewRenderer::SetBackgroundColor(D2D1_COLOR_F color)
{
	renderData.SetBackgroundColor(color);

	return this;
}

Camera* ViewRenderer::GetCamera()
{
	return renderData.GetCamera();
}

Size2U ViewRenderer::GetSize()
{
	return renderData.GetSize();
}

D2D1_COLOR_F ViewRenderer::GetBackgroundColor()
{
	return renderData.GetBackgroundColor();
}

ViewRenderData* ViewRenderer::GetRenderData()
{
	return &renderData;
}