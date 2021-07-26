#pragma once
#include "Object.h"
#include "InGameScene.h"
#include "Line.h"
#include "Gate.h"

class InGameScene;

struct Node
{
	Line* line;
	Gate* gate;
	int type = 0;
	int inDegree = 0;
	std::vector<Node*> next;
};

class PlayManager :
	public Object
{
	friend class GameInputManager;

private:
	InGameScene* scene;
	std::vector<Node*> sortedNodes;

	CommandList* tryPlay;
	CommandList* clearEffect;
	CommandList* gameNotClear;
	Color8 clearEffectColor = Color8(1, 0, 0);

	int playIndex = 0;
	int term = 0;
	bool isStop = false;

public:
	PlayManager(InGameScene*);
	~PlayManager();

	bool GetIsStop() { return isStop; }
	void SetIsStop(bool isStop_) { isStop = isStop_; }

	void OnUpdate();
	void OnStart();

	int CheckClear();
	void Try();
	void Play();
	void Result();

	GameState gameState = CircuitDesign;
};