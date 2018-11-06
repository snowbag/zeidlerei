#include "PermitForbidFilter.h"

#include <algorithm>


PermitForbidFilter::PermitForbidFilter(const std::string& rule)
{
	int plus = rule.find("+");
	int minus = rule.find("-");
	while (plus != std::string::npos) {
		int nextPlus = rule.find("+", plus + 1);
		if (nextPlus == std::string::npos) {
			required_.push_back(rule.substr(plus + 1, minus - (plus + 1)));
		}
		else {
			required_.push_back(rule.substr(plus + 1, nextPlus - (plus + 1)));
		}
		plus = nextPlus;
	}
	while (minus != std::string::npos) {
		int nextMinus = rule.find("-", minus + 1);
		forbidden_.push_back(rule.substr(minus + 1, nextMinus - (minus + 1)));
		minus = nextMinus;
	}
}

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