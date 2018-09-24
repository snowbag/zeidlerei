#pragma once
#include "Filter.h"
class FreeFilter :
	public Filter
{
public:
	FreeFilter();
	~FreeFilter();
	virtual bool apply(Word& w) const { return true; }
};

