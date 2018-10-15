#include "stdafx.h"
#include "LengthFilter.h"


LengthFilter::LengthFilter(const ComparisonType& comparisonType, const int& value)
	: value_(value), comparisonType_(comparisonType)
{
}


bool LengthFilter::apply(Word& word) const
{
	switch (comparisonType_)
	{
	case lessThan:
		return word.getContent().size() < value_;
	case equals:
		return word.getContent().size() == value_;
	case greaterThan:
		return word.getContent().size() > value_;
	default:
		throw std::domain_error("Unhandled comparison type.");
	}
}
