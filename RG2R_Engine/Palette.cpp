#include "stdafx.h"
#include "Palette.h"
#include "Engine.h"
#include "Settings.h"
#include "MapEditData.h"

Palette::Palette(MapCreateScene* scene)
{
	this->scene = scene;

	// battery
	gateData[0][0][0] = "battery";
	gateData[0][0][1] = "Resources/Sprites/Gates/battery.png";

	// light1
	gateData[0][1][0] = "light1";
	gateData[0][1][1] = "Resources/Sprites/Gates/Light/light1.png";

	// light2
	gateData[0][2][0] = "light2";
	gateData[0][2][1] = "Resources/Sprites/Gates/Light/light2.png";

	// light3
	gateData[0][3][0] = "light3";
	gateData[0][3][1] = "Resources/Sprites/Gates/Light/light3.png";

	// add_gate
	gateData[0][4][0] = "add_gate";
	gateData[0][4][1] = "Resources/Sprites/Gates/addGate.png";

	// sub_gate
	gateData[0][5][0] = "sub_gate";
	gateData[0][5][1] = "Resources/Sprites/Gates/subGate.png";

	// division_gate
	gateData[1][0][0] = "division_gate";
	gateData[1][0][1] = "Resources/Sprites/Gates/divisionGate.png";

	// reverse_gate
	gateData[1][1][0] = "reverse_gate";
	gateData[1][1][1] = "Resources/Sprites/Gates/reverseGate.png";

	// and_gate
	gateData[1][2][0] = "and_gate";
	gateData[1][2][1] = "Resources/Sprites/Gates/andGate.png";

	// diff_gate
	gateData[1][3][0] = "diff_gate";
	gateData[1][3][1] = "Resources/Sprites/Gates/diffGate.png";

	// not_division_gate
	gateData[1][4][0] = "not_division_gate";
	gateData[1][4][1] = "Resources/Sprites/Gates/notDivisionGate.png";

	// null
	gateData[1][5][0] = "null";
	gateData[1][5][1] = "Resources/Sprites/Gates/null.png";
}

Palette::~Palette()
{
}

void Palette::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/MapEditor/palette.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.65f, 0.65f)
		->SetAnchor(0, spriteRenderer->GetTexture()->GetSize().height)
		->SetIsRelative(false);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.15f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.15f);

		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			disappearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.15f - pow(animTime, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.15f);
		}, 0);
	disappearAnim->SetIsLoop(true);

	for (int i = 0; i < 6; i++)
	{
		Vec2F pos = Vec2F(spriteRenderer->GetTexture()->GetSize().width * 0.5f / INCH_PER_DISTANCE,
			spriteRenderer->GetTexture()->GetSize().height * 0.5f / INCH_PER_DISTANCE + 1.7f);
		if (i % 2)
			pos += Vec2F(spriteRenderer->GetTexture()->GetSize().width * 0.25f / INCH_PER_DISTANCE, 0);
		else
			pos -= Vec2F(spriteRenderer->GetTexture()->GetSize().width * 0.25f / INCH_PER_DISTANCE, 0);

		if (i / 2 == 1)
			pos -= Vec2F(0, 1.4f);
		else if (i / 2 == 2)
			pos -= Vec2F(0, 2.8f);

		GateInPalette* gate = new GateInPalette;
		gate->GetTransform()
			->SetPos(pos);
		gate->GetSpriteRenderer()
			->SetTexture(gateData[nowPage][i][1]);
		gate->type = gateData[nowPage][i][0];
		AttachChild(gate);
		gates.push_back(gate);
		gate->Done();
	}

	Object* pre = new Object;
	auto pre_trs = pre->GetComponent<Transform>()
	->SetScale(0.32f, 0.32f)
	->SetPos(spriteRenderer->GetTexture()->GetSize().width * 0.25f / INCH_PER_DISTANCE,
		spriteRenderer->GetTexture()->GetSize().height * 0.5f / INCH_PER_DISTANCE + 1.7f - 4);
	pre->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (pre_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.35f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				nowPage--;
				ChangePage();
			}
		}
	};
	AttachChild(pre);

	Object* next = new Object;
	auto next_trs = next->GetComponent<Transform>()
	->SetScale(0.32f, 0.32f)
	->SetPos(spriteRenderer->GetTexture()->GetSize().width * 0.75f / INCH_PER_DISTANCE,
		spriteRenderer->GetTexture()->GetSize().height * 0.5f / INCH_PER_DISTANCE + 1.7f - 4);
	next->onUpdateListener = [=]() {
		Vec2F vec = RG2R_InputM->GetMousePos() - (next_trs->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));
		if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.35f)
		{
			if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			{
				nowPage++;
				ChangePage();
			}
		}
	};
	AttachChild(next);

	liftGate = CreateObject();
	liftGate->AttachComponent<SpriteRenderer>()
	->SetTexture("Resources/Sprites/Gates/notDivisionGate.png")
	->SetIsEnable(false);
	auto trs = liftGate->GetComponent<Transform>()
	->SetAnchor(64, 64);
	liftGate->onUpdateListener = [=]() {
		trs->SetPos(RG2R_InputM->GetMouseWorldPos());
	};

	liftGateOutline = new Object();
	liftGateOutline->AttachComponent<SpriteRenderer>()
	->SetTexture("Resources/Sprites/Gates/battery_uncolored.png")
	->SetIsEnable(false);
	liftGateOutline->GetComponent<Transform>()
	->SetAnchor(64, 64);
	liftGate->AttachChild(liftGateOutline);
}

