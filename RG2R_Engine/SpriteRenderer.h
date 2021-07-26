#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "SpriteRenderData.h"
#include "Camera.h"
#include "ViewRenderData.h"
#include <map>

class SpriteRenderData;
class ViewRenderData;

class SpriteRenderer :
	public Renderer
{
private:
	std::map<Camera*, SpriteRenderData> datas;
	SpriteRenderData defaultData;

public:
	SpriteRenderer();
	~SpriteRenderer();

	std::type_index GetID(void) override { return typeid(SpriteRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Render(ViewRenderData&);
	void Draw();
	void Draw(ViewRenderData&);

	std::map<Camera*, SpriteRenderData>* GetDatas();
	SpriteRenderData* GetDefaultData();

	Texture* GetTexture();
	Rect GetVisibleArea();
	Rect GetRealArea();
	EnlargementType GetEnlargementType();

	SpriteRenderer* SetTexture(const std::string&);
	SpriteRenderer* SetTexture(Texture*);
	SpriteRenderer* SetVisibleArea(Rect);
	SpriteRenderer* SetVisibleArea(float, float, float, float);
	SpriteRenderer* SetEnlargementType(EnlargementType);
};