#pragma once
#include <vector>
#include <map>
#include <memory>

#include "Word.h"
#include "Rule.h"
#include "Filter.h"
#include "Multiset.h"

class Processor
{
public:
	Processor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
		const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter);
	virtual void evolve();
protected:
	Multiset<Word> wordSet_;
	std::vector<std::shared_ptr<Rule> > ruleSet_;
	std::shared_ptr<Filter> inputFilter_;
	std::shared_ptr<Filter> outputFilter_;
};

