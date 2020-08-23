#include "MaximumStepsHaltingCondition.h"

MaximumStepsHaltingCondition::MaximumStepsHaltingCondition(const int& steps) : stepsLeft_(steps)
{
}

void MaximumStepsHaltingCondition::calculate(const Network& network)
{
	--stepsLeft_;
}

bool MaximumStepsHaltingCondition::isTrue() const
{
	return stepsLeft_ <= 0;
}