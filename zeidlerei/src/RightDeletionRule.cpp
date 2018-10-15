#include "stdafx.h"
#include "RightDeletionRule.h"


std::vector<Word> RightDeletionRule::apply(Word& word) const
{
	if (isApplicable(word))
	{
		int len = word.getContent().length() - lhs_.length();
		return std::vector<Word> { word.getContent().substr(0, len) };
	}
}

bool RightDeletionRule::isApplicable(Word& word) const
{
	int pos = word.getContent().length() - lhs_.length();
	return word.getContent().substr(pos) == lhs_;
}