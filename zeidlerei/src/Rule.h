#pragma once
#include <vector>
#include <Word.h>

class Rule
{
public:
	Rule(const std::string& lhs, const std::string& rhs) : _lhs(lhs), _rhs(rhs) {}
	~Rule();
	virtual std::vector<Word> apply(Word& w) const = 0;
	virtual bool isApplicable(Word& w) const { return false; }
protected:
	std::string _lhs;
	std::string _rhs;
};

