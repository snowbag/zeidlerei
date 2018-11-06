#pragma once
#include "Rule.h"

class AnySubstitutionRule :
	public Rule
{
public:
	AnySubstitutionRule(const std::string& lhs, const std::string& rhs) : Rule(lhs, rhs) {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};

