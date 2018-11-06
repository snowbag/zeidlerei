#pragma once
#include "Rule.h"

class AnyDeletionRule :
	public Rule
{
public:
	AnyDeletionRule(const std::string& lhs) : Rule(lhs, "") {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};

