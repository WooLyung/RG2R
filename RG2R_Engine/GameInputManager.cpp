#include "stdafx.h"
#include "GameInputManager.h"
#include "InGameScene.h"
#include "Engine.h"
#include "Battery.h"
#include "Effect.h"
#include "Dust.h"
#include "SettingData.h"
#include "SoundMaster.h"

GameInputManager::GameInputManager(InGameScene* scene)
{
	this->scene = scene;
}

GameInputManager::~GameInputManager()
{
}

void GameInputManager::OnUpdate()
{
	if (scene->playManager->gameState == GameState::CircuitDesign)
	{
		Input();
	}

	if (inputState == InputState::GATE_LIFT)
	{
		scene->cursor->SetSpr(1);
	}
	else if (inputState == InputState::LINE_CONNECT
		|| inputState == InputState::LINE_START)
	{
		scene->cursor->SetSpr(2);
	}
	else
	{
		scene->cursor->SetSpr(0);
	}
}

void GameInputManager::OnStart()
{
	shadow = CreateObject();
	shadow->SetIsEnable(false);

	shadow_renderer = shadow->AttachComponent<SpriteRenderer>();
	shadow_renderer->SetZ_index(4);

	shadow->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(0, 0, 0, 0.7f)))
		->PushEffectInfo(new BrightnessEffectInfo(0, 0.5f, 0.f, 0.1f))
		->PushEffectInfo(new GaussianBlurEffectInfo(1.5f));

	shadow_transform = shadow->GetComponent<Transform>()
		->SetAnchor(64, 64);
}

void GameInputManager::Input()
{
	tilePos = scene->GetTilePos();
	targetGate = nullptr;
	for (auto& iter : scene->objectManager->gates)
	{
		if (iter->tilePos.x == tilePos.x && iter->tilePos.y == tilePos.y)
		{
			targetGate = iter;
		}
	}
	
	if (targetGate != nullptr)
	{
		Input_Connect();

		if (!targetGate->GetStatic())
		{
			Input_Rotate();
			Input_Select();
			Input_Wheel();
		}
	}

	Input_Erase();
	GateMove();
	LineConnect();
}

void GameInputManager::Input_Erase()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_E) == KeyState::KEYSTATE_ENTER
		&& inputState == InputState::NONE)
	{
		if (targetGate != nullptr)
		{
			Erase(targetGate);
		}
		else
		{
			Erase(tilePos);
		}
	}
}

void GameInputManager::Erase(Gate* gate)
{
	for (auto& iter : gate->input)
	{
		Line* line = scene->objectManager->FindLine(iter + gate->tilePos);

		if (line != nullptr && line->output == iter)
			Erase(iter + gate->tilePos);
	}
	for (auto& iter : gate->output)
	{
		Line* line = scene->objectManager->FindLine(iter + gate->tilePos);

		if (line != nullptr && line->input == iter)
			Erase(iter + gate->tilePos);
	}
}

void GameInputManager::Erase(Vec2L pos)
{
	Line* me = scene->objectManager->FindLine(pos);
	Line* nowLine = me;
	Vec2L nowPos = pos;

	if (nowLine == nullptr)
		return;

	while (true) // 인풋으로 진행하면서 제거
	{
		nowPos -= nowLine->input;
		nowLine = scene->objectManager->FindLine(nowPos);

		if (nowLine == nullptr)
		{
			break;
		}

		scene->objectManager->lines.remove(nowLine);
		nowLine->Destroy();
	}

	nowLine = scene->objectManager->FindLine(pos);
	nowPos = pos;
	if (nowLine == nullptr)
		return;

	while (true) // 아웃풋으로 진행하면서 제거
	{
		nowPos -= nowLine->output;
		nowLine = scene->objectManager->FindLine(nowPos);

		if (nowLine == nullptr)
		{
			break;
		}

		scene->objectManager->lines.remove(nowLine);
		nowLine->Destroy();
	}

	me->Destroy();
	scene->objectManager->lines.remove(me);
}

