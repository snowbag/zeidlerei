#include "stdafx.h"
#include "Processor.h"

#include <set>


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
	std::set<Word> usedWords;
	std::set<Word> createdWords;
	for (auto p : wordSet_) {
		Word w = p.first;
		for (auto r : ruleSet_) {
			if (r->isApplicable(w)) {
				usedWords.insert(w);
				auto result = r->apply(w);
				createdWords.insert(result.begin(),result.end());
			}
		}
	}

	for (auto p : wordSet_) {
		Word w = p.first;
		if (usedWords.count(w) == 0) {
			createdWords.insert(w);
		}
	}

	wordSet_.clear();

	for (auto w : createdWords) {
		wordSet_.add(w);
	}
}

Processor::Configuration Processor::exportConfiguration()
{
	return Configuration(wordSet_);
}
