#include "Processor.h"

#include <set>

#include "Visitor.h"

Processor::Processor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
	const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter, const std::string& id)
	: ruleSet_(ruleSet), inputFilter_(inputFilter), outputFilter_(outputFilter), id_(id)
{
	for (auto w : initialSet) {
		wordSet_.add(w);
	}
}

void Processor::evolve()
{
	std::set<Word> usedWords;
	Multiset<Word> createdWords;
	for (auto p : wordSet_) { //TODO: iterator on wordset keys
		Word w = p.first;
		for (auto r : ruleSet_) {
			if (r->isApplicable(w)) {
				usedWords.insert(w);
				auto result = r->apply(w);
				for (auto&& newWord : result) {
					createdWords.add(newWord, p.second);
				}
			}
		}
	}

	for (auto p : wordSet_) {
		Word w = p.first;
		if (usedWords.count(w) == 0) {
			createdWords.add(w, p.second);
		}
	}

	wordSet_.clear();
	wordSet_ = createdWords;
}

void Processor::receive(const Multiset<Word>& inputWords)
{
	for (auto p : inputWords) {
		Word w = p.first;
		if (inputFilter_->apply(w)) {
			wordSet_.add(w, p.second);
		}
	}
}

void Processor::collectOutput()
{
	Multiset<Word> remainingWords; //TODO: iterating on a separate vector of words as keys -> no need to create new multiset
	for (auto p : wordSet_) {
		Word w = p.first;
		if (outputFilter_->apply(w)) {
			output_.add(w, p.second);
		}
		else {
			remainingWords.add(w, p.second);
		}
	}
	wordSet_ = remainingWords;
}

Multiset<Word> Processor::flushOutput()
{
	Multiset<Word> sentWords = output_; //TODO move constructor?
	output_.clear();
	return sentWords;
}

std::shared_ptr<Processor::Configuration> Processor::exportConfiguration()
{
	return std::make_shared<Configuration>(id_, wordSet_);
}

void Processor::Configuration::accept(ConfigurationVisitor* visitor) {
	return visitor->visit(*this);
}