#pragma once
#include <vector>
#include <map>
#include <memory>

#include "Word.h"
#include "Rule.h"
#include "Filter.h"

class Processor
{
public:
	Processor(std::vector<Word>& initial_set, std::vector<std::shared_ptr<Rule> >& rule_set,
		std::shared_ptr<Filter> inputFilter, std::shared_ptr<Filter> outputFilter);
	~Processor();
	virtual void evolve();
protected:
	std::map<Word, int> _wordSet;
	std::vector<std::shared_ptr<Rule> >& _ruleSet;
	std::shared_ptr<Filter> _inputFilter;
	std::shared_ptr<Filter> _outputFilter;
};

