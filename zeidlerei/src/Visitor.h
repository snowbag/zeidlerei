#pragma once
#include "Processor.h"
#include "ClusteredProcessor.h"

class ConfigurationVisitor {
public:
	virtual void visit(const Processor::Configuration& configuration) = 0;
	virtual void visit(const ClusteredProcessor::Configuration& configuration) = 0;
};