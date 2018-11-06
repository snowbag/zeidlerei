#pragma once
#include <string>

#include "Word.h"
#include "Network.h"
#include "Simulator.h"
#include "tinyxml2.h"
#include "ClusteredProcessor.h"
#include "Visitor.h"

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
	class ProcessorConfigurationConverter : public ConfigurationVisitor
	{
	public:
		tinyxml2::XMLDocument& doc;
		tinyxml2::XMLElement* parentNode;
		const char* wordSeparator;

		ProcessorConfigurationConverter(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentNode, const char* wordSeparator)
			: doc(doc), parentNode(parentNode), wordSeparator(wordSeparator) {}

		void insertElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentNode, const ClusteredProcessor::Configuration& configuration, const char* wordSeparator);
		void insertElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* parentNode, const Processor::Configuration& configuration, const char* wordSeparator);

		virtual void visit(const Processor::Configuration& configuration)
		{
			insertElement(doc, parentNode, configuration, wordSeparator);
		}
		virtual void visit(const ClusteredProcessor::Configuration& configuration)
		{
			insertElement(doc, parentNode, configuration, wordSeparator);
		}
	};

	std::vector<Word> createWordset(const std::string& axiom, const std::string& separator);
	std::shared_ptr<Rule> createRuleInstance(tinyxml2::XMLElement* ruleElement, const std::string& ruleType);
	std::shared_ptr<Filter> createFilterInstance(tinyxml2::XMLElement* filterElement);
	std::shared_ptr<Processor> createProcessorInstance(tinyxml2::XMLElement* processorElement, const std::string& separator, const bool& hasConfiguration, const std::map<std::string, std::vector<Word> >& configurationWords);
	static std::string convertVectorToString(const std::vector<Word>& words, const char* wordSeparator);
	static std::string convertMultisetToString(const Multiset<Word>& multiset, const char* wordSeparator);
	void insertNetworkConfigurationElement(tinyxml2::XMLDocument& doc, const Simulator::StepType& lastStepType, const Network::Configuration& configuration, const char* wordSeparator);
};