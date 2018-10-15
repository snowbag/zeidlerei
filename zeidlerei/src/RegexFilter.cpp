#include "stdafx.h"
#include "RegexFilter.h"


RegexFilter::RegexFilter(const std::string& re)
	: regex_(re)
{
}

bool RegexFilter::apply(Word& word) const {
	return std::regex_match(word.getContent(), regex_);
}

