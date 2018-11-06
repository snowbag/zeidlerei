#include "XmlNetworkConverter.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>


#include "tinyxml2.h"
#include "HaltingCondition.h"
#include "SameConfigurationHaltingCondition.h"
#include "MaximumStepsHaltingCondition.h"
#include "NonEmptyNodeHaltingCondition.h"
#include "Processor.h"
#include "ClusteredProcessor.h"
#include "LengthFilter.h"
#include "RegexFilter.h"
#include "FreeFilter.h"
#include "PermitForbidFilter.h"
#include "LeftDeletionRule.h"
#include "LeftInsertionRule.h"
#include "LeftSubstitutionRule.h"
#include "RightDeletionRule.h"
#include "RightInsertionRule.h"
#include "RightSubstitutionRule.h"
#include "AnyDeletionRule.h"
#include "AnyInsertionRule.h"
#include "AnySubstitutionRule.h"
#include "Network.h"
#include "Simulator.h"
#include "ClusteringProcess.h"
#include "Kmeans.h"
#include "BottomUpClustering.h"

const char* MAIN_TAG = "network";
const char* WORD_SEPARATOR_ATTR = "word-separator";
const char* DEFAULT_WORD_SEPARATOR = ",";
const char* PROCESSOR_GROUP_TAG = "processors";
const char* PROCESSOR_TAG = "node";
const char* PROCESSOR_ID_ATTR = "id";
const char* PROCESSOR_CONTENT_ATTR = "content";

const char* RULE_GROUP_TAG = "rules";
const char* RULE_TAG = "rule";
const char* RULE_TYPE_ATTR = "type";
const char* SUBSTITUTION_RULE_TYPE = "substitution";
const char* INSERTION_RULE_TYPE = "insertion";
const char* DELETION_RULE_TYPE = "deletion";
const char* RULE_POSITION_ATTR = "position";
const char* RULE_LEFT_POSITION_ATTR = "left";
const char* RULE_RIGHT_POSITION_ATTR = "right";
const char* RULE_ANY_POSITION_ATTR = "any";
const char* RULE_LHS = "from";
const char* RULE_RHS = "to";

const char* INPUT_FILTER_TAG = "inputfilter";
const char* OUTPUT_FILTER_TAG = "outputfilter";
const char* FILTER_TYPE_ATTR = "type";
const char* FILTER_DETAILS_ATTR = "rule";
const char* REGEX_FILTER_TYPE = "regex";
const char* LENGTH_FILTER_TYPE = "length";
const char* FREE_FILTER_TYPE = "free";
const char* PERMIT_FORBID_FILTER_TYPE = "permit-forbid";

const char* EDGE_GROUP_TAG = "graph";
const char* EDGE_TAG = "edge";
const char* EDGE_FIRST_VERTEX_ATTR = "v1";
const char* EDGE_SECOND_VERTEX_ATTR = "v2";

const char* HALTING_CONDITION_GROUP_TAG = "halting-conditions";
const char* HALTING_CONDITION_TAG = "condition";
const char* HALTING_CONDITION_TYPE_ATTR = "type";
const char* HALTING_CONDITION_DETAILS_ATTR = "value";
const char* MAXIMUM_STEPS_HALTING_CONDITION_TYPE = "MaximumNumberOfSteps";
const char* NONEMPTY_NODE_HALTING_CONDITION_TYPE = "NonEmptyNode";
const char* SAME_CONFIGURATION_HALTING_CONDITION_TYPE = "ConsecutiveConfigurations";

const char* CONFIGURATION_TAG = "configuration";
const char* CONFIGURATION_TYPE_ATTR = "type";
const char* INITIAL_CONFIGURATION_TYPE = "initial";
const char* EVOLUTION_CONFIGURATION_TYPE = "evolution";
const char* COMMUNICATION_CONFIGURATION_TYPE = "communication";

const char* CLUSTERING_TAG = "clustering";
const char* CLUSTERING_TYPE_ATTR = "method";
const char* KMEANS_CLUSTERING_TYPE = "k-means";
const char* BOTTOMUP_CLUSTERING_TYPE = "bottom-up";
const char* CLUSTERING_NUMBER_ATTR = "number";
const char* CLUSTERING_MAX_STEPS_ATTR = "max-steps";

