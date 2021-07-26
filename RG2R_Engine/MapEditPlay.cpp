#include "stdafx.h"
#include "MapEditPlay.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"

MapEditPlay::MapEditPlay(MapEditorScene* scene)
{
	this->scene = scene;
}

MapEditPlay::~MapEditPlay()
{
}

void MapEditPlay::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/MapEditor/mapeditor_play.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-2);
	transform = GetComponent<Transform>()
		->SetScale(0.8f, 0.8f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.5f;
		transform->SetPos((1 - pow(animTime - 1, 2)) * 1 * Vec2F(6.5f, 0));

		if (animTime >= 1)
		{
			transform->SetPos(Vec2F(6.5f, 0));
			animTime = 0;
			appearAnim->Stop();
			state = StageState::wait2;
		}
		}, 0);
	appearAnim->SetIsLoop(true);

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.f;
		transform->SetPos((pow(animTime - 1, 2)) * 1 * Vec2F(6.5f, 0));

		if (animTime >= 1)
		{
			transform->SetPos(0, 0);
			animTime = 0;
			disappearAnim->Stop();
			state = StageState::disappear;
			spriteRenderer->SetIsEnable(false);
		}
		}, 0);
	disappearAnim->SetIsLoop(true);
}

void MapEditPlay::OnUpdate()
{
	if (MapEditPlay::state == MapEditPlay::appear)
	{
		animTime += RG2R_TimeM->GetDeltaTime();
		state = MapEditPlay::wait;
		animTime = 0;
		appearAnim->Start();
	}

	Input();
}

Transform* MapEditPlay::GetTransform()
{
	return transform;
}

SpriteRenderer* MapEditPlay::GetSpriteRenderer()
{
	return spriteRenderer;
}

void MapEditPlay::Disappear()
{
	appearAnim->Stop();
	disappearAnim->Start();
}

void MapEditPlay::Input()
{
	Vec2F vec = RG2R_InputM->GetMousePos() - transform->GetScreenPos();

	if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 3.f)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE)
		{
			if (inputState == InputState::none)
			{
				inputState = InputState::hover;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			if (inputState == InputState::hover)
			{
				inputState = InputState::click;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (inputState == InputState::click)
			{
				scene->MapPlay();
			}
		}
	}
	else
	{
		inputState = InputState::none;
	}
}