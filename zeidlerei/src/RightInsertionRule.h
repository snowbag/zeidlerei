#pragma once
#include "Rule.h"
class RightInsertionRule :
	public Rule
{
public:
	RightInsertionRule(const std::string& rhs) : Rule("", rhs) {}
	~RightInsertionRule();
	std::vector<Word> apply(Word& w) const override;
	bool isApplicable(Word& w) const override;
};