const char* CLUSTER_GROUP_TAG = "clusters";
const char* CLUSTER_TAG = "cluster";
const char* CLUSTER_ID_ATTR = "id";
const char* CLUSTER_CONTENT_ATTR = "content";

using namespace tinyxml2;

std::vector<Word> XmlNetworkConverter::createWordset(const std::string& axiom, const std::string& separator) {
	std::vector<Word> words;
	auto start = 0U;
	auto end = axiom.find(separator);
	while (end != std::string::npos)
	{
		words.push_back(axiom.substr(start, end - start));
		start = end + separator.length();
		end = axiom.find(separator, start);
	}
	words.push_back(axiom.substr(start, end));
	return words;
}

std::shared_ptr<Rule> XmlNetworkConverter::createRuleInstance(XMLElement* ruleElement, const std::string& ruleType) {
	std::string position = ruleElement->Attribute(RULE_POSITION_ATTR);
	if (ruleType == INSERTION_RULE_TYPE) {
		std::string rhs = ruleElement->Attribute(RULE_RHS);
		if (position == RULE_LEFT_POSITION_ATTR) {
			return std::make_shared<LeftInsertionRule>(LeftInsertionRule(rhs));
		}
		else if (position == RULE_RIGHT_POSITION_ATTR) {
			return std::make_shared<RightInsertionRule>(RightInsertionRule(rhs));
		}
		else if (position == RULE_ANY_POSITION_ATTR) {
			return std::make_shared<AnyInsertionRule>(AnyInsertionRule(rhs));
		}
	}
	else if (ruleType == DELETION_RULE_TYPE) {
		std::string lhs = ruleElement->Attribute(RULE_LHS);
		if (position == RULE_LEFT_POSITION_ATTR) {
			return std::make_shared<LeftDeletionRule>(LeftDeletionRule(lhs));
		}
		else if (position == RULE_RIGHT_POSITION_ATTR) {
			return std::make_shared<RightDeletionRule>(RightDeletionRule(lhs));
		}
		else if (position == RULE_ANY_POSITION_ATTR) {
			return std::make_shared<AnyDeletionRule>(AnyDeletionRule(lhs));
		}
	}
	else if (ruleType == SUBSTITUTION_RULE_TYPE) {
		std::string lhs = ruleElement->Attribute(RULE_LHS);
		std::string rhs = ruleElement->Attribute(RULE_RHS);
		if (position == RULE_LEFT_POSITION_ATTR) {
			return std::make_shared<LeftSubstitutionRule>(LeftSubstitutionRule(lhs, rhs));
		}
		else if (position == RULE_RIGHT_POSITION_ATTR) {
			return std::make_shared<RightSubstitutionRule>(RightSubstitutionRule(lhs, rhs));
		}
		else if (position == RULE_ANY_POSITION_ATTR) {
			return std::make_shared<AnySubstitutionRule>(AnySubstitutionRule(lhs, rhs));
		}
	}
	throw std::domain_error("Unhandled rule type: " + ruleType);
}

std::shared_ptr<Filter> XmlNetworkConverter::createFilterInstance(XMLElement* filterElement) {
	std::shared_ptr<Filter> filter;
	if (!filterElement) {
		filter = std::make_shared<FreeFilter>(FreeFilter());
	}
	else {
		std::string filterType = filterElement->Attribute(FILTER_TYPE_ATTR);
		if (filterType == LENGTH_FILTER_TYPE) {
			std::string rule = filterElement->Attribute(FILTER_DETAILS_ATTR);
			LengthFilter::ComparisonType comparisonType;
			if (rule.at(0) == '=') {
				comparisonType = LengthFilter::ComparisonType::equals;
			}
			else if (rule.at(0) == '<') {
				comparisonType = LengthFilter::ComparisonType::lessThan;
			}
			else if (rule.at(0) == '>') {
				comparisonType = LengthFilter::ComparisonType::greaterThan;
			}
			else {
				throw std::domain_error("Unhandled comparison type in filter: " + rule);
			}
			int value = std::stoi(rule.substr(1));
			filter = std::make_shared<LengthFilter>(LengthFilter(comparisonType, value));
		}
		else if (filterType == REGEX_FILTER_TYPE) {
			std::string rule = filterElement->Attribute(FILTER_DETAILS_ATTR);
			filter = std::make_shared<RegexFilter>(RegexFilter(rule));
		}
		else if (filterType == FREE_FILTER_TYPE) {
			filter = std::make_shared<FreeFilter>(FreeFilter());
		}
		else if (filterType == PERMIT_FORBID_FILTER_TYPE) {
			std::string rule = filterElement->Attribute(FILTER_DETAILS_ATTR);
			filter = std::make_shared<PermitForbidFilter>(PermitForbidFilter(rule));
		}
		else {
			throw std::domain_error("Unhandled inputfilter type.");
		}
	}
	return filter;
}

