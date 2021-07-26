#include "stdafx.h"
#include "PlayManager.h"
#include "Engine.h"
#include "CommandList.h"
#include "StageClearObj.h"
#include "ToNextButton.h"
#include "ToMenuButton.h"
#include "PlayerData.h"
#include "StageData.h"
#include "SettingData.h"
#include "Confetti.h"

#include "Battery.h"
#include "AddGate.h"
#include "DivisionGate.h"
#include "ReverseGate.h"
#include "AndGate.h"
#include "DiffGate.h"
#include "SubGate.h"
#include "Light2.h"
#include "NotDivisionGate.h"

#include <queue>
#include <fstream>
#include <stack>

PlayManager::PlayManager(InGameScene* scene)
{
	this->scene = scene;
}

PlayManager::~PlayManager()
{
}

void PlayManager::OnStart()
{
	gameNotClear = new CommandList;
	gameNotClear->PushCommand([=]() {
		for (auto& iter : scene->objectManager->gates)
		{
			if (iter->GetID() != typeid(Battery))
			{
				iter->SetColor(Color(0.8f, 0.8f, 0.8f, 1));
			}
		}
		for (auto& iter : scene->objectManager->lines)
		{
			iter->SetColor(Color(0.8f, 0.8f, 0.8f, 1));
		}
		}, 1.5f)
		->PushCommand([=]() {
			gameState = GameState::CircuitDesign;
			}, 0.5f);
		commandLists.push_back(gameNotClear);

	clearEffect = new CommandList;
	clearEffect->PushCommand([=]() {
		for (auto& iter : scene->objectManager->gates)
		{
			iter->SetColor(clearEffectColor);
		}
		for (auto& iter : scene->objectManager->lines)
		{
			iter->SetColor(clearEffectColor);
		}

		if (clearEffectColor == Color8(1, 0, 0))
			clearEffectColor = Color8(0, 1, 0);
		else if (clearEffectColor == Color8(0, 1, 0))
			clearEffectColor = Color8(0, 0, 1);
		else if (clearEffectColor == Color8(0, 0, 1))
			clearEffectColor = Color8(1, 0, 0);

		}, 0.6f);
	clearEffect->SetIsLoop(true);
	commandLists.push_back(clearEffect);

	tryPlay = new CommandList;
	tryPlay->PushCommand([=]() {
		if (!term)
		{
			if (!isStop)
			{

				if (sortedNodes[playIndex]->type == 1) // 라인
				{
					Line* line = scene->objectManager->FindLine(-sortedNodes[playIndex]->line->input + sortedNodes[playIndex]->line->tilePos);
					Gate* gate = scene->objectManager->FindGate(-sortedNodes[playIndex]->line->input + sortedNodes[playIndex]->line->tilePos);

					Color8 color;
					if (gate != nullptr)
						color = gate->GetColor();
					else
						color = line->GetColor();

					sortedNodes[playIndex]->line->SetColor(color);
				}
				else // 게이트
				{
					Color8 color = Color8(0, 0, 0);

					if (sortedNodes[playIndex]->gate->GetID() == typeid(AddGate)
						|| sortedNodes[playIndex]->gate->GetID() == typeid(Light))
					{
						for (auto inputs : sortedNodes[playIndex]->gate->input)
						{
							Line* line = scene->objectManager->FindLine(inputs + sortedNodes[playIndex]->gate->tilePos);
							Gate* gate = scene->objectManager->FindGate(inputs + sortedNodes[playIndex]->gate->tilePos);

							Color8 getColor = Color8(0, 0, 0);
							if (gate != nullptr)
								getColor = gate->GetColor();
							else
								getColor = line->GetColor();

							color = (Color8)(color + getColor);
						}
						sortedNodes[playIndex]->gate->SetColor(color);
					}
					else if (sortedNodes[playIndex]->gate->GetID() == typeid(DivisionGate))
					{
						for (auto inputs : sortedNodes[playIndex]->gate->input)
						{
							Line* line = scene->objectManager->FindLine(inputs + sortedNodes[playIndex]->gate->tilePos);
							Gate* gate = scene->objectManager->FindGate(inputs + sortedNodes[playIndex]->gate->tilePos);

							if (gate != nullptr)
								color = gate->GetColor();
							else
								color = line->GetColor();
						}
						sortedNodes[playIndex]->gate->SetColor(color);
					}
					else if (sortedNodes[playIndex]->gate->GetID() == typeid(ReverseGate)
						|| sortedNodes[playIndex]->gate->GetID() == typeid(NotDivisionGate))
					{
						for (auto inputs : sortedNodes[playIndex]->gate->input)
						{
							Line* line = scene->objectManager->FindLine(inputs + sortedNodes[playIndex]->gate->tilePos);
							Gate* gate = scene->objectManager->FindGate(inputs + sortedNodes[playIndex]->gate->tilePos);

							if (gate != nullptr)
								color = gate->GetColor();
							else
								color = line->GetColor();
						}
						sortedNodes[playIndex]->gate->SetColor(!color);
					}
					else if (sortedNodes[playIndex]->gate->GetID() == typeid(SubGate))
					{
						Color8 color1, color2;

						Line* line1 = scene->objectManager->FindLine(sortedNodes[playIndex]->gate->input[0] + sortedNodes[playIndex]->gate->tilePos);
						Gate* gate1 = scene->objectManager->FindGate(sortedNodes[playIndex]->gate->input[0] + sortedNodes[playIndex]->gate->tilePos);
						Line* line2 = scene->objectManager->FindLine(sortedNodes[playIndex]->gate->input[1] + sortedNodes[playIndex]->gate->tilePos);
						Gate* gate2 = scene->objectManager->FindGate(sortedNodes[playIndex]->gate->input[1] + sortedNodes[playIndex]->gate->tilePos);

						if (gate1 != nullptr)
							color1 = gate1->GetColor();
						else
							color1 = line1->GetColor();

						if (gate2 != nullptr)
							color2 = gate2->GetColor();
						else
							color2 = line2->GetColor();

						color = color1 - color2;
						sortedNodes[playIndex]->gate->SetColor(color);
					}
					if (sortedNodes[playIndex]->gate->GetID() == typeid(AndGate))
					{
						color = Color8(1, 1, 1);

						for (auto inputs : sortedNodes[playIndex]->gate->input)
						{
							Line* line = scene->objectManager->FindLine(inputs + sortedNodes[playIndex]->gate->tilePos);
							Gate* gate = scene->objectManager->FindGate(inputs + sortedNodes[playIndex]->gate->tilePos);

							Color8 getColor = Color8(0, 0, 0);
							if (gate != nullptr)
								getColor = gate->GetColor();
							else
								getColor = line->GetColor();

							color = color & getColor;
						}
						sortedNodes[playIndex]->gate->SetColor(color);
					}
					if (sortedNodes[playIndex]->gate->GetID() == typeid(DiffGate))
					{
						color = Color8(1, 1, 1);

						for (auto inputs : sortedNodes[playIndex]->gate->input)
						{
							Line* line = scene->objectManager->FindLine(inputs + sortedNodes[playIndex]->gate->tilePos);
							Gate* gate = scene->objectManager->FindGate(inputs + sortedNodes[playIndex]->gate->tilePos);

							Color8 getColor = Color8(0, 0, 0);
							if (gate != nullptr)
								getColor = gate->GetColor();
							else
								getColor = line->GetColor();

							color = color & getColor;
						}
						sortedNodes[playIndex]->gate->SetColor(!color);
					}
				}
				this->playIndex++;

				if (playIndex >= sortedNodes.size())
				{
					tryPlay->Stop();
					Result();
				}
				else if (sortedNodes[playIndex]->type == 0)
				{
					term = 5;
				}
			}
		}
		else
		{
			term--;
		}
		}, 0.03f);
	tryPlay->SetIsLoop(true);
	commandLists.push_back(tryPlay);
}

