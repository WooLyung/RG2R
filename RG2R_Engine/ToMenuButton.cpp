#include "stdafx.h"
#include "ToMenuButton.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"
#include "SceneData.h"
#include "ChapterScene.h"
#include "MapEditData.h"
#include <Windows.h>

ToMenuButton::ToMenuButton(InGameScene* scene, StageClearObj* clearObj)
{
	this->scene = scene;
	this->clearObj = clearObj;

	GetComponent<Transform>()->SetPos(50, 50);
}

ToMenuButton::~ToMenuButton()
{
}

void ToMenuButton::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	if (MapEditData::GetInstance()->playType == 0 || MapEditData::GetInstance()->playType == 2)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Clear/toMenu.png");
	else if (MapEditData::GetInstance()->playType == 1)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Clear/toUpload.png");
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.5f, 0.5f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetIsRelative(false);

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

		if (transform->GetScale().x > 0.2f)
		{
			transform->SetScale(0.2f, 0.2f);
			changeScale->Stop();
		}
		else if (transform->GetScale().x < 0.18f)
		{
			transform->SetScale(0.18f, 0.18f);
			changeScale->Stop();
		}
		}, 0);
	changeScale->SetIsLoop(true);
}

void ToMenuButton::OnUpdate()
{
	transform->SetPos(parentTransform->GetPos() + Vec2F(0.4f, -1.4f));
	Input();

	if (changeTime >= 0)
	{
		changeTime += RG2R_TimeM->GetDeltaTime();
		if (changeTime >= 1.2f)
			RG2R_SceneM->ChangeScene(new ChapterScene, true);
	}
}

void ToMenuButton::Input()
{
	Vec2F vec = RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos()) - transform->GetPos();

	if (vec.Dot(vec) <= 0.06f)
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
				inputState = InputState::end;

				if (MapEditData::GetInstance()->playType == 1)
				{
					auto data = MapEditData::GetInstance();

					std::string arguments = "x:" + to_string(data->width)
						+ ",y:" + to_string(data->height) + ",zoom:" + to_string(data->zoom)
						+ ",text:_";
					for (auto& iter : data->gates)
					{
						std::string gate_argument = ";x:" + to_string(iter.x)
							+ ",y:" + to_string(iter.y)
							+ ",type:" + iter.type;

						if (iter.type == "battery")
							gate_argument += ",color:" + iter.color;
						if (iter.isStatic)
							gate_argument += (",isStatic:true");
						if (iter.dir != "right")
							gate_argument += ",dir:" + iter.dir;

						arguments += gate_argument;
					}

					WinExec((std::string("Resources\\Processes\\Push\\Push.exe ") + arguments).c_str(), SW_HIDE);
				}

				sizeFlag = 1;
				changeScale->Start();
				clearObj->Disappear();
				
				changeTime = 0;
			}
		}
	}
	else
	{
		if (inputState != InputState::end)
			inputState = InputState::none;
		hoverFlag = -1;
		hoverAnim->Start();

		sizeFlag = 1;
		changeScale->Start();
	}
}

Transform* ToMenuButton::GetTransform()
{
	return transform;
}

SpriteRenderer* ToMenuButton::GetSpriteRenderer()
{
	return spriteRenderer;
}