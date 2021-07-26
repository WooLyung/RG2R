#include "stdafx.h"
#include "Object.h"
#include "Transform.h"
#include "Settings.h"
#include "Engine.h"

Object::Object()
{
	AttachComponent<Transform>();
}

Object::~Object()
{
	ApplyListener(onDestroyListener);
	OnDestroy();

	if (childs.size() > 0)
	{
		for (auto iter : childs)
		{
			delete iter;
		}
	}
	for (auto iter : commandLists)
	{
		delete iter;
	}
	for (auto& iter : components)
	{
		delete iter.second;
	}
}

void Object::Render()
{
	Transform* transform = GetComponent<Transform>();

	matrix =
		D2D1::Matrix3x2F(isFlipX ? -1 : 1, 0, 0, isFlipY ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Scale(transform->GetScale().x, transform->GetScale().y) *
		D2D1::Matrix3x2F::Rotation(transform->GetRot()) *
		D2D1::Matrix3x2F::Translation(transform->GetPos().x * INCH_PER_DISTANCE, -transform->GetPos().y * INCH_PER_DISTANCE);

	noCameraMatrix = matrix;

	anchor_matrix = D2D1::Matrix3x2F::Translation(-transform->GetAnchor().x, -transform->GetAnchor().y) *
		matrix;

	if (transform->GetIsRelative())
	{
		if (parent)
		{
			anchor_matrix = anchor_matrix * parent->GetMatrix();
			noCameraMatrix = noCameraMatrix * parent->GetNoCameraMatrix();
			matrix = matrix * parent->GetMatrix();
		}
		else
		{
			anchor_matrix = anchor_matrix * GetScene()->GetMatrix();
			matrix = matrix * GetScene()->GetMatrix();
		}
	}
	else if (!parent)
	{
		anchor_matrix = anchor_matrix * GetScene()->GetDefaultMatrix();
		matrix = matrix * GetScene()->GetDefaultMatrix();
	}

	for (auto iter : components)
	{
		if (iter.second->GetIsEnable())
		{
			iter.second->Render();
		}
	}

	for (auto iter : childs)
	{
		if (iter->GetIsEnable())
		{
			if (iter->isFirstRender)
			{
				ApplyListener(iter->onFirstRenderBeforeListener);
				iter->OnFirstRenderBefore();
			}
			ApplyListener(iter->onRenderBeforeListener);
			iter->OnRenderBefore();

			iter->Render();

			if (iter->isFirstRender)
			{
				ApplyListener(iter->onFirstRenderListener);
				iter->OnFirstRender();

				iter->isFirstRender = false;
			}
			ApplyListener(iter->onRenderListener);
			iter->OnRender();
		}
	}
}

void Object::Render(ViewRenderData& viewRenderData)
{
	Transform* transform = GetComponent<Transform>();

	matrix_v =
		D2D1::Matrix3x2F(isFlipX ? -1 : 1, 0, 0, isFlipY ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Scale(transform->GetScale().x, transform->GetScale().y) *
		D2D1::Matrix3x2F::Rotation(transform->GetRot()) *
		D2D1::Matrix3x2F::Translation(transform->GetPos().x * INCH_PER_DISTANCE, -transform->GetPos().y * INCH_PER_DISTANCE);

	anchor_matrix_v = D2D1::Matrix3x2F::Translation(-transform->GetAnchor().x, -transform->GetAnchor().y) *
		matrix_v;

	if (transform->GetIsRelative())
	{
		if (parent)
		{
			anchor_matrix_v = anchor_matrix_v * parent->GetMatrix_v();
			matrix_v = matrix_v * parent->GetMatrix_v();
		}
		else
		{
			anchor_matrix_v = anchor_matrix_v * GetScene()->GetMatrix_v();
			matrix_v = matrix_v * GetScene()->GetMatrix_v();
		}
	}
	else if (!parent)
	{
		anchor_matrix_v = anchor_matrix_v * GetScene()->GetDefaultMatrix_v();
		matrix_v = matrix_v * GetScene()->GetDefaultMatrix_v();
	}

	for (auto iter : components)
	{
		if (iter.second->GetIsEnable())
		{
			iter.second->Render(viewRenderData);
		}
	}

	for (auto iter : childs)
	{
		if (iter->GetIsEnable())
		{
			iter->Render(viewRenderData);
		}
	}
}

void Object::UpdateBefore()
{
	for (auto iter : childs)
	{
		if (iter->GetIsEnable())
		{
			iter->UpdateBefore();

			if (iter->isFirstUpdate)
			{
				ApplyListener(iter->onStartListener);
				iter->OnStart();

				ApplyListener(iter->onFirstUpdateBeforeListener);
				iter->OnFirstUpdateBefore();
			}
			ApplyListener(iter->onUpdateBeforeListener);
			iter->OnUpdateBefore();
		}
	}
}

void Object::Update()
{
	for (auto iter : commandLists)
	{
		iter->Update();
	}

	for (auto iter : components)
	{
		if (iter.second->GetIsEnable())
		{
			iter.second->Update();

			if (iter.second->GetIsFirstUpdate())
			{
				ApplyListener(iter.second->onUpdateListener);
				iter.second->OnUpdate();

				iter.second->isFirstUpdate = false;
			}
			ApplyListener(iter.second->onUpdateListener);
			iter.second->OnUpdate();
		}
	}

	for (auto iter : childs)
	{
		if (iter->GetIsEnable())
		{
			if (iter->isFirstUpdate)
			{
				ApplyListener(iter->onStartListener);
				iter->OnStart();

				ApplyListener(iter->onFirstUpdateBeforeListener);
				iter->OnFirstUpdateBefore();
			}
			ApplyListener(iter->onUpdateBeforeListener);
			iter->OnUpdateBefore();

			iter->Update();

			if (iter->isFirstUpdate)
			{
				ApplyListener(iter->onFirstUpdateListener);
				iter->OnFirstUpdate();

				iter->isFirstUpdate = false;
			}
			ApplyListener(iter->onUpdateListener);
			iter->OnUpdate();
		}
	}
}

void Object::SetIsFlipX(bool flag)
{
	isFlipX = flag;
}

void Object::SetIsFlipY(bool flag)
{
	isFlipY = flag;
}

void Object::ChangeParent(Object* newParent)
{
	if (parent != nullptr)
	{
		parent->DetachChild(this);
	}
	newParent->AttachChild(this);

	ApplyListener(onChangeParentListener);
	OnChangeParent();
}

Object* Object::DetachParent()
{
	if (parent != nullptr)
	{
		auto tmp = parent;
		parent->DetachChild(this);

		ApplyListener(onChangeParentListener);
		OnChangeParent();

		return tmp;
	}

	return nullptr;
}

void Object::DetachChild(Object* child)
{
	if (child->GetParent() != this)
	{
		return;
	}

	child->parent = nullptr;
	for (auto iter = childs.begin(); iter < childs.end(); iter++)
	{
		if (*iter == child)
		{
			childs.erase(iter);
			break;
		}
	}

	ApplyListener(onDetachChildListener);
	OnDetachChild();
}

void Object::AttachChild(Object* child)
{
	if (child->GetParent() == this)
	{
		return;
	}

	child->parent = this;
	childs.push_back(child);

	ApplyListener(onAttachChildListener);
	OnAttachChild();
}

Object* Object::FindChild(Object* object)
{
	for (auto iter : childs)
	{
		if (iter == object)
			return iter;

		auto result = iter->FindChild(object);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Object::FindChildByTag(std::string tag)
{
	for (auto iter : childs)
	{
		if (iter->GetTag() == tag)
			return iter;

		auto result = iter->FindChildByTag(tag);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Object::FindChildByName(std::string name)
{
	for (auto iter : childs)
	{
		if (iter->GetName() == name)
			return iter;

		auto result = iter->FindChildByName(name);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Object::FindChildCondition(std::function<bool(Object*)> condition)
{
	for (auto iter : childs)
	{
		if (condition(iter))
			return iter;

		auto result = iter->FindChildCondition(condition);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

std::vector<Object*> Object::FindChildsByTag(std::string tag)
{
	std::vector<Object*> foundObjects;

	for (auto iter : childs)
	{
		if (iter->GetTag() == tag)
			foundObjects.push_back(iter);

		auto result = iter->FindChildsByTag(tag);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

std::vector<Object*> Object::FindChildsByName(std::string name)
{
	std::vector<Object*> foundObjects;

	for (auto iter : childs)
	{
		if (iter->GetName() == name)
			foundObjects.push_back(iter);

		auto result = iter->FindChildsByName(name);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

std::vector<Object*> Object::FindChildsCondition(std::function<bool(Object*)> condition)
{
	std::vector<Object*> foundObjects;

	for (auto iter : childs)
	{
		if (condition(iter))
			foundObjects.push_back(iter);

		auto result = iter->FindChildsCondition(condition);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

Object* Object::CreateObject()
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->CreateObject();
}

Object* Object::CreateChildObject()
{
	auto object = new Object();
	AttachChild(object);

	return object;
}


Object* Object::AttachObject(Object* object)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->AttachObject(object);
}

Object* Object::FindObject(Object* object)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObject(object);
}

Object* Object::FindObjectByTag(std::string tag)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObjectByTag(tag);
}

Object* Object::FindObjectByName(std::string name)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObjectByName(name);
}

Object* Object::FindObjectCondition(std::function<bool(Object*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindObjectCondition(condition);
}

std::vector<Object*> Object::FindObjectsByTag(std::string tag)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Object*>();
	}
	return scene->FindObjectsByTag(tag);
}

std::vector<Object*> Object::FindObjectsByName(std::string name)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Object*>();
	}
	return scene->FindObjectsByName(name);
}

std::vector<Object*> Object::FindObjectsCondition(std::function<bool(Object*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Object*>();
	}
	return scene->FindObjectsCondition(condition);
}

Camera* Object::CreateCamera()
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->CreateCamera();
}

Camera* Object::AttachCamera(Camera* cam)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->AttachCamera(cam);
}

Camera* Object::FindCamera(Camera* cam)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindCamera(cam);
}

Camera* Object::FindCameraByName(std::string name)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindCameraByName(name);
}

Camera* Object::FindCameraCondition(std::function<bool(Camera*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return nullptr;
	}
	return scene->FindCameraCondition(condition);
}

std::vector<Camera*> Object::FindCamerasCondition(std::function<bool(Camera*)> condition)
{
	if (scene == nullptr)
	{
		Log_error("소속된 씬이 존재하지 않는 오브젝트입니다.");
		return std::vector<Camera*>();
	}
	return scene->FindCamerasCondition(condition);
}

Scene* Object::GetScene()
{
	return scene;
}

std::string Object::GetTag()
{
	return tag;
}

std::string Object::GetName()
{
	return name;
}

void Object::SetTag(std::string tag)
{
	this->tag = tag;

	ApplyListener(onChangeTagListener);
	OnChangeTag();
}

void Object::SetName(std::string name)
{
	this->name = name;

	ApplyListener(onChangeNameListener);
	OnChangeName();
}

bool Object::IsChild(Object*)
{
	for (auto iter : childs)
	{
		if (iter->IsParent(this))
			return true;
	}

	return false;
}

bool Object::IsParent(Object* object)
{
	return object == parent;
}

void Object::Destroy()
{
	state = OBJ_DESTROY;
	DetachParent();
	RG2R_SceneM->GetScene()->DestroyObject(this);

	for (auto& child : childs)
		child->Destroy();
}

bool Object::GetIsEnable()
{
	return isEnable;
}

Object* Object::GetParent()
{
	return parent;
}

void Object::SetIsEnable(bool flag)
{
	this->isEnable = flag;

	if (flag)
	{
		state = OBJ_ALIVE;
	}
	else
	{
		state = OBJ_DISABLE;
	}
}