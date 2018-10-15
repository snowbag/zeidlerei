#pragma once
#include <regex>

#include "Filter.h"

class RegexFilter :
	public Filter
{
public:
	RegexFilter(const std::string& re);
	virtual bool apply(Word& word) const;
private:
	std::regex regex_;
};

