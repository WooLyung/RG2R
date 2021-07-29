#include "SceneManager.h"
#include "Scene.h"

#pragma once
class WrappedEngine
{
private:
	Scene* startScene = nullptr;

public:
	WrappedEngine& SetFirstScene(Scene*);
	void Start();
};