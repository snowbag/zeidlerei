#pragma once
#include "Rule.h"
class LeftDeletionRule :
	public Rule
{
public:
	LeftDeletionRule(const std::string& lhs) : Rule(lhs, "") {}
	std::vector<Word> apply(Word& word) const override;
	bool isApplicable(Word& word) const override;
};