#pragma once
#include "Filter.h"

class NoneFilter :
	public Filter
{
public:
	virtual bool apply(Word& word) const { return false; }
};

