#pragma once
#include "Word.h"

class Filter
{
public:
	Filter();
	~Filter();
	virtual bool apply(Word& w) const = 0;
};

