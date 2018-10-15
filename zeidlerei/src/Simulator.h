#pragma once
#include "Network.h"
#include "HaltingCondition.h"

class Simulator
{
public:
	enum StepType { initial, evolution, communication };
	Simulator(const Network& network, const StepType& lastStepType = initial)
		: network_(network), lastStepType_(lastStepType) {}
	~Simulator();
	void executeSimulation(HaltingCondition& condition);
	void executeStep();
private:
	void executeEvolutionaryStep();
	void executeCommunicationStep();
	Network network_;
	StepType lastStepType_;
};

