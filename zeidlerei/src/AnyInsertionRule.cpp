#include "AnyInsertionRule.h"



std::vector<Word> AnyInsertionRule::apply(Word& word) const
{
	std::vector<Word> result;
	std::string content = word.getContent();
	for (size_t i = 0; i <= content.size(); ++i) {
		std::string next = content;
		next.insert(i, rhs_);
		result.push_back(next);
	}
	return result;
}

bool AnyInsertionRule::isApplicable(Word& word) const
{
	return true;
}
