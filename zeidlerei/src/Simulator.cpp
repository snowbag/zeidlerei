#include "stdafx.h"
#include "Simulator.h"

Simulator::~Simulator()
{
}

void Simulator::executeStep()
{
	switch (lastStepType_)
	{
	case initial:
	case communication:
		executeEvolutionaryStep();
		break;
	case evolution:
		executeCommunicationStep();
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