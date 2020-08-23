#include "EmptyNodeHaltingCondition.h"



EmptyNodeHaltingCondition::EmptyNodeHaltingCondition(std::shared_ptr<Processor> outputNode)
	: outputNode_(outputNode), becameEmpty_(false)
{
}

void EmptyNodeHaltingCondition::calculate(const Network& network)
{
	auto content = outputNode_->exportConfiguration();
	becameEmpty_ |= content->wordSet == emptySet_;
}

bool EmptyNodeHaltingCondition::isTrue() const
{
	return becameEmpty_;
}
