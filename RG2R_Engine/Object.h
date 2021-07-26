#pragma once
#include "Component.h"
#include "Scene.h"
#include "Camera.h"
#include "Math.h"
#include "ViewRenderData.h"
#include "CommandList.h"

class Component;
class Scene;
class Camera;
class ViewRenderData;

enum ObjectState
{
	OBJ_NONE,
	OBJ_START,
	OBJ_ALIVE,
	OBJ_DESTROY,
	OBJ_DISABLE
};

class Object
{
public:
	std::vector<CommandList*> commandLists;

private:
	void Render();
	void Render(ViewRenderData&);
	void Update();
	void UpdateBefore();

	Matrix matrix, matrix_v;
	Matrix anchor_matrix, anchor_matrix_v;
	Matrix noCameraMatrix;
	std::map<std::type_index, Component*> components;
	std::vector<Object*> childs;
	Object* parent = nullptr;
	Scene* scene = nullptr;

	ObjectState state = OBJ_NONE;
	std::string name = "";
	std::string tag = "";
	bool isFlipX = false;
	bool isFlipY = false;

	bool isFirstRender = true;
	bool isFirstUpdate = true;
	bool isEnable = true;

	friend class Scene;

public:
	Object();
	~Object();

	// 부모 관련
	void ChangeParent(Object*); // 부모 변경
	Object* DetachParent(); // 부모 해제
	Object* GetParent();
	bool IsParent(Object*); // 부모 체크

