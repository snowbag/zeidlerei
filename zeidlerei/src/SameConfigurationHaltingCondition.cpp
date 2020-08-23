#include "SameConfigurationHaltingCondition.h"

SameConfigurationHaltingCondition::SameConfigurationHaltingCondition(const Network& network)
	: firstAlteringStep_ (network.exportConfiguration()), firstIsNext_(false), becameSame_(false)
{
}

void SameConfigurationHaltingCondition::calculate(const Network& network)
{
	auto currentConfiguration = network.exportConfiguration();
	if (firstIsNext_)
	{
		becameSame_ = firstAlteringStep_ == currentConfiguration;
		firstAlteringStep_ = currentConfiguration;
	}
	else
	{
		becameSame_ = secondAlteringStep_ == currentConfiguration;
		secondAlteringStep_ = currentConfiguration;
	}
	firstIsNext_ = !firstIsNext_;
}

bool SameConfigurationHaltingCondition::isTrue() const
{
	return becameSame_;
}
