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
	Scene* ChangeScene(Scene*); // ���� �ٲ�
	Scene* ChangeScene(Scene*, bool); // ���� �ٲٰ�, ������ ���� ����
	Scene* ChangeScene(Scene*, void*); // ���� �ٲٰ�, �����͸� ������
	Scene* ChangeScene(Scene*, bool, void*); // ���� �ٲٰ�, ������ ���� �����ϰ�, �����͸� ������
	Scene* DeleteScene(Scene*); // ���� �޸𸮿��� ����

	std::vector<Scene*>* GetScenes() { return scenes; }
	Scene* GetScene() { return registeredScene; };
};