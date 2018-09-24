#include "stdafx.h"
#include "LeftDeletionRule.h"


LeftDeletionRule::~LeftDeletionRule()
{
}

std::vector<Word> LeftDeletionRule::apply(Word& w) const
{
	if (isApplicable(w))
	{
		return std::vector<Word> { w.getContent().substr(_lhs.length()) };
	}
}

bool LeftDeletionRule::isApplicable(Word& w) const
{
	return w.getContent().substr(0,_lhs.length()) == _lhs;
}