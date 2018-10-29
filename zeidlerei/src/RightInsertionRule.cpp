#include "RightInsertionRule.h"

std::vector<Word> RightInsertionRule::apply(Word& word) const {
	std::vector<Word> result = { word.getContent() + rhs_ };
	return result;
}

bool RightInsertionRule::isApplicable(Word& word) const {
	return true;
}