std::shared_ptr<Processor> XmlNetworkConverter::createProcessorInstance(tinyxml2::XMLElement* processorNode, const std::string& separator, const bool& hasConfiguration, const std::map<std::string, std::vector<Word> >& configurationWords) {
	//axiom
	std::vector<Word> initialSet;
	if (hasConfiguration) {
		if (configurationWords.find(processorNode->Attribute(PROCESSOR_ID_ATTR)) != configurationWords.end()) {
			initialSet = configurationWords.at(processorNode->Attribute(PROCESSOR_ID_ATTR));
		}
	}
	else {
		const char* axiomAttribute = processorNode->Attribute(PROCESSOR_CONTENT_ATTR);
		initialSet = axiomAttribute ? createWordset(axiomAttribute, separator) : std::vector<Word>();
	}
	

	//rules
	std::vector<std::shared_ptr<Rule> > ruleSet;
	XMLElement* ruleElements = processorNode->FirstChildElement(RULE_GROUP_TAG);
	if (ruleElements) {
		std::string ruleType(ruleElements->Attribute(RULE_TYPE_ATTR));
		XMLElement* ruleElement = ruleElements->FirstChildElement(RULE_TAG);
		while (ruleElement) {
			ruleSet.push_back(createRuleInstance(ruleElement, ruleType));
			ruleElement = ruleElement->NextSiblingElement(RULE_TAG);
		}
	}
	//inputfilter
	std::shared_ptr<Filter> inputFilter(createFilterInstance(processorNode->FirstChildElement(INPUT_FILTER_TAG)));
	//outputfilter
	std::shared_ptr<Filter> outputFilter(createFilterInstance(processorNode->FirstChildElement(OUTPUT_FILTER_TAG)));
	//id
	std::string id = processorNode->Attribute(PROCESSOR_ID_ATTR);
	//clustering
	XMLElement* clusteringElement = processorNode->FirstChildElement(CLUSTERING_TAG);
	if (clusteringElement) {
		std::string type = clusteringElement->Attribute(CLUSTERING_TYPE_ATTR);
		int k = clusteringElement->IntAttribute(CLUSTERING_NUMBER_ATTR);
		int maxSteps = INT_MAX;
		if (clusteringElement->Attribute(CLUSTERING_MAX_STEPS_ATTR)) {
			maxSteps = clusteringElement->IntAttribute(CLUSTERING_MAX_STEPS_ATTR);
		}
		std::shared_ptr<ClusteringProcess> clusterer;
		if (type == KMEANS_CLUSTERING_TYPE) {
			clusterer = std::make_shared<Kmeans>(Kmeans(k, maxSteps));
		}
		else if (type == BOTTOMUP_CLUSTERING_TYPE) {
			clusterer = std::make_shared<BottomUpClustering>(BottomUpClustering(k, maxSteps));
		}
		else {
			throw std::domain_error("Unhandled clustering type.");
		}
		return std::make_shared<ClusteredProcessor>(ClusteredProcessor(initialSet, ruleSet, inputFilter, outputFilter, clusterer, id));
	}

	return std::make_shared<Processor>(Processor(initialSet, ruleSet, inputFilter, outputFilter, id));
}


