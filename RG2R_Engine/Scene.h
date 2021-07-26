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
	void Render(); // 렌더링
	void Render(ViewRenderData&);
	void Update(); // 업데이트
	void UpdateBefore(); // 업데이트 전

	std::vector<Object*> objects; // 씬 안의 오브젝트
	std::vector<Object*> destroyed; // 삭제될 오브젝트
	std::vector<Camera*> cameras; // 씬 안의 카메라
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

	// 오브젝트 관련 메서드
	Object* CreateObject(); // 빈 오브젝트 생성
	Object* AttachObject(Object*); // 생성할 오브젝트를 지정
	void DestroyObject(Object*); // 오브젝트 제거
	Object* FindObject(Object*); // 오브젝트를 찾음
	Object* FindObjectByTag(std::string); // 태그에 맞는 오브젝트를 찾음
	Object* FindObjectByName(std::string); // 이름에 맞는 오브젝트를 찾음
	Object* FindObjectCondition(std::function<bool(Object*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Object*> FindObjectsByTag(std::string); // 태그에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindObjectsByName(std::string); // 이름에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindObjectsCondition(std::function<bool(Object*)>); // 조건에 맞는 오브젝트들을 찾음

	// 카메라 관련 메서드
	Camera* CreateCamera(); // 빈 카메라 생성
	Camera* AttachCamera(Camera*); // 생성할 카메라를 지정
	Camera* FindCamera(Camera*); // 카메라를 찾음
	Camera* FindCameraByName(std::string); // 이름에 맞는 카메라를 찾음
	Camera* FindCameraCondition(std::function<bool(Camera*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Camera*> FindCamerasCondition(std::function<bool(Camera*)>); // 조건에 맞는 오브젝트들을 찾음

	// 라이프사이클 리스너
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

	// 라이프사이클 메서드
	virtual void OnStart() {} // 씬의 첫 업데이트 시작시에
	virtual void OnFirstRegister() {} // 씬이 처음 등록됬을 때
	virtual void OnRegister() {} // 씬이 등록됬을 때
	virtual void OnFirstUpdate() {} // 씬의 첫 업데이트
	virtual void OnFirstUpdateBefore() {} // 씬의 첫 업데이트 이전
	virtual void OnUpdate() {} // 업데이트됬을 때
	virtual void OnUpdateBefore() {} // 업데이트 전
	virtual void OnFirstRender() {} // 첫 렌더링 됬을 때
	virtual void OnFirstRenderBefore() {} // 첫 렌더링 이전
	virtual void OnRender() {} // 렌더링 됬을 때
	virtual void OnRenderBefore() {} // 렌더링 전
	virtual void OnFinish() {} // 씬의 등록이 풀렸을 때
	virtual void OnDestroy() {} // 객체가 삭제됬을 때

	// 기타
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