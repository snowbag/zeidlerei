#include "LoggingSimulator.h"

void LoggingSimulator::executeSimulation(const std::vector<std::shared_ptr<HaltingCondition> > conditions)
{
	logs_.clear();
	summaries_.clear();
	while (std::none_of(conditions.begin(), conditions.end(), [](std::shared_ptr<HaltingCondition> c) {return c->isTrue(); }))
	{
		executeStep();
		std::for_each(conditions.begin(), conditions.end(), [&network = network_](std::shared_ptr<HaltingCondition> c) {return c->calculate(network); });
		logs_.push_back(Log{ lastStepType_, network_.exportConfiguration() });
	}
}

void LoggingSimulator::executeCommunicationStep()
{
	std::map<std::shared_ptr<Processor>, int> numberOfSentWords;
	std::map<std::shared_ptr<Processor>, int> numberOfReceivedWords;
	for (auto&& processor : network_.getProcessors())
	{
		processor->collectOutput();
	}
	for (auto&& processor : network_.getProcessors())
	{
		auto message = processor->flushOutput();
		int size = message.size();

		numberOfSentWords[processor] = size;
		for (auto&& neighbour : network_.getNeighbours(processor))
		{
			neighbour->receive(message);
			numberOfReceivedWords[neighbour] += size;
		}
	}

	std::vector<CommunicationSummary> summary;
	for (auto&& processor : network_.getProcessors()) {
		summary.push_back({ processor->getId(), numberOfSentWords[processor], numberOfReceivedWords[processor] });
	}
	summaries_.push_back(summary);
}