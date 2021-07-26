#pragma once
#include "Gate.h"

class NotDivisionGate :
	public Gate
{
public:
	NotDivisionGate(long, long, Dir);
	~NotDivisionGate();

	virtual std::type_index GetID(void) { return typeid(NotDivisionGate); };
};