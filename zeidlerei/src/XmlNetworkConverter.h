#pragma once
#include <string>

#include "Word.h"
#include "Network.h"
#include "Simulator.h"
#include "tinyxml2.h"

class XmlNetworkConverter
{
public:
	struct Result {
		Simulator simulator;
		Network network;
		std::vector<std::shared_ptr<HaltingCondition> > haltingConditions;
	};
	Result loadSimulation(const char* fileName, const char* configurationFileName = 0);
	void saveConfiguration(const Simulator& simulator, const Network& network, const char* fileName, const char* wordSeparator);
	void saveFullLog(std::vector<Simulator::Log> logs, const char* fileName, const char* wordSeparator);
	const char* stepTypeToString(Simulator::StepType stepType);
private:
	std::vector<Word> createWordset(const std::string& axiom, const std::string& separator);
	std::shared_ptr<Rule> createRuleInstance(tinyxml2::XMLElement* ruleElement, const std::string& ruleType);
	std::shared_ptr<Filter> createFilterInstance(tinyxml2::XMLElement* filterElement);
	std::shared_ptr<Processor> createProcessorInstance(tinyxml2::XMLElement* processorElement, const std::string& separator, const bool& hasConfiguration, const std::map<std::string, std::vector<Word> >& configurationWords);
	std::string convertMultisetToString(const Multiset<Word>& multiset, const char* wordSeparator);
	void insertConfigurationElement(tinyxml2::XMLDocument& doc, const Simulator::StepType& lastStepType, const Network::Configuration& configuration, const char* wordSeparator);
};