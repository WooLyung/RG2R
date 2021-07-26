#pragma once
#include "Object.h"
#include "CommandList.h"

class Tiles :
	public Object
{
private:
	CommandList* upAnim, *downAnim;
	float animTime = 0;

public:
	Tiles(int, int);
	~Tiles();

	void Down();
};