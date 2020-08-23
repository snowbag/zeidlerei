#pragma once
#include "Filter.h"

class LengthFilter : public Filter
{
public:
	enum ComparisonType { lessThan, equals, greaterThan };
	LengthFilter(const ComparisonType& comparisonType, const int& value);
	bool apply(Word& word) const override;
private:
	int value_;
	ComparisonType comparisonType_;
};

