#pragma once
#include "HaltingCondition.h"

class SameConfigurationHaltingCondition :
	public HaltingCondition
{
public:
	SameConfigurationHaltingCondition(const Network& network);
	void calculate(const Network& network) override;
	bool isTrue() const override;
private:
	Network::Configuration firstAlteringStep_;
	Network::Configuration secondAlteringStep_;
	bool firstIsNext_;
	bool becameSame_;
};

