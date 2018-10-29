#include "NonEmptyNodeHaltingCondition.h"


NonEmptyNodeHaltingCondition::NonEmptyNodeHaltingCondition(std::shared_ptr<Processor> outputNode)
	: outputNode_(outputNode), becameNonEmpty_(false)
{
}

void NonEmptyNodeHaltingCondition::calculate(const Network& network)
{
	auto content = outputNode_->exportConfiguration();
	becameNonEmpty_ |= content.wordSet != emptySet_;
}

bool NonEmptyNodeHaltingCondition::isTrue() const
{
	return becameNonEmpty_;
}
