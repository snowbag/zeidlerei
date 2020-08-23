#pragma once
#include <vector>

#include "Word.h"

class Rule
{
public:
	Rule(const std::string& lhs, const std::string& rhs) : lhs_(lhs), rhs_(rhs) {}
	~Rule() {}
	virtual std::vector<Word> apply(Word& word) const = 0;
	virtual bool isApplicable(Word& word) const { return false; }
protected:
	std::string lhs_;
	std::string rhs_;
};

