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

	virtual void OnStart() {} // ������Ʈ�� ù ������Ʈ ���۽ÿ�
	virtual void OnFirstUpdate() {} // ������Ʈ�� ù ������Ʈ
	virtual void OnFirstUpdateBefore() {} // ������Ʈ�� ù ������Ʈ ����
	virtual void OnUpdate() {} // ������Ʈ���� ��
	virtual void OnUpdateBefore() {} // ������Ʈ ��
	virtual void OnDestroy() {} // ��ü�� �������� ��

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