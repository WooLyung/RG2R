#include "stdafx.h"
#include "StageChoice.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "MapEditData.h"
#include "PlayerData.h"

StageChoice::StageChoice(int Stage, std::string path, StageScene* scene, Vec2F pos)
{
	this->stage = Stage;
	this->path = path;
	this->scene = scene;
	this->toPos = pos;
}

StageChoice::~StageChoice()
{
}

void StageChoice::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture(path)
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-2);
	transform = GetComponent<Transform>()
		->SetScale(0.3f, 0.3f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	if (!(PlayerData::GetInstance()->chapter > StageData::GetInstance()->chapter
		|| PlayerData::GetInstance()->chapter == StageData::GetInstance()->chapter
		&& PlayerData::GetInstance()->stage >= stage))
	{
		Object* child = new Object;
		lock = child;
		auto spr = child->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/UIs/Stages/stageLock.png");
		spr->SetZ_index(3);
		child->GetComponent<Transform>()
			->SetScale(0.8f, 0.8f)
			->SetPos(0, 1.2f)
			->SetAnchor(spr->GetTexture()->GetSize().width * 0.5f,
				spr->GetTexture()->GetSize().height * 0.5f);
		AttachChild(child);
	}

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.5f;
		transform->SetPos((1 - pow(animTime - 1, 2)) * 1 * toPos);

		if (animTime >= 1)
		{
			transform->SetPos(toPos);
			animTime = 0;
			appearAnim->Stop();
			state = StageState::wait2;
		}
		}, 0);
	appearAnim->SetIsLoop(true);

	hoverAnim = new CommandList;
	commandLists.push_back(hoverAnim);
	hoverAnim->PushCommand([=]() {
		transform->SetRot(transform->GetRot() + RG2R_TimeM->GetDeltaTime() * hoverFlag * 100);

		if (transform->GetRot() > 8)
		{
			transform->SetRot(8);
			hoverAnim->Stop();
		}
		else if (transform->GetRot() < 0)
		{
			transform->SetRot(0);
			hoverAnim->Stop();
		}
		}, 0);
	hoverAnim->SetIsLoop(true);

	changeScale = new CommandList;
	commandLists.push_back(changeScale);
	changeScale->PushCommand([=]() {
		transform->SetScale(Vec2F(transform->GetScale()) + Vec2F(1, 1) * RG2R_TimeM->GetDeltaTime() * 0.3f * sizeFlag);

		if (transform->GetScale().x > 0.3f)
		{
			transform->SetScale(0.3f, 0.3f);
			changeScale->Stop();
		}
		else if (transform->GetScale().x < 0.28f)
		{
			transform->SetScale(0.28f, 0.28f);
			changeScale->Stop();
		}
		}, 0);
	changeScale->SetIsLoop(true);

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.f;
		transform->SetPos((pow(animTime - 1, 2)) * 1 * -toPos);

		if (animTime >= 1)
		{
			transform->SetPos(0, 0);
			animTime = 0;
			disappearAnim->Stop();
			state = StageState::disappear;
			spriteRenderer->SetIsEnable(false);
			if (lock != nullptr)
				lock->SetIsEnable(false);
		}
		}, 0);
	disappearAnim->SetIsLoop(true);
}

void StageChoice::OnUpdate()
{
	if (StageChoice::state == StageChoice::appear)
	{
		animTime += RG2R_TimeM->GetDeltaTime();
		if (animTime >= 0.12f * stage)
		{
			state = StageChoice::wait;
			animTime = 0;
			appearAnim->Start();
		}
	}

	if (PlayerData::GetInstance()->chapter > StageData::GetInstance()->chapter
		|| PlayerData::GetInstance()->chapter == StageData::GetInstance()->chapter
		&& PlayerData::GetInstance()->stage >= stage)
	{
		if (state == StageState::wait2)
		{
			Input();
		}
	}
}

void StageChoice::Input()
{
	Vec2F vec = RG2R_InputM->GetMouseWorldPos() - transform->GetPos();

	if (vec.Dot(vec) <= 0.6f)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE)
		{
			if (inputState == InputState::none)
			{
				inputState = InputState::hover;
				hoverFlag = 1;
				hoverAnim->Start();
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			if (inputState == InputState::hover)
			{
				inputState = InputState::click;
				sizeFlag = -1;
				changeScale->Start();
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (inputState == InputState::click)
			{
				StageData::GetInstance()->stage = stage;
				MapEditData::GetInstance()->playType = 0;
				sizeFlag = 1;
				changeScale->Start();
				scene->ChoiceStage();
			}
		}
	}
	else
	{
		inputState = InputState::none;
		hoverFlag = -1;
		hoverAnim->Start();

		sizeFlag = 1;
		changeScale->Start();
	}
}

Transform* StageChoice::GetTransform()
{
	return transform;
}

SpriteRenderer* StageChoice::GetSpriteRenderer()
{
	return spriteRenderer;
}

void StageChoice::Disappear()
{
	appearAnim->Stop();
	disappearAnim->Start();
}