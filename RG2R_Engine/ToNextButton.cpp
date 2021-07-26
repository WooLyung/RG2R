#include "stdafx.h"
#include "ToNextButton.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"
#include "SceneData.h"
#include "MapEditData.h"

ToNextButton::ToNextButton(InGameScene* scene, StageClearObj* clearObj)
{
	this->scene = scene;
	this->clearObj = clearObj;

	GetComponent<Transform>()->SetPos(50, 50);
}

ToNextButton::~ToNextButton()
{
}

void ToNextButton::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	if (MapEditData::GetInstance()->playType == 0 || MapEditData::GetInstance()->playType == 2)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Clear/toNext.png");
	else if(MapEditData::GetInstance()->playType == 1)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Clear/toEdit.png");

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

void ToNextButton::OnUpdate()
{
	transform->SetPos(parentTransform->GetPos() + Vec2F(-0.4f, -1.4f));
	Input();
}

void ToNextButton::Input()
{
	Vec2F vec = RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos()) - transform->GetPos();

	if (vec.Dot(vec) <= 0.06f && inputState != InputState::end)
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
			if (MapEditData::GetInstance()->playType == 0)
			{
				if (inputState == InputState::click)
				{
					inputState = InputState::end;

					if (StageData::GetInstance()->stage == 8)
					{
						StageData::GetInstance()->chapter++;
						StageData::GetInstance()->stage = 1;
					}
					else
					{
						StageData::GetInstance()->stage++;
					}

					sizeFlag = 1;
					changeScale->Start();
					clearObj->Disappear();
					scene->sceneChangeManager->Diff();
				}
			}
			else if (MapEditData::GetInstance()->playType == 1)
			{
				inputState = InputState::end;

				SceneData::GetInstance()->inGameCode = 0;
				scene->postit->Disappear();
				scene->playButton->Disappear();
				scene->resetButton->Disappear();
				scene->menuButton->Disappear();
				scene->editButton->Disappear();
				scene->tiles->Down();
				clearObj->disappearAnim->Start();
				scene->sceneChangeManager->Edit();
			}
			else if (MapEditData::GetInstance()->playType == 2)
			{
				inputState = InputState::end;

				SceneData::GetInstance()->inGameCode = 0;
				scene->postit->Disappear();
				scene->playButton->Disappear();
				scene->resetButton->Disappear();
				scene->menuButton->Disappear();
				scene->editButton->Disappear();
				scene->tiles->Down();
				clearObj->disappearAnim->Start();
				scene->sceneChangeManager->GetMap();
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

Transform* ToNextButton::GetTransform()
{
	return transform;
}

SpriteRenderer* ToNextButton::GetSpriteRenderer()
{
	return spriteRenderer;
}