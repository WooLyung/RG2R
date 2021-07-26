#include "stdafx.h"
#include "TextRenderData.h"
#include "Engine.h"
#include <string>

TextRenderData::TextRenderData()
{
	fontFamily = Widen("¸¼Àº °íµñ").c_str();
	weight = DWRITE_FONT_WEIGHT_REGULAR;
	style = DWRITE_FONT_STYLE_NORMAL;
	stretch = DWRITE_FONT_STRETCH_NORMAL;
	text = "";
	size = 30;
	alignScale = { 0, 0 };
	alignmentWidth = ALIGN_LEFT;
	alignmentHeight = ALIGN_LEFT;
	textColor = Color(1, 1, 1, 1);

	RG2R_GraphicM->GetDwFactory()->CreateTextFormat(
		fontFamily,
		NULL,
		weight,
		style,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"ko",
		&format
	);

	RG2R_GraphicM->GetDwFactory()->CreateTextLayout(
		Widen(text).c_str(),
		Widen(text).length(),
		format,
		RG2R_GraphicM->GetDeviceContext()->GetSize().width,
		RG2R_GraphicM->GetDeviceContext()->GetSize().height,
		&layout);

	textRange = { 0, Widen(text).length() };
}

TextRenderData::~TextRenderData()
{

}

LPCWSTR TextRenderData::GetFontFamily()
{
	return fontFamily;
}

DWRITE_FONT_WEIGHT TextRenderData::GetWeight()
{
	return weight;
}

DWRITE_FONT_STYLE TextRenderData::GetStyle()
{
	return style;
}

DWRITE_FONT_STRETCH TextRenderData::GetStretch()
{
	return stretch;
}

string TextRenderData::GetText()
{
	return text;
}

IDWriteTextFormat*& TextRenderData::GetFormat()
{
	return format;
}

IDWriteTextLayout*& TextRenderData::GetLayout()
{
	return layout;
}

Vec2F TextRenderData::GetAlignScale()
{
	return alignScale;
}

TextAlignment TextRenderData::GetAlignmentWidth()
{
	return alignmentWidth;
}

TextAlignment TextRenderData::GetAlignmentHeight()
{
	return alignmentHeight;
}

float TextRenderData::GetSize()
{
	return size;
}

Color TextRenderData::GetTextColor()
{
	return textColor;
}

TextRenderData* TextRenderData::SetText(string text)
{
	this->text = text;

	if (layout != nullptr)
		layout->Release();

	RG2R_GraphicM->GetDwFactory()->CreateTextLayout(
		Widen(text).c_str(),
		Widen(text).length(),
		format,
		RG2R_GraphicM->GetDeviceContext()->GetSize().width,
		RG2R_GraphicM->GetDeviceContext()->GetSize().height,
		&layout);

	textRange = { 0, Widen(text).length() };

	SetFontFamily(fontFamily);
	SetWeight(weight);
	SetStyle(style);
	SetStretch(stretch);
	SetAlignmentWidth(alignmentWidth);
	SetAlignmentHeight(alignmentHeight);

	return this;
}

TextRenderData* TextRenderData::SetFontFamily(LPCWSTR font)
{
	this->fontFamily = font;
	layout->SetFontFamilyName(font, textRange);

	return this;
}

TextRenderData* TextRenderData::SetWeight(DWRITE_FONT_WEIGHT weight)
{
	this->weight = weight;
	layout->SetFontWeight(weight, textRange);

	return this;
}

TextRenderData* TextRenderData::SetStyle(DWRITE_FONT_STYLE style)
{
	this->style = style;
	layout->SetFontStyle(style, textRange);

	return this;
}

TextRenderData* TextRenderData::SetStretch(DWRITE_FONT_STRETCH stretch)
{
	this->stretch = stretch;
	layout->SetFontStretch(stretch, textRange);

	return this;
}

TextRenderData* TextRenderData::SetAlignmentWidth(TextAlignment alignment)
{
	this->alignmentWidth = alignment;

	if (alignment == TextAlignment::ALIGN_LEFT)
	{
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		alignScale.x = 0;
	}
	else if (alignment == TextAlignment::ALIGN_CENTER)
	{
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		alignScale.x = RG2R_GraphicM->GetDeviceContext()->GetSize().width / -2.f;
	}
	else if (alignment == TextAlignment::ALIGN_RIGHT)
	{
		layout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		alignScale.x = RG2R_GraphicM->GetDeviceContext()->GetSize().width * -1.f;
	}

	return this;
}

TextRenderData* TextRenderData::SetAlignmentHeight(TextAlignment alignment)
{
	this->alignmentHeight = alignment;

	if (alignment == TextAlignment::ALIGN_LEFT)
	{
		alignScale.y = 0;
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
	else if (alignment == TextAlignment::ALIGN_CENTER)
	{
		alignScale.y = RG2R_GraphicM->GetDeviceContext()->GetSize().height  * -0.5f;
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else if (alignment == TextAlignment::ALIGN_RIGHT)
	{
		alignScale.y = RG2R_GraphicM->GetDeviceContext()->GetSize().height  * -1.f;
		layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
	}

	return this;
}

TextRenderData* TextRenderData::SetSize(float size)
{
	this->size = size;

	if (format != nullptr)
		format->Release();

	RG2R_GraphicM->GetDwFactory()->CreateTextFormat(
		fontFamily,
		NULL,
		weight,
		style,
		stretch,
		size,
		L"ko",
		&format
	);

	if (layout != nullptr)
		layout->Release();

	RG2R_GraphicM->GetDwFactory()->CreateTextLayout(
		Widen(text).c_str(),
		Widen(text).length(),
		format,
		RG2R_GraphicM->GetDeviceContext()->GetSize().width,
		RG2R_GraphicM->GetDeviceContext()->GetSize().height,
		&layout);

	textRange = { 0, Widen(text).length() };

	SetAlignmentWidth(alignmentWidth);
	SetAlignmentHeight(alignmentHeight);

	return this;
}

TextRenderData* TextRenderData::SetTextColor(Color color)
{
	this->textColor = color;

	return this;
}