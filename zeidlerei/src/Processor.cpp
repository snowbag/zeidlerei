#include "stdafx.h"
#include "Processor.h"


Processor::Processor(std::vector<Word>& initial_set, std::vector<std::shared_ptr<Rule> >& rule_set,
	std::shared_ptr<Filter> inputFilter, std::shared_ptr<Filter> outputFilter)
	: _ruleSet(rule_set), _inputFilter(inputFilter), _outputFilter(outputFilter)
{
	for (auto w : initial_set) { //TODO: define multiset
		_wordSet[w] = 1;
	}
}


Processor::~Processor()
{
}

void Processor::evolve()
{
	std::vector<Word> remaining;
	for (auto w : _wordSet)
	{
		for (auto r : _ruleSet) {
			//if (r->isApplicable(w)) {
			//}
		}
	}
}
