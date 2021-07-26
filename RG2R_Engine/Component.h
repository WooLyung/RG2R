#pragma once
#include "Object.h"
#include "ViewRenderData.h"

class Object;
class ViewRenderData;

class Component
{
private:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Render(ViewRenderData&) = 0;

	bool isEnable = true;
	bool isFirstUpdate = true;
	Object* owner;

	friend class Object;

public:
	Component();
	~Component();

	virtual std::type_index GetID(void) = 0 { return typeid(Component); }
	static std::type_index GetFamilyID(void) { return typeid(Component); }

	virtual void OnStart() {} // 컴포넌트의 첫 업데이트 시작시에
	virtual void OnFirstUpdate() {} // 컴포넌트의 첫 업데이트
	virtual void OnFirstUpdateBefore() {} // 컴포넌트의 첫 업데이트 이전
	virtual void OnUpdate() {} // 업데이트됐을 때
	virtual void OnUpdateBefore() {} // 업데이트 전
	virtual void OnDestroy() {} // 객체가 삭제됐을 때

	std::function<void()> onStartListener = NULL;
	std::function<void()> onFirstUpdateListener = NULL;
	std::function<void()> onFirstUpdateBeforeListener = NULL;
	std::function<void()> onUpdateListener = NULL;
	std::function<void()> onUpdateBeforeListener = NULL;
	std::function<void()> onDestroyListener = NULL;

	void SetIsEnable(bool);
	bool GetIsEnable();
	bool GetIsFirstUpdate();
	Object* GetOwner();
};