#include "PermitForbidFilter.h"

#include <algorithm>


PermitForbidFilter::PermitForbidFilter(const std::vector<std::string>& required, const std::vector<std::string>& forbidden)
	: required_(required), forbidden_(forbidden)
{
}


bool PermitForbidFilter::apply(Word& word) const
{
	std::string content = word.getContent();
	bool ok =
		std::all_of(required_.begin(), required_.end(), [&content](std::string part) { return content.find(part) != std::string::npos; })
		&&
		std::none_of(forbidden_.begin(), forbidden_.end(), [&content](std::string part) { return content.find(part) != std::string::npos; });
	return ok;
}