XmlNetworkConverter::Result XmlNetworkConverter::loadSimulation(const char* fileName, const char* configurationFileName)
{
	XMLDocument doc;
	XMLDocument confDoc;

	auto result = doc.LoadFile(fileName);
	if (result != tinyxml2::XMLError::XML_SUCCESS) {
		throw std::domain_error("The file (" + std::string(fileName) + ") cannot be read as a NEP description. Error code: " + std::to_string(result));
	}


	Simulator::StepType lastStepType = Simulator::StepType::initial;
	std::map<std::string, std::vector<Word> > configurationWords;
	bool hasConfigurationFile = false;
	if (configurationFileName) {
		result = confDoc.LoadFile(configurationFileName);
		if (result != tinyxml2::XMLError::XML_SUCCESS) {
			throw std::domain_error("The file (" + std::string(configurationFileName) + ") cannot be read as a Configuration description. Error code: " + std::to_string(result));
		}
		XMLElement* configurationElement = confDoc.LastChildElement(CONFIGURATION_TAG);
		const char* separator = configurationElement->Attribute(WORD_SEPARATOR_ATTR);
		separator = separator ? separator : ",";
		std::string type = configurationElement->Attribute(CONFIGURATION_TYPE_ATTR) ? configurationElement->Attribute(CONFIGURATION_TYPE_ATTR) : "initial";
		if (type == INITIAL_CONFIGURATION_TYPE) {
			lastStepType = Simulator::StepType::initial;
		}
		else if (type == EVOLUTION_CONFIGURATION_TYPE) {
			lastStepType = Simulator::StepType::evolution;
		}
		else if (type == COMMUNICATION_CONFIGURATION_TYPE) {
			lastStepType = Simulator::StepType::communication;
		}
		else {
			throw std::domain_error("Unhandled last step type.");
		}
		XMLElement * processorElements = configurationElement->FirstChildElement(PROCESSOR_GROUP_TAG);
		XMLElement * processorNode = processorElements->FirstChildElement(PROCESSOR_TAG);
		while (processorNode) {
			const char* contentAttribute = processorNode->Attribute(PROCESSOR_CONTENT_ATTR);
			std::vector<Word> configurationSet = contentAttribute ? createWordset(contentAttribute, separator) : std::vector<Word>();
			configurationWords[processorNode->Attribute(PROCESSOR_ID_ATTR)] = configurationSet;
			processorNode = processorNode->NextSiblingElement(PROCESSOR_TAG);
		}
		hasConfigurationFile = true;
	}

	XMLElement * node = doc.FirstChildElement(MAIN_TAG);
	//load processors
	XMLElement * processorElements = node->FirstChildElement(PROCESSOR_GROUP_TAG);
	const char* separator = processorElements->Attribute(WORD_SEPARATOR_ATTR);
	separator = separator ? separator : DEFAULT_WORD_SEPARATOR;

	std::map<std::string, std::shared_ptr<Processor> > processorIdMap;
	XMLElement * processorNode = processorElements->FirstChildElement(PROCESSOR_TAG);

	std::vector<std::shared_ptr<Processor> > processors;
	while (processorNode) {
		auto processor = createProcessorInstance(processorNode, separator, hasConfigurationFile, configurationWords);
		processorIdMap[processorNode->Attribute(PROCESSOR_ID_ATTR)] = processor;
		processors.push_back(processor);
		processorNode = processorNode->NextSiblingElement(PROCESSOR_TAG);
	}

	std::vector<Network::Edge> edges;

	XMLElement* graphElements = node->FirstChildElement(EDGE_GROUP_TAG);
	XMLElement* edgeElement = graphElements->FirstChildElement(EDGE_TAG);
	while (edgeElement)
	{
		std::string v1Id = edgeElement->Attribute(EDGE_FIRST_VERTEX_ATTR);
		std::string v2Id = edgeElement->Attribute(EDGE_SECOND_VERTEX_ATTR);
		edges.push_back(Network::Edge(processorIdMap[v1Id], processorIdMap[v2Id]));
		edgeElement = edgeElement->NextSiblingElement(EDGE_TAG);
	}

	Network network(processors, edges);

	XMLElement * haltingConditions = node->FirstChildElement(HALTING_CONDITION_GROUP_TAG);
	XMLElement * haltingCondition = haltingConditions->FirstChildElement(HALTING_CONDITION_TAG);

	std::vector<std::shared_ptr<HaltingCondition> > conditions;

	while (haltingCondition)
	{
		std::string haltingConditionType = haltingCondition->Attribute(HALTING_CONDITION_TYPE_ATTR);
		if (haltingConditionType == SAME_CONFIGURATION_HALTING_CONDITION_TYPE) {
			conditions.push_back(std::make_shared<SameConfigurationHaltingCondition>(SameConfigurationHaltingCondition(network)));
		}
		else if (haltingConditionType == MAXIMUM_STEPS_HALTING_CONDITION_TYPE) {
			int numberOfSteps;
			haltingCondition->QueryIntAttribute(HALTING_CONDITION_DETAILS_ATTR, &numberOfSteps);
			conditions.push_back(std::make_shared<MaximumStepsHaltingCondition>(MaximumStepsHaltingCondition(numberOfSteps)));
		}
		else if (haltingConditionType == NONEMPTY_NODE_HALTING_CONDITION_TYPE) {
			std::shared_ptr<Processor> processor = processorIdMap[haltingCondition->Attribute(HALTING_CONDITION_DETAILS_ATTR)];
			conditions.push_back(std::make_shared<NonEmptyNodeHaltingCondition>(NonEmptyNodeHaltingCondition(processor)));
		}
		else {
			throw std::domain_error("Unhandled halting condition type.");
		}
		haltingCondition = haltingCondition->NextSiblingElement(HALTING_CONDITION_TAG);
	}

	return Result{ Simulator(network, lastStepType), network, conditions };
}

