#include "stdafx.h"
#include "Processor.h"


Processor::Processor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
	const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter)
	: ruleSet_(ruleSet), inputFilter_(inputFilter), outputFilter_(outputFilter)
{
	for (auto w : initialSet) {
		wordSet_.add(w);
	}
}

void Processor::evolve()
{
	//TODO
}
