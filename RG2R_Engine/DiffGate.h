#pragma once
#include "Gate.h"

class DiffGate :
	public Gate
{
public:
	DiffGate(long, long, Dir);
	~DiffGate();

	virtual std::type_index GetID(void) { return typeid(DiffGate); };
};