void GameInputManager::Input_Rotate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_R) == KeyState::KEYSTATE_ENTER
		&& inputState == InputState::NONE)
	{
		Erase(targetGate);

		if (targetGate->GetDir() == Dir::RIGHT)
			targetGate->SetDir(Dir::DOWN);
		else if (targetGate->GetDir() == Dir::DOWN)
			targetGate->SetDir(Dir::LEFT);
		else if (targetGate->GetDir() == Dir::LEFT)
			targetGate->SetDir(Dir::UP);
		else if (targetGate->GetDir() == Dir::UP)
			targetGate->SetDir(Dir::RIGHT);

		auto& input = targetGate->input;
		auto& output = targetGate->output;

		for (int i = 0; i < input.size(); i++)
		{
			if (input[i].x == 1 && input[i].y == 0)
			{
				input[i].x = 0;
				input[i].y = -1;
			}
			else if (input[i].x == 0 && input[i].y == -1)
			{
				input[i].x = -1;
				input[i].y = 0;
			}
			else if (input[i].x == -1 && input[i].y == 0)
			{
				input[i].x = 0;
				input[i].y = 1;
			}
			else if (input[i].x == 0 && input[i].y == 1)
			{
				input[i].x = 1;
				input[i].y = 0;
			}
		}
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i].x == 1 && output[i].y == 0)
			{
				output[i].x = 0;
				output[i].y = -1;
			}
			else if (output[i].x == 0 && output[i].y == -1)
			{
				output[i].x = -1;
				output[i].y = 0;
			}
			else if (output[i].x == -1 && output[i].y == 0)
			{
				output[i].x = 0;
				output[i].y = 1;
			}
			else if (output[i].x == 0 && output[i].y == 1)
			{
				output[i].x = 1;
				output[i].y = 0;
			}
		}
	}
}

void GameInputManager::Input_Select() // 게이트 들기, 우클릭
{
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KeyState::KEYSTATE_ENTER
		&& inputState == InputState::NONE)
	{
		Erase(targetGate);
		inputState = InputState::GATE_LIFT;
		myGate = targetGate;
		myGate->GetSpriteRenderer()->SetZ_index(5);
		SoundMaster::GetInstance()->PlayEffectSound(SoundID::LIFT);
		if (SettingData::GetInstance()->effect)
		{
			for (int i = 0; i < 3; i++)
			{
				Dust* dust = new Dust;
				dust->GetComponent<Transform>()->SetPos(tilePos.x, tilePos.y);
				AttachObject(dust);
			}
		}

		shadow->SetIsEnable(true);
		shadow_renderer->SetTexture(myGate->GetSpriteRenderer()->GetTexture());
		shadow_transform->SetRot(myGate->GetTransform()->GetRot());
	}
}

void GameInputManager::Input_Connect() // 라인 연결, 좌클릭
{
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER
		&& inputState == InputState::NONE)
	{
		inputState = InputState::LINE_START;
		myGate = targetGate;
	}
}

void GameInputManager::Input_Wheel()
{
	if (targetGate != nullptr
		&& targetGate->GetID() == typeid(Battery))
	{
		if (RG2R_InputM->GetMouseWheel() != 0 && inputState == InputState::NONE)
		{
			int scale = RG2R_InputM->GetMouseWheel() / 120;

			while (scale)
			{
				if (scale > 0)
				{
					scale--;

					if (targetGate->GetColor() == Color8(1, 0, 0))
						targetGate->SetColor(Color8(0, 1, 0));
					else if (targetGate->GetColor() == Color8(0, 1, 0))
						targetGate->SetColor(Color8(0, 0, 1));
					else if (targetGate->GetColor() == Color8(0, 0, 1))
						targetGate->SetColor(Color8(1, 0, 0));
				}
				else
				{
					scale++;

					if (targetGate->GetColor() == Color8(1, 0, 0))
						targetGate->SetColor(Color8(0, 0, 1));
					else if (targetGate->GetColor() == Color8(0, 1, 0))
						targetGate->SetColor(Color8(1, 0, 0));
					else if (targetGate->GetColor() == Color8(0, 0, 1))
						targetGate->SetColor(Color8(0, 1, 0));
				}
			}
		}
	}
}

