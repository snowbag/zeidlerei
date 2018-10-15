#pragma once
#include "HaltingCondition.h"

class NonEmptyNodeHaltingCondition : public HaltingCondition
{
public:
	NonEmptyNodeHaltingCondition(Processor* outputNode);
	void calculate(const Network& network) override;
	bool isTrue() const override;
private:
	const Multiset<Word> emptySet_;
	Processor* outputNode_;
	bool becameNonEmpty_;
};

