#include "LeftDeletionRule.h"

std::vector<Word> LeftDeletionRule::apply(Word& word) const
{
	if (isApplicable(word))
	{
		return std::vector<Word> { word.getContent().substr(lhs_.length()) };
	}
}

bool LeftDeletionRule::isApplicable(Word& word) const
{
	return word.getContent().substr(0,lhs_.length()) == lhs_;
}