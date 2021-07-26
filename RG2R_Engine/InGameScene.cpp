#include "stdafx.h"
#include "InGameScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"
#include "AddGate.h"
#include "Light1.h"
#include "Light2.h"
#include "Light3.h"
#include "Battery.h"
#include "Gate.h"
#include "Line.h"
#include "DivisionGate.h"
#include "SubGate.h"
#include "ReverseGate.h"
#include "AndGate.h"
#include "DiffGate.h"
#include "NotDivisionGate.h"
#include "ObjectManager.h"
#include "GameInputManager.h"
#include "StageData.h"
#include "SceneData.h"
#include "MapEditData.h"
#include <fstream>

#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::OnStart()
{
	cursor = new Cursor;
	AttachObject(cursor);

	objectManager = new ObjectManager(this);
	gameInputManager = new GameInputManager(this);
	playManager = new PlayManager(this);
	sceneChangeManager = new SceneChangeManager(this);

	AttachObject(objectManager);
	AttachObject(gameInputManager);
	AttachObject(playManager);
	AttachObject(sceneChangeManager);

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));

	if (SceneData::GetInstance()->inGameCode == 0)
	{
		playButton = new PlayButton(true, this);
		resetButton = new ResetButton(true, this);
		menuButton = new MenuButton(true, this);
		editButton = new EditButton(true, this);
	}
	else
	{
		playButton = new PlayButton(false, this);
		resetButton = new ResetButton(false, this);
		menuButton = new MenuButton(false, this);
		editButton = new EditButton(false, this);
	}
	popup = new Popup;
	postit = new PostIt(true);

	AttachObject(popup);
	AttachObject(postit);
	AttachObject(playButton);
	AttachObject(resetButton);
	AttachObject(editButton);
	AttachObject(menuButton);

	Init();
}

void InGameScene::OnUpdate()
{
}

void InGameScene::Init()
{
	if (MapEditData::GetInstance()->playType == 0)
	{
		std::string path = "Resources/Maps/";
		path += std::to_string(StageData::GetInstance()->chapter) + "Chapter/";
		path += std::to_string(StageData::GetInstance()->stage) + "stage.txt";

		std::string data;
		std::ifstream in(path);
		while (getline(in, data)) {
			size_t start_pos = 0;
			while ((start_pos = data.find(" ", start_pos)) != std::string::npos)
			{
				data.replace(start_pos, string(" ").length(), "");
				start_pos += string("").length();
			}

			string splitedString, key, value;
			std::map<string, string> gateData;
			size_t begin = 0, end = 1;

			while (true)
			{
				end++;
				if (data[end] == ',' || end == data.size())
				{
					splitedString = data.substr(begin, end - begin);

					key = splitedString.substr(0, splitedString.find(":"));
					value = splitedString.substr(splitedString.find(":") + 1, splitedString.size());

					gateData.insert(std::pair<string, string>(key, value));

					begin = ++end;
				}
				if (end >= data.size())
					break;
			}

			if (gateData.find("type") == gateData.end())
			{
				mapSize.x = std::stoi(gateData["x"]);
				mapSize.y = std::stoi(gateData["y"]);
				GetMainCamera()->SetZoom(std::stof(gateData["zoom"]), std::stof(gateData["zoom"]));

				string text = gateData["text"];
				size_t start_pos = 0;
				while ((start_pos = text.find("_", start_pos)) != std::string::npos)
				{
					text.replace(start_pos, string("_").length(), " ");
					start_pos += string(" ").length();
				}
				start_pos = 0;
				while ((start_pos = text.find("\\", start_pos)) != std::string::npos)
				{
					text.replace(start_pos, string("\\").length(), "\n");
					start_pos += string("\n").length();
				}

				postit->GetTextRenderer()->SetText(text);

				tiles = new Tiles(mapSize.x, mapSize.y);
				AttachObject(tiles);
			}
			else
			{
				CreateGate(gateData);
			}
		}
		in.close();
	}
	else if (MapEditData::GetInstance()->playType == 2)
	{
		std::string data;
		std::ifstream in("Datas/lastMap.txt");
		while (getline(in, data)) {
			size_t start_pos = 0;
			while ((start_pos = data.find(" ", start_pos)) != std::string::npos)
			{
				data.replace(start_pos, string(" ").length(), "");
				start_pos += string("").length();
			}

			string splitedString, key, value;
			std::map<string, string> gateData;
			size_t begin = 0, end = 1;

			while (true)
			{
				end++;
				if (data[end] == ',' || end == data.size())
				{
					splitedString = data.substr(begin, end - begin);

					key = splitedString.substr(0, splitedString.find(":"));
					value = splitedString.substr(splitedString.find(":") + 1, splitedString.size());

					gateData.insert(std::pair<string, string>(key, value));

					begin = ++end;
				}
				if (end >= data.size())
					break;
			}

			if (gateData.find("type") == gateData.end())
			{
				mapSize.x = std::stoi(gateData["x"]);
				mapSize.y = std::stoi(gateData["y"]);
				GetMainCamera()->SetZoom(std::stof(gateData["zoom"]), std::stof(gateData["zoom"]));

				string text = gateData["text"];
				size_t start_pos = 0;
				while ((start_pos = text.find("_", start_pos)) != std::string::npos)
				{
					text.replace(start_pos, string("_").length(), " ");
					start_pos += string(" ").length();
				}
				start_pos = 0;
				while ((start_pos = text.find("\\", start_pos)) != std::string::npos)
				{
					text.replace(start_pos, string("\\").length(), "\n");
					start_pos += string("\n").length();
				}

				postit->GetTextRenderer()->SetText(text);

				tiles = new Tiles(mapSize.x, mapSize.y);
				AttachObject(tiles);
			}
			else
			{
				CreateGate(gateData);
			}
		}
		in.close();
	}
	else if (MapEditData::GetInstance()->playType == 1)
	{
		mapSize.x = MapEditData::GetInstance()->width;
		mapSize.y = MapEditData::GetInstance()->height;
		GetMainCamera()->SetZoom(MapEditData::GetInstance()->zoom, MapEditData::GetInstance()->zoom);
		postit->GetTextRenderer()->SetText("제작한 맵을 클리어해야\n업로드가 가능합니다");

		tiles = new Tiles(mapSize.x, mapSize.y);
		AttachObject(tiles);

		for (auto& iter : MapEditData::GetInstance()->gates)
		{
			std::map<string, string> gateData;

			gateData.insert(std::pair<string, string>("x", to_string(iter.x)));
			gateData.insert(std::pair<string, string>("y", to_string(iter.y)));
			gateData.insert(std::pair<string, string>("type", iter.type));
			gateData.insert(std::pair<string, string>("isStatic", iter.isStatic ? "true" : "false"));
			gateData.insert(std::pair<string, string>("dir", iter.dir));
			gateData.insert(std::pair<string, string>("color", iter.color));

			CreateGate(gateData);
		}
	}

	if (mapSize.x % 2 == 0)
		GetMainCamera()->Translate(-0.5f, 0);
	if (mapSize.y % 2 == 0)
		GetMainCamera()->Translate(0, -0.5f);
}