int PlayManager::CheckClear()
{
	std::map<Object*, Node*> map;
	std::vector<Node*> nodes;
	std::queue<Node*> nodeStack;

	int input = 0, output = 0;

	for (auto& iter : sortedNodes)
	{
		delete iter;
	}
	sortedNodes.clear();

	for (auto& iter : scene->objectManager->gates)
	{
		Node* node = new Node;
		node->gate = iter;
		node->type = 0;
		map.insert(std::pair<Object*, Node*>(iter, node));
		nodes.push_back(node);

		input += iter->input.size();
		output += iter->output.size();
	}
	for (auto& iter : scene->objectManager->lines)
	{
		Node* node = new Node;
		node->line = iter;
		node->type = 1;
		map.insert(std::pair<Object*, Node*>(iter, node));
		nodes.push_back(node);
	}

	if (input != output)
		return 1;

	for (auto& node : nodes)
	{
		if (node->type == 0) // 게이트
		{
			for (auto output : node->gate->output)
			{
				Gate* findGate = scene->objectManager->FindGate(node->gate->tilePos + output);
				Line* findLine = scene->objectManager->FindLine(node->gate->tilePos + output);

				if (findGate != nullptr)
				{
					bool isOk = false;

					for (auto input : findGate->input)
					{
						Vec2L pos1 = input + findGate->tilePos;
						Vec2L pos2 = node->gate->tilePos;

						if (pos1 == pos2)
						{
							isOk = true;
							node->next.push_back(map[findGate]);
						}
					}

					if (!isOk)
					{
						return 1;
					}
				}
				else if (findLine != nullptr)
				{
					node->next.push_back(map[findLine]);
				}
				else
				{
					return 1;
				}
			}

			if (node->gate->GetID() == typeid(Battery))
			{
				nodeStack.push(node);
			}
		}
		else // 라인
		{
			Gate* findGate = scene->objectManager->FindGate(node->line->tilePos - node->line->output);
			Line* findLine = scene->objectManager->FindLine(node->line->tilePos - node->line->output);

			if (findGate != nullptr)
			{
				node->next.push_back(map[findGate]);
			}
			else
			{
				node->next.push_back(map[findLine]);
			}
		}

		for (auto iter : node->next)
		{
			iter->inDegree++;
		}
	}

	while (nodeStack.size() > 0)
	{
		Node* node = nodeStack.front();
		nodeStack.pop();
		sortedNodes.push_back(node);

		for (auto iter : node->next)
		{
			iter->inDegree--;

			if (iter->inDegree == 0)
			{
				nodeStack.push(iter);
			}
		}
	}

	if (sortedNodes.size() != nodes.size())
		return 2;

	return 0;
}

