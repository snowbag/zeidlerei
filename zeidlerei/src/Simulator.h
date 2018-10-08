#pragma once
#include "Network.h"

class Simulator
{
public:
	enum StepType { initial, evolutionary, communication };
	Simulator(const Network& network, const StepType& lastStepType = initial) : network_(network), lastStepType_(lastStepType) {}
	~Simulator();
	void executeStep();
private:
	void executeEvolutionaryStep();
	void executeCommunicationStep();
	Network network_;
	StepType lastStepType_;
};