	// 자식 관련
	void DetachChild(Object*); // 자식 해제
	void AttachChild(Object*); // 자식 추가
	Object* FindChild(Object*); // 오브젝트를 찾음
	Object* FindChildByTag(std::string); // 태그에 맞는 오브젝트를 찾음
	Object* FindChildByName(std::string); // 이름에 맞는 오브젝트를 찾음
	Object* FindChildCondition(std::function<bool(Object*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Object*> FindChildsByTag(std::string); // 태그에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindChildsByName(std::string); // 이름에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindChildsCondition(std::function<bool(Object*)>); // 조건에 맞는 오브젝트들을 찾음
	bool IsChild(Object*); // 자식 체크

	// 오브젝트 관련
	std::string GetTag(); // 태그 얻기
	std::string GetName(); // 이름 얻기
	void SetTag(std::string); // 태그 설정
	void SetName(std::string); // 이름 설정
	void SetIsEnable(bool); // 활성화 상태 설정
	void Destroy(); // 오브젝트 제거
	bool GetIsEnable(); // 활성화 상태 얻기
	ObjectState GetState() { return state; }
	Matrix GetMatrix() { return matrix; }
	Matrix GetAnchorMatrix() { return anchor_matrix; }
	Matrix GetMatrix_v() { return matrix_v; }
	Matrix GetAnchorMatrix_v() { return anchor_matrix_v; }
	Matrix GetNoCameraMatrix() { return noCameraMatrix; }
	bool GetIsFlipX() { return isFlipX; }
	bool GetIsFlipY() { return isFlipY; }
	void SetIsFlipX(bool);
	void SetIsFlipY(bool);

	// 컴포넌트 관련
	template<typename T>
	T* AttachComponent(); // 컴포넌트를 추가
	template<typename T>
	void DetachComponent(); // 컴포넌트를 해제
	template<typename T>
	T* GetComponent(); // 컴포넌트 획득

	// 씬 메서드
	Scene* GetScene();
	Object* CreateObject(); // 빈 오브젝트 생성
	Object* CreateChildObject(); // 빈 자식 객체 생성
	Object* AttachObject(Object*); // 생성할 오브젝트를 지정
	Object* FindObject(Object*); // 오브젝트를 찾음
	Object* FindObjectByTag(std::string); // 태그에 맞는 오브젝트를 찾음
	Object* FindObjectByName(std::string); // 이름에 맞는 오브젝트를 찾음
	Object* FindObjectCondition(std::function<bool(Object*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Object*> FindObjectsByTag(std::string); // 태그에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindObjectsByName(std::string); // 이름에 맞는 오브젝트들을 찾음
	std::vector<Object*> FindObjectsCondition(std::function<bool(Object*)>); // 조건에 맞는 오브젝트들을 찾음
	Camera* CreateCamera(); // 빈 카메라 생성
	Camera* AttachCamera(Camera*); // 생성할 카메라를 지정
	Camera* FindCamera(Camera*); // 카메라를 찾음
	Camera* FindCameraByName(std::string); // 이름에 맞는 카메라를 찾음
	Camera* FindCameraCondition(std::function<bool(Camera*)>); // 조건에 맞는 오브젝트를 찾음
	std::vector<Camera*> FindCamerasCondition(std::function<bool(Camera*)>); // 조건에 맞는 오브젝트들을 찾음

	// 라이프사이클 메서드
	virtual void OnStart() {} // 씬의 첫 업데이트 시작시에
	virtual void OnFirstUpdate() {} // 씬의 첫 업데이트
	virtual void OnFirstUpdateBefore() {} // 씬의 첫 업데이트 이전
	virtual void OnUpdate() { } // 업데이트됐을 때
	virtual void OnUpdateBefore() {} // 업데이트 전
	virtual void OnFirstRender() {} // 첫 렌더링 됐을 때
	virtual void OnFirstRenderBefore() {} // 첫 렌더링 이전
	virtual void OnRender() {} // 렌더링 됐을 때
	virtual void OnRenderBefore() {} // 렌더링 전
	virtual void OnDestroy() {} // 객체가 삭제됐을 때

	// 이벤트 메서드
	virtual void OnAttachComponent() {} // 컴포넌트가 추가됐을 때
	virtual void OnDetachComponent() {} // 컴포넌트가 삭제됐을 때
	virtual void OnCollisionEnter() {} // 충돌했을 때
	virtual void OnCollisionStay() {} // 충돌중
	virtual void OnCollisionExit() {} // 충돌이 끝났을 때
	virtual void OnChangeName() {} // 이름 변경
	virtual void OnChangeTag() {} // 태그 변경
	virtual void OnChangeParent() {} // 부모 오브젝트 변수가 바뀌었을 떄
	virtual void OnAttachChild() {} // 자식 오브젝트 변수가 추가됐을 때
	virtual void OnDetachChild() {} // 자식 오브젝트 변수가 삭제됐을 때

	// 라이프사이클 리스너
	std::function<void()> onStartListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onFirstRenderListener = NULL;
	std::function<void()> onFirstRenderBeforeListener = NULL;
	std::function<void()> onRenderListener = NULL;
	std::function<void()> onRenderBeforeListener = NULL;
	std::function<void()> onDestroyListener = NULL;

	// 이벤트 리스너
	std::function<void()> onAttachComponentListener = NULL;
	std::function<void()> onDetachComponentListener = NULL;
	std::function<void()> onCollisionEnterListener = NULL;
	std::function<void()> onCollisionStayListener = NULL;
	std::function<void()> onCollisionExitListener = NULL;
	std::function<void()> onChangeNameListener = NULL;
	std::function<void()> onChangeTagListener = NULL;
	std::function<void()> onChangeParentListener = NULL;
	std::function<void()> onAttachChildListener = NULL;
	std::function<void()> onDetachChildListener = NULL;

	// 기타
	bool GetIsFirstRender() { return isFirstRender; }
	bool GetIsFirstUpdate() { return isFirstUpdate; }
};

template<typename T>
T* Object::AttachComponent()
{
	std::type_index i(T::GetFamilyID());
	if (components.count(i) > 0)
		delete components[i];

	T* component = new T();
	components[i] = component;
	component->owner = this;

	ApplyListener(onAttachComponentListener);
	OnAttachComponent();

	return component;
}

template<typename T>
void Object::DetachComponent(void)
{
	std::type_index i(T::GetFamilyID());
	Component* component = components[i];
	delete component;
	components.erase(i);

	ApplyListener(onDetachComponentListener);
	OnDetachComponent();
}

template<typename T>
T* Object::GetComponent(void)
{
	std::type_index i(T::GetFamilyID());
	if (components.count(i) <= 0)
		return nullptr;

	return static_cast<T*>(components[i]);
}