Vec2L InGameScene::GetTilePos()
{
	Vec2F pos = RG2R_InputM->GetMouseWorldPos();
	pos += Vec2F(0.5f, 0.5f);
	pos = Vec2F(floor(pos.x), floor(pos.y));

	return Vec2L(pos.x, pos.y);
}

void InGameScene::PushGate(Gate* gate)
{
	objectManager->PushGate(gate);
}

void InGameScene::CreateGate(std::map<string, string> data)
{
	Gate* gate = nullptr;

	Dir dir = Dir::RIGHT;
	if (data.find("dir") != data.end())
	{
		if (data["dir"] == "right")
			dir = Dir::RIGHT;
		else if (data["dir"] == "left")
			dir = Dir::LEFT;
		else if (data["dir"] == "up")
			dir = Dir::UP;
		else if (data["dir"] == "down")
			dir = Dir::DOWN;
	}

	bool isStatic = false;
	if (data.find("isStatic") != data.end())
	{
		if (data["isStatic"] == "true")
			isStatic = true;
	}

	int x = std::stoi(data["x"]);
	int y = std::stoi(data["y"]);

	if (data["type"] == "battery")
	{
		Color8 color = Color8(1, 0, 0);
		if (data.find("color") != data.end())
		{
			if (data["color"] == "red")
				color = Color8(1, 0, 0);
			else if (data["color"] == "green")
				color = Color8(0, 1, 0);
			else if (data["color"] == "blue")
				color = Color8(0, 0, 1);
			else if (data["color"] == "cyan")
				color = Color8(0, 1, 1);
			else if (data["color"] == "magenta")
				color = Color8(1, 0, 1);
			else if (data["color"] == "yellow")
				color = Color8(1, 1, 0);
			else if (data["color"] == "black")
				color = Color8(0, 0, 0);
			else if (data["color"] == "white")
				color = Color8(1, 1, 1);
		}

		gate = new Battery(x, y, dir, color);
		PushGate(gate);
	}
	else if (data["type"] == "add_gate")
	{
		gate = new AddGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "division_gate")
	{
		gate = new DivisionGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "sub_gate")
	{
		gate = new SubGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "light1")
	{
		gate = new Light1(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "light2")
	{
		gate = new Light2(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "light3")
	{
		gate = new Light3(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "reverse_gate")
	{
		gate = new ReverseGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "and_gate")
	{
		gate = new AndGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "diff_gate")
	{
		gate = new DiffGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "not_division_gate")
	{
		gate = new NotDivisionGate(x, y, dir);
		PushGate(gate);
	}

	if (gate != nullptr)
	{
		gate->SetStatic(isStatic);
		gate->ChangeParent(tiles);
	}
}

void InGameScene::PopMsg(int code)
{
	popup->Pop(code);
}

void InGameScene::Disappear(int code)
{
	if (!isFinish)
	{
		isFinish = true;

		if (code == 1) // 재시작
		{
			SceneData::GetInstance()->inGameCode = 1;
			postit->Disappear();
			tiles->Down();
			sceneChangeManager->Reset();
		}
		else if (code == 2) // 다른 스테이지
		{
			SceneData::GetInstance()->inGameCode = 1;
			postit->Disappear();
			tiles->Down();
			sceneChangeManager->Diff();
		}
		else if (code == 3) // 스테이지 선택으로
		{
			SceneData::GetInstance()->inGameCode = 0;
			postit->Disappear();
			playButton->Disappear();
			resetButton->Disappear();
			menuButton->Disappear();
			editButton->Disappear();
			tiles->Down();
			sceneChangeManager->Back();
		}
		else if (code == 4) // 맵 제작으로
		{
			SceneData::GetInstance()->inGameCode = 0;
			postit->Disappear();
			playButton->Disappear();
			resetButton->Disappear();
			menuButton->Disappear();
			editButton->Disappear();
			tiles->Down();
			sceneChangeManager->Edit();
		}
	}
}