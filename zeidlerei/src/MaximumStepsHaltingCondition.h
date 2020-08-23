#pragma once
#include "HaltingCondition.h"

class MaximumStepsHaltingCondition : public HaltingCondition
{
public:
	MaximumStepsHaltingCondition(const int& steps);
	void calculate(const Network& network) override;
	bool isTrue() const override;
private:
	int stepsLeft_;
};