void GameInputManager::LineConnect()
{
	if (inputState == InputState::LINE_START) // 라인 연결 시작
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY) // 클릭 유지
		{
			Vec2L dirVec = tilePos - myGate->tilePos;
			if (dirVec == Vec2L(1, 0)
				|| dirVec == Vec2L(-1, 0)
				|| dirVec == Vec2L(0, 1)
				|| dirVec == Vec2L(0, -1)) // 한 칸만 옮겼을 때
			{
				directional = NO;

				for (auto& iter : myGate->input)
				{
					if (iter == dirVec)
						directional = INPUT;
				}
				for (auto& iter : myGate->output)
				{
					if (iter == dirVec)
						directional = OUTPUT;
				}

				if (directional == NO) // 인풋 혹은 아웃풋 방향이 아닐 때
				{
					CancelConnect();
				}
				else
				{
					inputState = InputState::LINE_CONNECT;
					lastLine = CreateLine(tilePos.x, tilePos.y);

					if (lastLine == nullptr) // 라인을 이을 수 없을 때
					{
						CancelConnect();
					}
				}
			}
			else if (tilePos != myGate->tilePos) // 여러 칸을 옮겼을 때 (연결 취소)
			{
				CancelConnect();
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) // 라인 연결 취소
		{
			CancelConnect();
		}
	}
	else if (inputState == InputState::LINE_CONNECT) // 라인 연결 중
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY) // 클릭 유지
		{
			Vec2L dirVec = tilePos - lastLine->tilePos;
			if (dirVec == Vec2L(1, 0)
				|| dirVec == Vec2L(-1, 0)
				|| dirVec == Vec2L(0, 1)
				|| dirVec == Vec2L(0, -1)) // 한 칸만 옮겼을 때
			{
				auto lastlastLine = lastLine;
				lastLine = CreateLine(tilePos.x, tilePos.y, lastLine);

				if (existGate == true) // 게이트와 연결이 되었을 때
				{
					Directional dirGate = NO;

					for (auto& iter : targetGate->input)
					{
						if (iter == -dirVec)
							dirGate = INPUT;
					}
					for (auto& iter : targetGate->output)
					{
						if (iter == -dirVec)
							dirGate = OUTPUT;
					}

					if (dirGate == INPUT && directional == OUTPUT
						|| dirGate == OUTPUT && directional == INPUT) // 게이트와 연결 성공
					{
						scene->objectManager->connectingLine.clear();

						if (directional == OUTPUT)
						{
							lastlastLine->output = lastlastLine->tilePos - tilePos;
						}
						else
						{
							lastlastLine->input = lastlastLine->tilePos - tilePos;
						}
						lastlastLine->SetSprite();

						inputState = InputState::NONE;
						myGate->GetSpriteRenderer()->SetZ_index(0);
						shadow->SetIsEnable(false);
						myGate = nullptr;
					}
					else
					{
						CancelConnect();
					}
				}
				else if (lastLine == nullptr) // 라인을 이을 수 없을 때
				{
					CancelConnect();
				}
			}
			else if (tilePos != lastLine->tilePos) // 여러 칸을 옮겼을 때 (연결 취소)
			{
				CancelConnect();
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) // 라인 연결 취소
		{
			CancelConnect();
		}
	}
}

Line* GameInputManager::CreateLine(int x, int y)
{
	Vec2L pos(x, y);
	bool canCreate = true;
	existGate = false;

	// 그 위치에 이미 게이트가 있는가?
	for (auto& iter : scene->objectManager->gates)
	{
		if (iter->tilePos == pos)
		{
			canCreate = false;
			existGate = true;
		}
	}

	// 그 위치에 이미 라인이 있는가?
	for (auto& iter : scene->objectManager->lines)
	{
		if (iter->tilePos == pos)
			canCreate = false;
	}

	// 맵 밖인가?
	if (!(pos.x >= -scene->mapSize.x / 2 && pos.x <= scene->mapSize.x / 2 - !(scene->mapSize.x % 2)
		&& pos.y >= -scene->mapSize.y / 2 && pos.y <= scene->mapSize.y / 2 - !(scene->mapSize.y % 2)))
	{
		canCreate = false;
	}

	if (canCreate)
	{
		if (SettingData::GetInstance()->effect)
		{
			for (int i = 0; i < 4; i++)
			{
				Dust* dust = new Dust;
				dust->GetComponent<Transform>()->SetPos(x, y);
				AttachObject(dust);
			}
		}

		Line* line = new Line(x, y);
		scene->objectManager->connectingLine.push_back(line);
		scene->objectManager->lines.push_back(line);
		line->ChangeParent(scene->tiles);
		
		if (directional == OUTPUT)
			line->input = pos - myGate->tilePos;
		else
			line->output = pos - myGate->tilePos;
		
		line->SetSprite();

		return line;
	}
	else
	{
		return nullptr;
	}
}

