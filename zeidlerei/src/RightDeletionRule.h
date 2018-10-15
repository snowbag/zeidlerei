#pragma once
#include "Rule.h"
//TODO it's actually RightSubstitutionRule to ""
class RightDeletionRule :
	public Rule
{
public:
	RightDeletionRule(const std::string& lhs) : Rule(lhs, "") {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};

