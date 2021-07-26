#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "AnimationRenderData.h"
#include "Camera.h"
#include "ViewRenderData.h"
#include <map>

class AnimationRenderData;
class ViewRenderData;

class AnimationRenderer :
	public Renderer
{
private:
	std::map<Camera*, AnimationRenderData> datas;
	AnimationRenderData defaultData;

public:
	AnimationRenderer();
	~AnimationRenderer();

	std::type_index GetID(void) override { return typeid(AnimationRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Render(ViewRenderData&);
	void Draw();
	void Draw(ViewRenderData&);

	std::map<Camera*, AnimationRenderData>* GetDatas();
	AnimationRenderData* GetDefaultData();

	std::vector<Textures>* GetAnimations();
	Rect GetVisibleArea();
	int GetTargetAnim();
	int GetNowIndex();
	float GetInterval();
	float GetTime();
	bool GetIsLoop();
	EnlargementType GetEnlargementType();

	AnimationRenderer* SetVisibleArea(Rect);
	AnimationRenderer* SetVisibleArea(float, float, float, float);
	AnimationRenderer* SetVisibleArea();
	AnimationRenderer* SetTargetAnim(int);
	AnimationRenderer* SetNowIndex(int);
	AnimationRenderer* SetInterval(float);
	AnimationRenderer* SetTime(float);
	AnimationRenderer* SetIsLoop(bool);
	AnimationRenderer* SetEnlargementType(EnlargementType);
};