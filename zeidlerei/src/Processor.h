#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>

#include "Word.h"
#include "Rule.h"
#include "Filter.h"
#include "Multiset.h"

class ConfigurationVisitor;

class Processor
{
public:
	struct Configuration {
		std::string processorId;
		Multiset<Word> wordSet;
		Configuration(const std::string processorId, const Multiset<Word>& wordSet) : processorId(processorId), wordSet(wordSet) {}
		friend std::ostream& operator<< (std::ostream& stream, const Configuration& config) {
			stream << "processor id: " << (config.processorId != "" ? config.processorId : "none") << "\n";
			for (auto p : config.wordSet)
			{
				stream << "word: " << p.first.getContent() << "; count: " << p.second << "\n";
			}
			return stream;
		}

		virtual bool operator==(const Configuration& other) const {
			return wordSet == other.wordSet;
		}

		virtual bool operator!=(const Configuration& other) const {
			return !(*this == other);
		}

		virtual void accept(ConfigurationVisitor* visitor);
	};

	Processor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
		const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter, const std::string& id = "");
	virtual void evolve();
	virtual void receive(const Multiset<Word>& inputWords);
	virtual void collectOutput();
	virtual Multiset<Word> flushOutput();
	virtual std::shared_ptr<Configuration> exportConfiguration();
	std::string getId() { return id_; }
protected:
	Multiset<Word> wordSet_;
	std::vector<std::shared_ptr<Rule> > ruleSet_;
	std::shared_ptr<Filter> inputFilter_;
	std::shared_ptr<Filter> outputFilter_;
	Multiset<Word> output_;
	std::string id_;
};

