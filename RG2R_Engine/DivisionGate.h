#pragma once
#include "Gate.h"

class DivisionGate :
	public Gate
{
public:
	DivisionGate(long, long, Dir);
	~DivisionGate();

	virtual std::type_index GetID(void) { return typeid(DivisionGate); };
};