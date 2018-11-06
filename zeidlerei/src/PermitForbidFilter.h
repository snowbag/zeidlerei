#pragma once
#include "Filter.h"

#include <vector>
#include <string>

class PermitForbidFilter :
	public Filter
{
public:
	PermitForbidFilter(const std::string& rule);
	PermitForbidFilter(const std::vector<std::string>& required, const std::vector<std::string>& forbidden);
	virtual bool apply(Word& word) const;
private:
	std::vector<std::string> required_;
	std::vector<std::string> forbidden_;
};

