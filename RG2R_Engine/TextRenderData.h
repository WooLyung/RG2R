#pragma once
#include "Math.h"
#include <string>

enum TextAlignment
{
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

class TextRenderData
{
private:
	IDWriteTextFormat* format;
	IDWriteTextLayout* layout;
	DWRITE_TEXT_RANGE textRange;

	LPCWSTR fontFamily;
	DWRITE_FONT_WEIGHT weight;
	DWRITE_FONT_STYLE style;
	DWRITE_FONT_STRETCH stretch;
	std::string text;
	float size;
	Vec2F alignScale;
	TextAlignment alignmentWidth;
	TextAlignment alignmentHeight;
	Color textColor;

public:
	TextRenderData();
	~TextRenderData();

	LPCWSTR GetFontFamily();
	DWRITE_FONT_WEIGHT GetWeight();
	DWRITE_FONT_STYLE GetStyle();
	DWRITE_FONT_STRETCH GetStretch();
	std::string GetText();
	Vec2F GetAlignScale();
	TextAlignment GetAlignmentWidth();
	TextAlignment GetAlignmentHeight();
	float GetSize();
	Color GetTextColor();
	IDWriteTextFormat*& GetFormat();
	IDWriteTextLayout*& GetLayout();

	TextRenderData* SetFontFamily(LPCWSTR);
	TextRenderData* SetWeight(DWRITE_FONT_WEIGHT);
	TextRenderData* SetStyle(DWRITE_FONT_STYLE);
	TextRenderData* SetStretch(DWRITE_FONT_STRETCH);
	TextRenderData* SetText(std::string);
	TextRenderData* SetAlignmentWidth(TextAlignment);
	TextRenderData* SetAlignmentHeight(TextAlignment);
	TextRenderData* SetSize(float);
	TextRenderData* SetTextColor(Color);
};