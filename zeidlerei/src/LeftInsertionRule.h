#pragma once
#include "Rule.h"
class LeftInsertionRule :
	public Rule
{
public:
	LeftInsertionRule(const std::string& rhs) : Rule("", rhs) {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};

