#pragma once
#include "Rule.h"
class RightInsertionRule :
	public Rule
{
public:
	RightInsertionRule(const std::string& rhs) : Rule("", rhs) {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};

