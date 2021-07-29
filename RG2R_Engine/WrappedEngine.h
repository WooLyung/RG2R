#include "SceneManager.h"
#include "Scene.h"

#pragma once
class WrappedEngine
{
private:
	Scene* startScene = nullptr;
	FP setting = nullptr;

public:
	WrappedEngine& SetFirstScene(Scene*);
	WrappedEngine& SetSetting(FP);
	void Start();
};