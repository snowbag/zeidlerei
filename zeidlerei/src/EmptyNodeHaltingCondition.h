#pragma once
#include "HaltingCondition.h"

class EmptyNodeHaltingCondition : public HaltingCondition
{
public:
	EmptyNodeHaltingCondition(std::shared_ptr<Processor> outputNode);
	void calculate(const Network& network) override;
	bool isTrue() const override;
private:
	const Multiset<Word> emptySet_;
	std::shared_ptr<Processor> outputNode_;
	bool becameEmpty_;
};