Line* GameInputManager::CreateLine(int x, int y, Line* preLine)
{
	Vec2L pos(x, y);
	bool canCreate = true;
	existGate = false;

	// 그 위치에 이미 게이트가 있는가?
	for (auto& iter : scene->objectManager->gates)
	{
		if (iter->tilePos == pos)
		{
			canCreate = false;
			existGate = true;
		}
	}

	// 그 위치에 이미 라인이 있는가?
	for (auto& iter : scene->objectManager->lines)
	{
		if (iter->tilePos == pos)
			canCreate = false;
	}

	// 맵 밖인가?
	if (!(pos.x >= -scene->mapSize.x / 2 && pos.x <= scene->mapSize.x / 2 - !(scene->mapSize.x % 2)
		&& pos.y >= -scene->mapSize.y / 2 && pos.y <= scene->mapSize.y / 2 - !(scene->mapSize.y % 2)))
	{
		canCreate = false;
	}

	if (canCreate)
	{
		if (SettingData::GetInstance()->effect)
		{
			for (int i = 0; i < 4; i++)
			{
				Dust* dust = new Dust;
				dust->GetComponent<Transform>()->SetPos(x, y);
				AttachObject(dust);
			}
		}

		Line* line = new Line(x, y);
		scene->objectManager->connectingLine.push_back(line);
		scene->objectManager->lines.push_back(line);
		line->ChangeParent(scene->tiles);

		if (directional == OUTPUT)
		{
			line->input = pos - preLine->tilePos;
			preLine->output = preLine->tilePos - pos;
		}
		else
		{
			line->output = pos - preLine->tilePos;
			preLine->input = preLine->tilePos - pos;
		}

		line->SetSprite();
		preLine->SetSprite();

		return line;
	}
	else
	{
		return nullptr;
	}
}

void GameInputManager::CancelConnect()
{
	for (auto& iter : scene->objectManager->connectingLine)
	{
		iter->Destroy();
		scene->objectManager->lines.remove(iter);
	}
	scene->objectManager->connectingLine.clear();

	inputState = InputState::NONE;
	myGate->GetSpriteRenderer()->SetZ_index(0);
	shadow->SetIsEnable(false);
	myGate = nullptr;
}

void GameInputManager::GateMove()
{
	if (inputState == InputState::GATE_LIFT) // 게이트를 들고 있을 때
	{
		Vec2F mousePos = RG2R_InputM->GetMouseWorldPos();
		myGate->GetTransform()->SetPos(mousePos + Vec2F(0, 0.2f));
		shadow_transform->SetPos(mousePos);

		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KeyState::KEYSTATE_EXIT) // 게이트를 놨을 때
		{
			if (myGate->tilePos == tilePos) // 위치 변화가 없을 경우
			{
				myGate->GetTransform()->SetPos(myGate->tilePos.x, myGate->tilePos.y);
				inputState = InputState::NONE;
				myGate->GetSpriteRenderer()->SetZ_index(0);
				shadow->SetIsEnable(false);
				myGate = nullptr;
			}
			else
			{
				bool canMove = true;

				// 그 위치에 이미 게이트가 있는가?
				for (auto& iter : scene->objectManager->gates)
				{
					if (iter->tilePos == tilePos)
						canMove = false;
				}

				// 그 위치에 이미 라인이 있는가?
				for (auto& iter : scene->objectManager->lines)
				{
					if (iter->tilePos == tilePos)
						canMove = false;
				}

				// 맵 밖인가?
				if (!(tilePos.x >= -scene->mapSize.x / 2 && tilePos.x <= scene->mapSize.x / 2 - !(scene->mapSize.x % 2)
					&& tilePos.y >= -scene->mapSize.y / 2 && tilePos.y <= scene->mapSize.y / 2 - !(scene->mapSize.y % 2)))
				{
					canMove = false;
				}

				if (canMove) // 움직일 수 있을 때
				{
					myGate->GetTransform()->SetPos(tilePos.x, tilePos.y);
					myGate->tilePos = tilePos;
					inputState = InputState::NONE;
					myGate->GetSpriteRenderer()->SetZ_index(0);
					shadow->SetIsEnable(false);
					myGate = nullptr;
					SoundMaster::GetInstance()->PlayEffectSound(SoundID::DROP);
				}
				else // 움직일 수 없을 때
				{
					myGate->GetTransform()->SetPos(myGate->tilePos.x, myGate->tilePos.y);
					inputState = InputState::NONE;
					myGate->GetSpriteRenderer()->SetZ_index(0);
					shadow->SetIsEnable(false);
					myGate = nullptr;
				}
			}
		}
	}
}