void Palette::OnUpdate()
{
	Input();
}

void Palette::Disappear()
{
	animTime = 0;
	disappearAnim->Start();
}

Transform* Palette::GetTransform()
{
	return transform;
}

SpriteRenderer* Palette::GetSpriteRenderer()
{
	return spriteRenderer;
}

void Palette::ChangePage()
{
	if (nowPage < 0)
		nowPage = 0;
	if (nowPage > maxPage)
		nowPage = maxPage;

	for (int i = 0; i < 6; i++)
	{
		auto gate = gates[i];

		gate->GetSpriteRenderer()
			->SetTexture(gateData[nowPage][i][1]);
		gate->type = gateData[nowPage][i][0];
		gate->Done();
	}
}

void Palette::Input()
{
	if (inputState == NONE)
	{
		Vec2L pos = scene->GetTilePos();
		GateF* gate = nullptr;

		for (auto& iter : scene->gates)
		{
			if (iter->pos == pos)
				gate = iter;
		}

		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			int index = -1;

			for (int i = 0; i < 6; i++)
			{
				if (gates[i]->CheckHover())
				{
					index = i;
				}
			}

			if (index != -1)
			{
				nowIndex = index;

				liftGate->GetComponent<SpriteRenderer>()
					->SetTexture(gateData[nowPage][index][1])
					->SetIsEnable(true);
				if (gateData[nowPage][index][0] == "battery")
					liftGateOutline->GetComponent<SpriteRenderer>()
					->SetIsEnable(true);

				inputState = LIFT;
			}
			else
			{
				Vec2L pos = scene->GetTilePos();
				moveGate = nullptr;

				for (auto& iter : scene->gates)
				{
					if (iter->pos == pos)
						moveGate = iter;
				}

				if (moveGate != nullptr)
				{
					inputState = MOVE;
				}
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			Vec2L pos = scene->GetTilePos();
			GateF* gate = nullptr;

			for (auto& iter : scene->gates)
			{
				if (iter->pos == pos)
					gate = iter;
			}

			if (gate != nullptr)
			{
				gate->SetIsStatic(!gate->GetIsStatic());
			}
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_E) == KeyState::KEYSTATE_ENTER)
		{
			if (gate != nullptr)
			{
				scene->gates.remove(gate);
				gate->Destroy();
			}
		}
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_R) == KeyState::KEYSTATE_ENTER)
		{
			if (gate != nullptr)
			{
				if (gate->dir == "right")
				{
					gate->dir = "down";
					gate->GetTransform()->SetRot(90);
				}
				else if (gate->dir == "down")
				{
					gate->dir = "left";
					gate->GetTransform()->SetRot(180);
				}
				else if (gate->dir == "left")
				{
					gate->dir = "up";
					gate->GetTransform()->SetRot(270);
				}
				else if (gate->dir == "up")
				{
					gate->dir = "right";
					gate->GetTransform()->SetRot(0);
				}
			}
		}

		if (gate != nullptr && gate->type == "battery")
		if (RG2R_InputM->GetMouseWheel() != 0 && inputState == InputState::NONE)
		{
			int scale = RG2R_InputM->GetMouseWheel() / 120;

			while (scale)
			{
				if (scale > 0)
				{
					scale--;

					if (gate->color == "white")
						gate->SetColor("magenta");
					else if (gate->color == "red")
						gate->SetColor("white");
					else if (gate->color == "yellow")
						gate->SetColor("red");
					else if (gate->color == "green")
						gate->SetColor("yellow");
					else if (gate->color == "cyan")
						gate->SetColor("green");
					else if (gate->color == "blue")
						gate->SetColor("cyan");
					else if (gate->color == "magenta")
						gate->SetColor("blue");
				}
				else
				{
					scale++;

					if (gate->color == "white")
						gate->SetColor("red");
					else if (gate->color == "red")
						gate->SetColor("yellow");
					else if (gate->color == "yellow")
						gate->SetColor("green");
					else if (gate->color == "green")
						gate->SetColor("cyan");
					else if (gate->color == "cyan")
						gate->SetColor("blue");
					else if (gate->color == "blue")
						gate->SetColor("magenta");
					else if (gate->color == "magenta")
						gate->SetColor("white");
				}
			}
		}
	}
	else if (inputState == LIFT
		&& RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
	{
		inputState = NONE;

		liftGate->GetComponent<SpriteRenderer>()
			->SetIsEnable(false);
		liftGateOutline->GetComponent<SpriteRenderer>()
			->SetIsEnable(false);

		Vec2L mapSize = Vec2L(MapEditData::GetInstance()->width, MapEditData::GetInstance()->height);
		Vec2L pos = scene->GetTilePos();
		
		bool canCreate = true;

		// ¸Ê ¹ÛÀÎ°¡?
		if (!(pos.x >= -mapSize.x / 2 && pos.x <= mapSize.x / 2 - !(mapSize.x % 2)
			&& pos.y >= -mapSize.y / 2 && pos.y <= mapSize.y / 2 - !(mapSize.y % 2)))
		{
			canCreate = false;
		}

		for (auto& iter : scene->gates)
		{
			if (iter->pos == pos)
				canCreate = false;
		}

		if (canCreate)
			scene->CreateGate(gateData[nowPage][nowIndex][0], gateData[nowPage][nowIndex][1], pos);
	}
	else if (inputState == MOVE)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY)
		{
			moveGate->GetTransform()->SetPos(RG2R_InputM->GetMouseWorldPos());
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			Vec2L mapSize = Vec2L(MapEditData::GetInstance()->width, MapEditData::GetInstance()->height);
			Vec2L pos = scene->GetTilePos();

			inputState = NONE;
			bool canMove = true;

			// ¸Ê ¹ÛÀÎ°¡?
			if (!(pos.x >= -mapSize.x / 2 && pos.x <= mapSize.x / 2 - !(mapSize.x % 2)
				&& pos.y >= -mapSize.y / 2 && pos.y <= mapSize.y / 2 - !(mapSize.y % 2)))
			{
				scene->gates.remove(moveGate);
				moveGate->Destroy();

				return;
			}

			for (auto& iter : scene->gates)
			{
				if (iter->pos == pos)
					canMove = false;
			}

			if (canMove)
			{
				moveGate->SetPos(pos);
			}
			else
			{
				moveGate->SetPos(moveGate->pos);
			}

			moveGate = nullptr;
		}
	}
}