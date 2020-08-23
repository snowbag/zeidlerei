#pragma once
#include "Word.h"

class Filter
{
public:
	virtual bool apply(Word& word) const = 0;
};