void PlayManager::Play()
{
	playIndex = 0;
	gameState = GameState::Try;
	tryPlay->Start();
}

void PlayManager::Try()
{
	int result = CheckClear();
	if (result == 0)
	{
		Play();
		scene->playButton->GetSpriteRenderer()
			->SetTexture("Resources/Sprites/UIs/Menus/stopButton.png");
	}
	else if (result == 1)
	{
		scene->PopMsg(0);
		scene->playButton->GetSpriteRenderer()
			->SetTexture("Resources/Sprites/UIs/Menus/playButton.png");
	}
	else if (result == 2)
	{
		scene->PopMsg(1);
		scene->playButton->GetSpriteRenderer()
			->SetTexture("Resources/Sprites/UIs/Menus/playButton.png");
	}
}

void PlayManager::OnUpdate()
{
}

void PlayManager::Result()
{
	scene->playButton->GetSpriteRenderer()
		->SetTexture("Resources/Sprites/UIs/Menus/playButton.png");

	bool isClear = true;
	for (auto& iter : scene->objectManager->gates)
	{
		if (iter->GetID() == typeid(Light) && iter->GetColor() != Color8(1, 1, 1))
		{
			isClear = false;
		}
	}

	if (isClear)
	{
		auto obj = new StageClearObj(scene);
		auto child1 = new ToNextButton(scene, obj);
		auto child2 = new ToMenuButton(scene, obj);
		AttachObject(child1);
		AttachObject(child2);
		AttachObject(obj);
		child1->parentTransform = obj->GetComponent<Transform>();
		child2->parentTransform = obj->GetComponent<Transform>();
		
		if (SettingData::GetInstance()->effect)
		{
			for (int i = 0; i < 50; i++)
			{
				Confetti* confetti = new Confetti(0);
				AttachObject(confetti);
			}
			for (int i = 0; i < 50; i++)
			{
				Confetti* confetti = new Confetti(1);
				AttachObject(confetti);
			}
		}
		gameState = GameState::Clear;

		if (PlayerData::GetInstance()->stage == StageData::GetInstance()->stage
			&& PlayerData::GetInstance()->chapter == StageData::GetInstance()->chapter)
		{
			if (PlayerData::GetInstance()->stage == 8)
			{
				PlayerData::GetInstance()->chapter++;
				PlayerData::GetInstance()->stage = 1;
			}
			else
			{
				PlayerData::GetInstance()->stage++;
			}

			std::string out_line;
			std::ofstream out("Datas/stageData.txt");
			out << PlayerData::GetInstance()->chapter << std::endl << PlayerData::GetInstance()->stage;
			out.close();
		}
	}
	else
	{
		scene->PopMsg(2);
		gameNotClear->Start();
	}
}