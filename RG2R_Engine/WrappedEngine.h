#include "SceneManager.h"
#include "Scene.h"

#pragma once
class WrappedEngine
{
private:
	Scene* startScene = nullptr;
	void (*setting)() = nullptr;

public:
	WrappedEngine& SetFirstScene(Scene*);
	WrappedEngine& SetSetting(void(*)());
	void Start();
};