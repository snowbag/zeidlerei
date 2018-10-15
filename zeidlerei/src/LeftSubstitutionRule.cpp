#include "stdafx.h"
#include "LeftSubstitutionRule.h"


std::vector<Word> LeftSubstitutionRule::apply(Word& word) const
{
	if (isApplicable(word))
	{
		return std::vector<Word> { rhs_ + word.getContent().substr(lhs_.length()) };
	}
}

bool LeftSubstitutionRule::isApplicable(Word& word) const
{
	return word.getContent().substr(0, lhs_.length()) == lhs_;
}