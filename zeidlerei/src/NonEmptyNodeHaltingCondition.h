#pragma once
#include "HaltingCondition.h"

class NonEmptyNodeHaltingCondition : public HaltingCondition
{
public:
	NonEmptyNodeHaltingCondition(std::shared_ptr<Processor> outputNode);
	void calculate(const Network& network) override;
	bool isTrue() const override;
private:
	const Multiset<Word> emptySet_;
	std::shared_ptr<Processor> outputNode_;
	bool becameNonEmpty_;
};

