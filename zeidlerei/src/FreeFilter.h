#pragma once
#include "Filter.h"

class FreeFilter :
	public Filter
{
public:
	virtual bool apply(Word& word) const { return true; }
};