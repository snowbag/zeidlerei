#pragma once
#include "Network.h"

class HaltingCondition
{
public:
	virtual void calculate(const Network& network) = 0;
	virtual bool isTrue() const = 0;
};

