#include "stdafx.h"
#include "RightInsertionRule.h"


RightInsertionRule::~RightInsertionRule()
{
}

std::vector<Word> RightInsertionRule::apply(Word& w) const {
	auto result = std::vector<Word>{ w.getContent() + _rhs };
	return result;
}

bool RightInsertionRule::isApplicable(Word& w) const {
	return true;
}