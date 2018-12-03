#pragma once
#include "Simulator.h"

class LoggingSimulator : public Simulator
{
public:
	struct CommunicationSummary {
		std::string processorId;
		int numberOfReceived;
		int numberOfSent;
	};

	LoggingSimulator(const Network& network, const StepType& lastStepType = initial)
		: Simulator(network, lastStepType) {}

	virtual void executeSimulation(const std::vector<std::shared_ptr<HaltingCondition> > conditions) override;
	std::vector<Log> getLogs() { return logs_; }
	std::vector<std::vector<CommunicationSummary> > getSummaries() { return summaries_; }
protected:
	virtual void executeCommunicationStep() override;
	std::vector<Log> logs_;
	std::vector<std::vector<CommunicationSummary> > summaries_;
};

