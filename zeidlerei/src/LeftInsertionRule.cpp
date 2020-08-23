#include "LeftInsertionRule.h"

std::vector<Word> LeftInsertionRule::apply(Word& word) const {
	std::vector<Word> result = { Word(rhs_ + word.getContent()) };
	return result;
}

bool LeftInsertionRule::isApplicable(Word& word) const {
	return true;
}