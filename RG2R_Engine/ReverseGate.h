#pragma once
#include "Gate.h"

class ReverseGate :
	public Gate
{
public:
	ReverseGate(long, long, Dir);
	~ReverseGate();

	virtual std::type_index GetID(void) { return typeid(ReverseGate); };
};