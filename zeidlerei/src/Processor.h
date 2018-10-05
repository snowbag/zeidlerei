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
	struct Configuration {
		Multiset<Word> wordSet;
		Configuration(const Multiset<Word>& wordSet) : wordSet(wordSet) {}
		friend std::ostream& operator<< (std::ostream& stream, const Configuration& config) {
			for (auto p : config.wordSet)
			{
				stream << "word: " << p.first.getContent() << "; count: " << p.second << "\n";
			}
			return stream;
		}
	};

	Processor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
		const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter);
	virtual void evolve();
	virtual void receiveInputWords(const Multiset<Word>& inputWords);
	virtual Multiset<Word> getOutputWords();
	virtual Configuration exportConfiguration();
protected:
	Multiset<Word> wordSet_;
	std::vector<std::shared_ptr<Rule> > ruleSet_;
	std::shared_ptr<Filter> inputFilter_;
	std::shared_ptr<Filter> outputFilter_;
};

