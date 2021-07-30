#pragma once
#include "Command.h"

class CommandList
{
private:
	float time = 0;
	int index = 0;
	std::vector<Command> commands;
	bool isPlaying = false;
	bool isLoop = false;

public:
	CommandList();
	~CommandList();

	float GetTime();
	int GetIndex();
	bool GetIsPlaying();
	bool GetIsLoop();

	CommandList* SetIsLoop(bool);
	CommandList* PushCommand(FP, float);
	Command PopCommand();

	void Update();
	void Start();
	void Pause();
	void Stop();
	void Restart();
};