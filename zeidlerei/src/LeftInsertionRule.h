#pragma once
#include "Rule.h"
class LeftInsertionRule :
	public Rule
{
public:
	LeftInsertionRule(const std::string& rhs) : Rule("", rhs) {}
	~LeftInsertionRule();
	std::vector<Word> apply(Word& w) const override;
	bool isApplicable(Word& w) const override;
};

