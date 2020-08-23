#pragma once
#include "Rule.h"

class AnyInsertionRule :
	public Rule
{
public:
	AnyInsertionRule(const std::string& rhs) : Rule("", rhs) {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};

