#pragma once
#include "stdafx.h"

struct Command
{
	float time = 0;
	float startPos = 0;
	std::function<void()> command = NULL;
};