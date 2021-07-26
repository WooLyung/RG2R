#include "stdafx.h"
#include "TextRenderer.h"
#include "Engine.h"

TextRenderer::TextRenderer()
{

}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Update()
{
}

void TextRenderer::Render()
{
	RG2R_GraphicM->PushRenderBuffer(this);
}

void TextRenderer::Render(ViewRenderData&)
{
	RG2R_GraphicM->PushViewRenderBuffer(this);
}

void TextRenderer::Draw()
{
	RG2R_GraphicM->fillBrush_->SetColor(defaultData.GetTextColor());

	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetMatrix());
	RG2R_GraphicM->GetDeviceContext()->DrawTextLayout(
		D2D1::Point2F(defaultData.GetAlignScale().x, defaultData.GetAlignScale().y),
		defaultData.GetLayout(),
		RG2R_GraphicM->fillBrush_);
}

void TextRenderer::Draw(ViewRenderData& viewRenderData)
{
	if (datas.find(viewRenderData.GetCamera()) != datas.end())
	{
		RG2R_GraphicM->fillBrush_->SetColor(datas[viewRenderData.GetCamera()].GetTextColor());

		RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetMatrix_v());
		RG2R_GraphicM->GetDeviceContext()->DrawTextLayout(
			D2D1::Point2F(datas[viewRenderData.GetCamera()].GetAlignScale().x, datas[viewRenderData.GetCamera()].GetAlignScale().y),
			datas[viewRenderData.GetCamera()].GetLayout(),
			RG2R_GraphicM->fillBrush_);
	}
	else
	{
		RG2R_GraphicM->fillBrush_->SetColor(defaultData.GetTextColor());

		RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetMatrix_v());
		RG2R_GraphicM->GetDeviceContext()->DrawTextLayout(
			D2D1::Point2F(defaultData.GetAlignScale().x, defaultData.GetAlignScale().y),
			defaultData.GetLayout(),
			RG2R_GraphicM->fillBrush_);
	}
}

LPCWSTR TextRenderer::GetFontFamily()
{
	return defaultData.GetFontFamily();
}

DWRITE_FONT_WEIGHT TextRenderer::GetWeight()
{
	return defaultData.GetWeight();
}

DWRITE_FONT_STYLE TextRenderer::GetStyle()
{
	return defaultData.GetStyle();
}

DWRITE_FONT_STRETCH TextRenderer::GetStretch()
{
	return defaultData.GetStretch();
}

Vec2F TextRenderer::GetAlignScale()
{
	return defaultData.GetAlignScale();
}

TextAlignment TextRenderer::GetAlignmentWidth()
{
	return defaultData.GetAlignmentWidth();
}

TextAlignment TextRenderer::GetAlignmentHeight()
{
	return defaultData.GetAlignmentHeight();
}

std::string TextRenderer::GetText()
{
	return defaultData.GetText();
}

float TextRenderer::GetSize()
{
	return defaultData.GetSize();
}

Color TextRenderer::GetTextColor()
{
	return defaultData.GetTextColor();
}

TextRenderer* TextRenderer::SetFontFamily(LPCWSTR str)
{
	defaultData.SetFontFamily(str);

	return this;
}

TextRenderer* TextRenderer::SetWeight(DWRITE_FONT_WEIGHT weight)
{
	defaultData.SetWeight(weight);

	return this;
}

TextRenderer* TextRenderer::SetStyle(DWRITE_FONT_STYLE style)
{
	defaultData.SetStyle(style);

	return this;
}

TextRenderer* TextRenderer::SetStretch(DWRITE_FONT_STRETCH stretch)
{
	defaultData.SetStretch(stretch);

	return this;
}

TextRenderer* TextRenderer::SetText(std::string text)
{
	defaultData.SetText(text);

	return this;
}

TextRenderer* TextRenderer::SetAlignmentWidth(TextAlignment alignment)
{
	defaultData.SetAlignmentWidth(alignment);

	return this;
}

TextRenderer* TextRenderer::SetAlignmentHeight(TextAlignment alignment)
{
	defaultData.SetAlignmentHeight(alignment);

	return this;
}

TextRenderer* TextRenderer::SetSize(float size)
{
	defaultData.SetSize(size);

	return this;
}

TextRenderer* TextRenderer::SetTextColor(Color color)
{
	defaultData.SetTextColor(color);

	return this;
}

std::map<Camera*, TextRenderData>* TextRenderer::GetDatas()
{
	return &datas;
}

TextRenderData* TextRenderer::GetDefaultData()
{
	return &defaultData;
}
