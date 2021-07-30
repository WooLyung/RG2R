#include "stdafx.h"
#include "CommandList.h"
#include "Engine.h"

CommandList::CommandList()
{
}

CommandList::~CommandList()
{
}

float CommandList::GetTime()
{
	return time;
}

int CommandList::GetIndex()
{
	return index;
}

bool CommandList::GetIsPlaying()
{
	return isPlaying;
}

bool CommandList::GetIsLoop()
{
	return isLoop;
}

void CommandList::Update()
{
	if (isPlaying)
	{
		time += RG2R_TimeM->GetDeltaTime();

		if (commands[index].startPos + commands[index].time <= time)
		{
			if (commands[index].command != NULL)
				commands[index].command();

			if (index == commands.size() - 1)
			{
				index = 0;
				time = 0;

				if (!isLoop)
				{
					isPlaying = false;
				}
			}
			else
			{
				index++;
			}
		}
	}
}

void CommandList::Start()
{
	isPlaying = true;
}

void CommandList::Pause()
{
	isPlaying = false;
}

void CommandList::Stop()
{
	isPlaying = false;
	index = 0;
	time = 0;
}

void CommandList::Restart()
{
	isPlaying = true;
	index = 0;
	time = 0;
}

CommandList* CommandList::PushCommand(FP function, float time)
{
	Command command;
	command.command = function;
	command.time = time;
	if (commands.size() == 0)
		command.startPos = 0;
	else
		command.startPos = commands[commands.size() - 1].startPos + commands[commands.size() - 1].time;

	commands.push_back(command);

	return this;
}

Command CommandList::PopCommand()
{
	Command command = commands[commands.size() - 1];
	commands.pop_back();

	return command;
}

CommandList* CommandList::SetIsLoop(bool isLoop)
{
	this->isLoop = isLoop;

	return this;
}