#pragma once
#include "Object.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ViewRenderData.h"
#include "Math.h"

class SceneManager;
class Camera;
class Object;
class ViewRenderData;

enum SceneState
{
	SCENE_UNREGISTERED,
	SCENE_START,
	SCENE_ALIVE
};

class Scene
{
private:
	void Render(); // ������
	void Render(ViewRenderData&);
	void Update(); // ������Ʈ
	void UpdateBefore(); // ������Ʈ ��

	std::vector<Object*> objects; // �� ���� ������Ʈ
	std::vector<Object*> destroyed; // ������ ������Ʈ
	std::vector<Camera*> cameras; // �� ���� ī�޶�
	Camera* mainCamera = nullptr;

	Matrix matrix, matrix_v;
	Matrix defaultMatrix, defaultMatrix_v;
	SceneState state = SCENE_UNREGISTERED;
	bool isFirstRender = true;
	bool isFirstUpdate = true;
	bool isFirstRegister = true;

	friend class SceneManager;

public:
	Scene();
	~Scene();

	// ������Ʈ ���� �޼���
	Object* CreateObject(); // �� ������Ʈ ����
	Object* AttachObject(Object*); // ������ ������Ʈ�� ����
	void DestroyObject(Object*); // ������Ʈ ����
	Object* FindObject(Object*); // ������Ʈ�� ã��
	Object* FindObjectByTag(std::string); // �±׿� �´� ������Ʈ�� ã��
	Object* FindObjectByName(std::string); // �̸��� �´� ������Ʈ�� ã��
	Object* FindObjectCondition(std::function<bool(Object*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Object*> FindObjectsByTag(std::string); // �±׿� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsByName(std::string); // �̸��� �´� ������Ʈ���� ã��
	std::vector<Object*> FindObjectsCondition(std::function<bool(Object*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ī�޶� ���� �޼���
	Camera* CreateCamera(); // �� ī�޶� ����
	Camera* AttachCamera(Camera*); // ������ ī�޶� ����
	Camera* FindCamera(Camera*); // ī�޶� ã��
	Camera* FindCameraByName(std::string); // �̸��� �´� ī�޶� ã��
	Camera* FindCameraCondition(std::function<bool(Camera*)>); // ���ǿ� �´� ������Ʈ�� ã��
	std::vector<Camera*> FindCamerasCondition(std::function<bool(Camera*)>); // ���ǿ� �´� ������Ʈ���� ã��

	// ����������Ŭ ������
	std::function<void()> onStartListener = NULL;
	std::function<void()> onFirstRegisterListener = NULL;
	std::function<void()> onRegisterListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onFirstRenderListener = NULL;
	std::function<void()> onFirstRenderBeforeListener = NULL;
	std::function<void()> onRenderListener = NULL;
	std::function<void()> onRenderBeforeListener = NULL;
	std::function<void()> onFinishListener = NULL;
	std::function<void()> onDestroyListener = NULL;

	// ����������Ŭ �޼���
	virtual void OnStart() {} // ���� ù ������Ʈ ���۽ÿ�
	virtual void OnFirstRegister() {} // ���� ó�� ��ω��� ��
	virtual void OnRegister() {} // ���� ��ω��� ��
	virtual void OnFirstUpdate() {} // ���� ù ������Ʈ
	virtual void OnFirstUpdateBefore() {} // ���� ù ������Ʈ ����
	virtual void OnUpdate() {} // ������Ʈ���� ��
	virtual void OnUpdateBefore() {} // ������Ʈ ��
	virtual void OnFirstRender() {} // ù ������ ���� ��
	virtual void OnFirstRenderBefore() {} // ù ������ ����
	virtual void OnRender() {} // ������ ���� ��
	virtual void OnRenderBefore() {} // ������ ��
	virtual void OnFinish() {} // ���� ����� Ǯ���� ��
	virtual void OnDestroy() {} // ��ü�� �������� ��

	// ��Ÿ
	bool GetIsFirstRender() { return isFirstRender; }
	bool GetIsFirstUpdate() { return isFirstUpdate; }
	bool GetIsFirstRegister() { return isFirstRegister; }
	SceneState GetState() { return state; }
	Camera* GetMainCamera() { return mainCamera; }
	Matrix GetMatrix() { return matrix; }
	Matrix GetDefaultMatrix() { return defaultMatrix; }
	Matrix GetMatrix_v() { return matrix_v; }
	Matrix GetDefaultMatrix_v() { return defaultMatrix_v; }
};