void XmlNetworkConverter::saveFullLog(std::vector<Simulator::Log> logs, const char* fileName, const char* wordSeparator)
{
	XMLDocument doc;
	for (auto&& l : logs) {
		insertNetworkConfigurationElement(doc, l.lastStepType, l.configuration, wordSeparator);
	}
	doc.SaveFile(fileName);
}

void XmlNetworkConverter::saveConfiguration(const Simulator& simulator, const Network& network, const char* fileName, const char* wordSeparator)
{
	XMLDocument doc;
	Simulator::StepType lastStepType = simulator.getLastStepType();
	Network::Configuration configuration = network.exportConfiguration();
	insertNetworkConfigurationElement(doc, lastStepType, configuration, wordSeparator);
	doc.SaveFile(fileName);
}

void XmlNetworkConverter::ProcessorConfigurationConverter::insertElement(XMLDocument& doc, XMLElement* parentNode, const ClusteredProcessor::Configuration& configuration, const char* wordSeparator)
{
	XMLElement* nodeElement = doc.NewElement(PROCESSOR_TAG);
	nodeElement->SetAttribute(PROCESSOR_ID_ATTR, configuration.processorId.c_str());
	std::string content = convertMultisetToString(configuration.wordSet, wordSeparator);
	nodeElement->SetAttribute(PROCESSOR_CONTENT_ATTR, content.c_str());
	XMLElement* clustersElement = doc.NewElement(CLUSTER_GROUP_TAG);
	nodeElement->InsertEndChild(clustersElement);
	for (int i=0;i<configuration.clusters.size();++i)
	{
		XMLElement* clusterElement = doc.NewElement(CLUSTER_TAG);
		clusterElement->SetAttribute(CLUSTER_ID_ATTR, i);
		std::string clusterContent = convertVectorToString(configuration.clusters[i].points, wordSeparator);
		clusterElement->SetAttribute(CLUSTER_CONTENT_ATTR, clusterContent.c_str());
		clustersElement->InsertEndChild(clusterElement);
	}
	parentNode->InsertEndChild(nodeElement);
}
void XmlNetworkConverter::ProcessorConfigurationConverter::insertElement(XMLDocument& doc, XMLElement* parentNode, const Processor::Configuration& configuration, const char* wordSeparator)
{
	XMLElement* nodeElement = doc.NewElement(PROCESSOR_TAG);
	nodeElement->SetAttribute(PROCESSOR_ID_ATTR, configuration.processorId.c_str());
	std::string content = convertMultisetToString(configuration.wordSet, wordSeparator);
	nodeElement->SetAttribute(PROCESSOR_CONTENT_ATTR, content.c_str());
	parentNode->InsertEndChild(nodeElement);
}

