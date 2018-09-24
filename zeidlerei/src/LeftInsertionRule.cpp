#include "stdafx.h"
#include "LeftInsertionRule.h"

LeftInsertionRule::~LeftInsertionRule()
{
}

std::vector<Word> LeftInsertionRule::apply(Word& w) const {
	auto result = std::vector<Word>{ Word(_rhs + w.getContent()) };
	return result;
}

bool LeftInsertionRule::isApplicable(Word& w) const {
	return true;
}