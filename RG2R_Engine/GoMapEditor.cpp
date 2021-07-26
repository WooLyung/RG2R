#include "stdafx.h"
#include "GoMapEditor.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "MapEditorScene.h"
#include "StageData.h"
#include "PlayerData.h"

GoMapEditor::GoMapEditor(ChapterScene* scene)
{
	this->scene = scene;
}

GoMapEditor::~GoMapEditor()
{
}

void GoMapEditor::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Chapters/map_editor.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	transform = GetComponent<Transform>()
		->SetScale(0.4f, 0.4f)
		->SetPos(3.5f * (-2), -5)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	Object* child = new Object;
	spriteRenderer_child = child->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Chapters/in.png");
	spriteRenderer_child->SetZ_index(-1);
	transform_child = child->GetComponent<Transform>()
		->SetScale(1.15f, 1.15f)
		->SetPos(0.8f, 0)
		->SetAnchor(spriteRenderer_child->GetTexture()->GetSize().width * 0.5f,
			spriteRenderer_child->GetTexture()->GetSize().height * 0.5f);
	transform_child->SetRot(0);
	AttachChild(child);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPosY(-pow(animTime - 1, 2) * 5);
		transform->SetRot(-(pow(animTime - 1, 2) + 1) * 20);

		if (animTime >= 1)
		{
			transform->SetPosY(0);
			animTime = 0;
			appearAnim->Stop();
			state = ChapterState::wait2;
		}
		}, 0);
	appearAnim->SetIsLoop(true);

	moveIn = new CommandList;
	commandLists.push_back(moveIn);
	moveIn->PushCommand([=]() {
		transform_child->SetRot(transform_child->GetRot() + RG2R_TimeM->GetDeltaTime() * inFlag * 140);

		if (transform_child->GetRot() > 25)
		{
			transform_child->SetRot(25);
			moveIn->Stop();
		}
		else if (transform_child->GetRot() < 0)
		{
			transform_child->SetRot(0);
			moveIn->Stop();
		}
		}, 0);
	moveIn->SetIsLoop(true);

	changeScale = new CommandList;
	commandLists.push_back(changeScale);
	changeScale->PushCommand([=]() {
		transform->SetScale(Vec2F(transform->GetScale()) + Vec2F(1, 1) * RG2R_TimeM->GetDeltaTime() * 0.3f * sizeFlag);

		if (transform->GetScale().x > 0.4f)
		{
			transform->SetScale(0.4f, 0.4f);
			changeScale->Stop();
		}
		else if (transform->GetScale().x < 0.38f)
		{
			transform->SetScale(0.38f, 0.38f);
			changeScale->Stop();
		}
		}, 0);
	changeScale->SetIsLoop(true);

	moveDown = new CommandList;
	commandLists.push_back(moveDown);
	moveDown->PushCommand([=]() {
		transform->Translate(0, RG2R_TimeM->GetDeltaTime() * -10);
		if (transform->GetPos().y <= -10)
			moveDown->Stop();
		}, 0);
	moveDown->SetIsLoop(true);

	goStageScene = new CommandList;
	commandLists.push_back(goStageScene);
	goStageScene->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		transform->SetRot(pow(animTime - 1, 2) * -20);
		transform_child->SetScale(transform_child->GetScale().x - RG2R_TimeM->GetDeltaTime(),
			transform_child->GetScale().y - RG2R_TimeM->GetDeltaTime());

		float dis = transform->GetPos().x - fromX;
		scene->GetMainCamera()->SetPosX((-pow(animTime - 1, 2) + 1) * dis + fromX);

		if (animTime >= 1)
		{
			RG2R_SceneM->ChangeScene(new MapEditorScene);
		}
		}, 0);
	goStageScene->SetIsLoop(true);
}

void GoMapEditor::OnUpdate()
{
	if (GoMapEditor::state == ChapterState::appear)
	{
		animTime += RG2R_TimeM->GetDeltaTime();
		appearAnim->Start();
		GoMapEditor::state = ChapterState::wait;
	}

	if (GoMapEditor::state == ChapterState::wait2
		&& scene->settingBoard->boardState == SettingBoard::BoardState::top)
		Input();
}

void GoMapEditor::Input()
{
	Vec2F vec = RG2R_InputM->GetMouseWorldPos() - transform->GetPos();

	if (vec.Dot(vec) <= 3)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE)
		{
			if (inputState == InputState::none)
			{
				inputState = InputState::hover;
				moveIn->Start();
				inFlag = 1;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			if (inputState == InputState::hover)
			{
				inputState = InputState::click;
				changeScale->Start();
				sizeFlag = -1;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (inputState == InputState::click)
			{
				changeScale->Start();
				sizeFlag = 1;
				scene->MapEditor();
			}
		}
	}
	else
	{
		inputState = InputState::none;
		moveIn->Start();
		inFlag = -1;

		changeScale->Start();
		sizeFlag = 1;
	}
}

Transform* GoMapEditor::GetTransform()
{
	return transform;
}

SpriteRenderer* GoMapEditor::GetSpriteRenderer()
{
	return spriteRenderer;
}

void GoMapEditor::MoveDown()
{
	moveDown->Start();
}

void GoMapEditor::ChangeScene()
{
	goStageScene->Start();
	animTime = 0;
	fromX = scene->GetMainCamera()->GetPos().x;
}