#include "stdafx.h"
#include "Tiles.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"
#include "Effect.h"

Tiles::Tiles(int x, int y)
{
	auto transform = GetComponent<Transform>();

	upAnim = new CommandList;
	upAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		if (animTime >= 1)
		{
			animTime = 1;
			upAnim->Stop();
		}
		transform->SetPosY(-pow(animTime - 1, 2) * 14);

		}, 0);
	upAnim->SetIsLoop(true);
	commandLists.push_back(upAnim);
	upAnim->Start();

	downAnim = new CommandList;
	downAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		if (animTime >= 1)
		{
			animTime = 1;
			downAnim->Stop();
		}
		transform->SetPosY(-pow(animTime, 2) * 14);

		}, 0);
	downAnim->SetIsLoop(true);
	commandLists.push_back(downAnim);

	for (int i = 0; i < x + 2; i++)
	{
		for (int j = 0; j < y + 2; j++)
		{
			auto tile = new Object;
			tile->AttachComponent<SpriteRenderer>()
				->SetTexture("Resources/Sprites/Tiles/tile.png")
				->SetZ_index(-4);
			tile->GetComponent<Transform>()
				->SetAnchor(64, 64)
				->SetPos(i - (x + 2)/2, j - (y + 2)/2);

			AttachChild(tile);
		}
	}

	for (int i = 0; i < x; i++)
	{
		auto line1 = new Object;
		line1->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/Tiles/outline1.png")
			->SetZ_index(-3);
		line1->GetComponent<Transform>()
			->SetAnchor(64, 64)
			->SetRot(270)
			->SetPos(i - x / 2, -(y + 2) / 2);

		auto line2 = new Object;
		line2->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/Tiles/outline1.png")
			->SetZ_index(-3);
		line2->GetComponent<Transform>()
			->SetAnchor(64, 64)
			->SetRot(90)
			->SetPos(i - x / 2, (y + y % 2 + 1) / 2);

		AttachChild(line1);
		AttachChild(line2);
	}

	for (int i = 0; i < y; i++)
	{
		auto line1 = new Object;
		line1->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/Tiles/outline1.png")
			->SetZ_index(-3);
		line1->GetComponent<Transform>()
			->SetAnchor(64, 64)
			->SetRot(180)
			->SetPos((x + x % 2 + 1) / 2, i - y / 2);

		auto line2 = new Object;
		line2->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/Tiles/outline1.png")
			->SetZ_index(-3);
		line2->GetComponent<Transform>()
			->SetAnchor(64, 64)
			->SetRot(0)
			->SetPos(-(x + 2) / 2, i - y / 2);

		AttachChild(line1);
		AttachChild(line2);
	}

	auto edge1 = new Object;
	edge1->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Tiles/outline2.png")
		->SetZ_index(-3);
	edge1->GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetRot(90)
		->SetPos((x + x % 2 + 1) / 2, (y + y % 2 + 1) / 2);

	auto edge2 = new Object;
	edge2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Tiles/outline2.png")
		->SetZ_index(-3);
	edge2->GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetRot(0)
		->SetPos(-(x + 2) / 2, (y + y % 2 + 1) / 2);

	auto edge3 = new Object;
	edge3->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Tiles/outline2.png")
		->SetZ_index(-3);
	edge3->GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetRot(180)
		->SetPos((x + x % 2 + 1) / 2, -(y + 2) / 2);

	auto edge4 = new Object;
	edge4->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Tiles/outline2.png")
		->SetZ_index(-3);
	edge4->GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetRot(270)
		->SetPos(-(x + 2) / 2, -(y + 2) / 2);

	AttachChild(edge1);
	AttachChild(edge2);
	AttachChild(edge3);
	AttachChild(edge4);
}

Tiles::~Tiles()
{
}

void Tiles::Down()
{
	animTime = 0;
	downAnim->Start();
}