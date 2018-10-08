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
	case evolutionary:
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
	//TODO
}