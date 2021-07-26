#include "stdafx.h"
#include "MapEditCreate.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"
#include "SizeChoice.h"

MapEditCreate::MapEditCreate(MapEditorScene* scene)
{
	this->scene = scene;
}

MapEditCreate::~MapEditCreate()
{
}

void MapEditCreate::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/MapEditor/mapeditor_create.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-2);
	transform = GetComponent<Transform>()
		->SetScale(0.8f, 0.8f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.5f;
		transform->SetPos((1 - pow(animTime - 1, 2)) * 1 * Vec2F(-6.5f, 0));

		if (animTime >= 1)
		{
			transform->SetPos(Vec2F(-6.5f, 0));
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
		transform->SetPos((pow(animTime - 1, 2)) * 1 * Vec2F(-6.5f, 0));

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

	SizeChoice* s44 = new SizeChoice(Vec2L(4, 4), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_44.png", scene, Vec2F(-1.2f, 1.5f));
	SizeChoice* s55 = new SizeChoice(Vec2L(5, 5), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_55.png", scene, Vec2F(-1.2f, 0));
	SizeChoice* s66 = new SizeChoice(Vec2L(6, 6), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_66.png", scene, Vec2F(-1.2f, -1.5f));
	SizeChoice* s77 = new SizeChoice(Vec2L(7, 7), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_77.png", scene, Vec2F(-1.2f, -3.0f));
	SizeChoice* s35 = new SizeChoice(Vec2L(5, 3), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_35.png", scene, Vec2F(1.2f, 1.5f));
	SizeChoice* s46 = new SizeChoice(Vec2L(6, 4), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_46.png", scene, Vec2F(1.2f, 0));
	SizeChoice* s57 = new SizeChoice(Vec2L(7, 5), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_57.png", scene, Vec2F(1.2f, -1.5f));
	SizeChoice* s68 = new SizeChoice(Vec2L(8, 6), "Resources/Sprites/UIs/MapEditor/StageSizes/mapsize_68.png", scene, Vec2F(1.2f, -3.0f));
	AttachChild(s44);
	AttachChild(s55);
	AttachChild(s66);
	AttachChild(s77);
	AttachChild(s35);
	AttachChild(s46);
	AttachChild(s57);
	AttachChild(s68);
}

void MapEditCreate::OnUpdate()
{
	if (MapEditCreate::state == MapEditCreate::appear)
	{
		animTime += RG2R_TimeM->GetDeltaTime();
		state = MapEditCreate::wait;
		animTime = 0;
		appearAnim->Start();
	}
}

Transform* MapEditCreate::GetTransform()
{
	return transform;
}

SpriteRenderer* MapEditCreate::GetSpriteRenderer()
{
	return spriteRenderer;
}

void MapEditCreate::Disappear()
{
	appearAnim->Stop();
	disappearAnim->Start();
}