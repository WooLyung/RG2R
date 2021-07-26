#pragma once
#include "Gate.h"

class AndGate :
	public Gate
{
public:
	AndGate(long, long, Dir);
	~AndGate();

	virtual std::type_index GetID(void) { return typeid(AndGate); };
};