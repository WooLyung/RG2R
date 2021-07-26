#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "TextRenderData.h"
#include "Camera.h"
#include "ViewRenderData.h"
#include <map>

class TextRenderData;
class ViewRenderData;

class TextRenderer :
	public Renderer
{
private:
	std::map<Camera*, TextRenderData> datas;
	TextRenderData defaultData;

public:
	TextRenderer();
	~TextRenderer();

	std::type_index GetID(void) override { return typeid(TextRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Render(ViewRenderData&);
	void Draw();
	void Draw(ViewRenderData&);

	std::map<Camera*, TextRenderData>* GetDatas();
	TextRenderData* GetDefaultData();

	LPCWSTR GetFontFamily();
	DWRITE_FONT_WEIGHT GetWeight();
	DWRITE_FONT_STYLE GetStyle();
	DWRITE_FONT_STRETCH GetStretch();
	Vec2F GetAlignScale();
	TextAlignment GetAlignmentWidth();
	TextAlignment GetAlignmentHeight();
	std::string GetText();
	float GetSize();
	Color GetTextColor();

	TextRenderer* SetFontFamily(LPCWSTR);
	TextRenderer* SetWeight(DWRITE_FONT_WEIGHT);
	TextRenderer* SetStyle(DWRITE_FONT_STYLE);
	TextRenderer* SetStretch(DWRITE_FONT_STRETCH);
	TextRenderer* SetText(std::string);
	TextRenderer* SetAlignmentWidth(TextAlignment);
	TextRenderer* SetAlignmentHeight(TextAlignment);
	TextRenderer* SetSize(float);
	TextRenderer* SetTextColor(Color);
};