void XmlNetworkConverter::insertNetworkConfigurationElement(XMLDocument& doc, const Simulator::StepType& lastStepType, const Network::Configuration& configuration, const char* wordSeparator)
{
	XMLElement* configurationElement = doc.NewElement(CONFIGURATION_TAG);
	const char* stepTypeAttr = stepTypeToString(lastStepType);
	configurationElement->SetAttribute(CONFIGURATION_TYPE_ATTR, stepTypeAttr);
	configurationElement->SetAttribute(WORD_SEPARATOR_ATTR, wordSeparator);
	doc.InsertEndChild(configurationElement);
	XMLElement* processorsElement = doc.NewElement(PROCESSOR_GROUP_TAG);
	configurationElement->InsertEndChild(processorsElement);
	ProcessorConfigurationConverter converter { doc, processorsElement, wordSeparator };
	for (auto&& pc : configuration.nodes) {
		pc->accept(&converter);
	}
}

std::string XmlNetworkConverter::convertVectorToString(const std::vector<Word>& words, const char* wordSeparator) {
	std::ostringstream os;
	const char* separator = "";
	for (auto&& w : words) {
		os << separator << w.getContent();
		separator = wordSeparator;
	}
	return os.str();
}

std::string XmlNetworkConverter::convertMultisetToString(const Multiset<Word>& multiset, const char* wordSeparator) {
	std::ostringstream os;
	const char* separator = "";
	for (auto&& p : multiset) {
		for (int i = 0; i < p.second; ++i) {
			os << separator << p.first.getContent();
			separator = wordSeparator;
		}
	}
	return os.str();
}

const char* XmlNetworkConverter::stepTypeToString(Simulator::StepType stepType)
{
	switch (stepType) {
	case Simulator::StepType::initial:
		return INITIAL_CONFIGURATION_TYPE; break;
	case Simulator::StepType::evolution:
		return EVOLUTION_CONFIGURATION_TYPE; break;
	case Simulator::StepType::communication:
		return COMMUNICATION_CONFIGURATION_TYPE; break;
	default:
		throw std::domain_error("Unhandled last step type.");
	}
}

int main(int argc, char** argv)
{
	const char* nepFilename = 0;
	const char* configFilename = 0;
	const char* outputFilename = 0;
	const char* wordSeparator = DEFAULT_WORD_SEPARATOR;
	bool outputAll = false;
	if (argc > 1) {
		nepFilename = argv[1];
	}
	for (int i = 0; i < argc; ++i) {
		if (i + 1 < argc && strcmp(argv[i], "-c") == 0) {
			configFilename = argv[i + 1];
			++i;
		}
		if (i + 1 < argc && strcmp(argv[i], "-o") == 0) {
			outputFilename = argv[i+1];
			++i;
		}
		if (i + 1 < argc && strcmp(argv[i], "-s") == 0) {
			wordSeparator = argv[i + 1];
			++i;
		}
		if (strcmp(argv[i], "--outputall") == 0) {
			outputAll = true;
		}

	}

	try
	{
		XmlNetworkConverter xnc;
		auto result = xnc.loadSimulation(nepFilename, configFilename);
		if (outputAll) {
			auto log = result.simulator.executeSimulationWithLog(result.haltingConditions);
			if (outputFilename) {
				xnc.saveFullLog(log, outputFilename, wordSeparator);
			}
			else {
				for (int i = 0; i < log.size(); ++i) {
					std::cout << "Step " << i + 1 << " (" << xnc.stepTypeToString(log[i].lastStepType) << ")" << std::endl;
					std::cout << log[i].configuration << std::endl;
				}
			}
		}
		else {
			result.simulator.executeSimulation(result.haltingConditions);
			if (outputFilename) {
				xnc.saveConfiguration(result.simulator, result.network, outputFilename, wordSeparator);
			}
			else {
				std::cout << "Last step: " << xnc.stepTypeToString(result.simulator.getLastStepType()) << std::endl;
				std::cout << result.network.exportConfiguration() << std::endl;
			}
		}
	}
	catch (std::domain_error& ex) {
		std::cout << "An error occured:" << std::endl;
		std::cout << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "The simulation cannot be run. Your XML file is not available or not in a proper format." << std::endl;
	}
}