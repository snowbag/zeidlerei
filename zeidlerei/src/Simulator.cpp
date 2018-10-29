#include "Simulator.h"

#include <algorithm>

Simulator::~Simulator()
{
}

void Simulator::executeSimulation(const std::vector<std::shared_ptr<HaltingCondition> > conditions)
{
	while (std::none_of(conditions.begin(), conditions.end(), [](std::shared_ptr<HaltingCondition> c) {return c->isTrue(); }))
	{
		executeStep();
		std::for_each(conditions.begin(), conditions.end(), [&network = network_](std::shared_ptr<HaltingCondition> c) {return c->calculate(network); });
	}
}

std::vector<Simulator::Log> Simulator::executeSimulationWithLog(const std::vector<std::shared_ptr<HaltingCondition> > conditions)
{
	std::vector<Log> logs;
	while (std::none_of(conditions.begin(), conditions.end(), [](std::shared_ptr<HaltingCondition> c) {return c->isTrue(); }))
	{
		executeStep();
		std::for_each(conditions.begin(), conditions.end(), [&network = network_](std::shared_ptr<HaltingCondition> c) {return c->calculate(network); });
		logs.push_back(Log{ lastStepType_, network_.exportConfiguration() });
	}
	return logs;
}

void Simulator::executeStep()
{
	switch (lastStepType_)
	{
	case initial:
	case communication:
		executeEvolutionaryStep();
		lastStepType_ = evolution;
		break;
	case evolution:
		executeCommunicationStep();
		lastStepType_ = communication;
		break;
	default:
		throw std::domain_error("Unhandled step type.");
	}
	
}

void Simulator::executeEvolutionaryStep()
{
	for (auto processor : network_.getProcessors())
	{
		processor->evolve();
	}
}

void Simulator::executeCommunicationStep()
{
	for (auto processor : network_.getProcessors())
	{
		processor->collectOutput();
	}
	for (auto processor : network_.getProcessors())
	{
		auto message = processor->flushOutput();
		for (auto neighbour : network_.getNeighbours(processor))
		{
			neighbour->receive(message);
		}
	}
}

Simulator::StepType Simulator::getLastStepType() const {
	return lastStepType_;
}