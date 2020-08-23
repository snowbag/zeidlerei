#include "AnyDeletionRule.h"



std::vector<Word> AnyDeletionRule::apply(Word& word) const
{
	if (isApplicable(word))
	{
		std::vector<Word> result;
		std::string content = word.getContent();
		int i = 0, m;
		const int lhsSize = lhs_.size();
		while (m = content.find(lhs_, i), m != std::string::npos) {
			std::string next = content;
			next.erase(m, lhsSize);
			result.push_back(next);
			i = m + 1;
		}
		return result;
	}
}

bool AnyDeletionRule::isApplicable(Word& word) const
{
	return word.getContent().find(lhs_) != std::string::npos;
}