#pragma once
#include "Gate.h"

class AddGate :
	public Gate
{
public:
	AddGate(long, long, Dir);
	~AddGate();

	virtual std::type_index GetID(void) { return typeid(AddGate); };
};