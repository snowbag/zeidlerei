#pragma once
#include "Rule.h"
class LeftDeletionRule :
	public Rule
{
public:
	LeftDeletionRule(const std::string& lhs) : Rule(lhs, "") {}
	~LeftDeletionRule();
	std::vector<Word> apply(Word& w) const override;
	bool isApplicable(Word& w) const override;
};

