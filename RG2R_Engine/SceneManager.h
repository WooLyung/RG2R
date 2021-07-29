#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "ViewRenderData.h"

class Scene;
class ViewRenderData;

class SceneManager
{
private:
	Scene* registeredScene = nullptr;
	Scene* nextScene = nullptr;
	std::vector<Scene*>* scenes = nullptr;
	std::vector<Scene*>* deletedScenes = nullptr;
	void* data;

public:
	SceneManager(Scene* scene);
	~SceneManager();

	void Update();
	void Render();
	void Render(ViewRenderData&);

	void* GetData();

	Scene* FirstScene();
	Scene* ChangeScene(Scene*); // 씬을 바꿈
	Scene* ChangeScene(Scene*, bool); // 씬을 바꾸고, 기존의 씬을 삭제
	Scene* ChangeScene(Scene*, void*); // 씬을 바꾸고, 데이터를 저장함
	Scene* ChangeScene(Scene*, bool, void*); // 씬을 바꾸고, 기존의 씬을 삭제하고, 데이터를 저장함
	Scene* DeleteScene(Scene*); // 씬을 메모리에서 지움

	std::vector<Scene*>* GetScenes() { return scenes; }
	Scene* GetScene() { return registeredScene; };
};