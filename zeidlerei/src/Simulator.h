#pragma once
#include "Network.h"
#include "HaltingCondition.h"

class Simulator
{
public:
	enum StepType { initial, evolution, communication };
	struct Log {
		StepType lastStepType;
		Network::Configuration configuration;
	};
	Simulator(const Network& network, const StepType& lastStepType = initial)
		: network_(network), lastStepType_(lastStepType) {}
	~Simulator();
	void executeSimulation(const std::vector<std::shared_ptr<HaltingCondition> > conditions);
	std::vector<Log> executeSimulationWithLog(const std::vector<std::shared_ptr<HaltingCondition> > conditions);
	void executeStep();
	StepType getLastStepType() const;
private:
	void executeEvolutionaryStep();
	void executeCommunicationStep();
	Network network_;
	StepType lastStepType_;
};

