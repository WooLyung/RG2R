#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "SpriteRenderer.h"
#include <iostream>

Scene* SceneManager::FirstScene()
{
	return nullptr;
}

SceneManager::SceneManager()
{
	scenes = new std::vector<Scene*>;
	deletedScenes = new std::vector<Scene*>;
	ChangeScene(FirstScene());
}

SceneManager::~SceneManager()
{
	for (auto iter : *scenes)
		SafeDelete(iter);
	for (auto iter : *deletedScenes)
		SafeDelete(iter);

	SafeDelete(scenes);
	SafeDelete(deletedScenes);

	if (registeredScene != nullptr)
		SafeDelete(registeredScene);
}

void SceneManager::Update()
{
	if (nextScene != nullptr)
	{
		Scene* preScene = registeredScene;
		registeredScene = nextScene;
		nextScene = nullptr;

		if (preScene != nullptr)
		{
			preScene->state = SceneState::SCENE_UNREGISTERED;
			ApplyListener(preScene->onFinishListener);
			preScene->OnFinish();
		}

		registeredScene->state = SceneState::SCENE_START;
		if (registeredScene->GetIsFirstRegister())
		{
			ApplyListener(registeredScene->onFirstRegisterListener);
			registeredScene->OnFirstRegister();

			registeredScene->isFirstRegister = false;
		}
		ApplyListener(registeredScene->onRegisterListener);
		registeredScene->OnRegister();
	}

	for (int i = 0; i < deletedScenes->size(); i++)
	{
		delete deletedScenes->operator[](i);
	}

	deletedScenes->clear();

	if (registeredScene != nullptr)
	{
		registeredScene->UpdateBefore();

		if (registeredScene->GetIsFirstUpdate())
		{
			ApplyListener(registeredScene->onStartListener);
			registeredScene->OnStart();

			ApplyListener(registeredScene->onFirstUpdateBeforeListener);
			registeredScene->OnFirstUpdateBefore();
		}
		ApplyListener(registeredScene->onUpdateBeforeListener);
		registeredScene->OnUpdateBefore();

		registeredScene->Update();

		if (registeredScene->GetIsFirstUpdate())
		{
			ApplyListener(registeredScene->onFirstUpdateListener);
			registeredScene->OnFirstUpdate();

			registeredScene->isFirstUpdate = false;
		}
		ApplyListener(registeredScene->onUpdateListener);
		registeredScene->OnUpdate();

		registeredScene->state = SceneState::SCENE_ALIVE;
	}
}

void SceneManager::Render()
{
	if (registeredScene != nullptr)
	{
		if (registeredScene->GetIsFirstRender())
		{
			ApplyListener(registeredScene->onFirstRenderBeforeListener);
			registeredScene->OnFirstRenderBefore();
		}
		ApplyListener(registeredScene->onRenderBeforeListener);
		registeredScene->OnRenderBefore();

		registeredScene->Render();

		if (registeredScene->GetIsFirstRender())
		{
			ApplyListener(registeredScene->onFirstRenderListener);
			registeredScene->OnFirstRender();

			registeredScene->isFirstRender = false;
		}
		ApplyListener(registeredScene->onRenderListener);
		registeredScene->OnRender();
	}
}

void SceneManager::Render(ViewRenderData& viewRenderData)
{
	if (registeredScene != nullptr)
	{
		registeredScene->Render(viewRenderData);
	}
}

Scene* SceneManager::ChangeScene(Scene* newScene)
{
	nextScene = newScene;

	return nextScene;
}

Scene* SceneManager::ChangeScene(Scene* newScene, bool isDelete)
{
	nextScene = newScene;
	if (isDelete)
		deletedScenes->push_back(registeredScene);

	return nextScene;
}

Scene* SceneManager::ChangeScene(Scene* newScene, void* data)
{
	nextScene = newScene;
	this->data = data;

	return nextScene;
}

Scene* SceneManager::ChangeScene(Scene* newScene, bool isDelete, void* data)
{
	nextScene = newScene;
	this->data = data;
	if (isDelete)
		deletedScenes->push_back(registeredScene);

	return nextScene;
}

Scene* SceneManager::DeleteScene(Scene* scene)
{
	deletedScenes->push_back(scene);

	return scene;
}

void* SceneManager::GetData()
{
	return data;
}