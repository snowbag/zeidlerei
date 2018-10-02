#include "stdafx.h"
#include <iostream>
#include <memory>

#include "Word.h"
#include "Rule.h"
#include "LeftInsertionRule.h"
#include "FreeFilter.h"
#include "Processor.h"

#include "gtest/gtest.h"

TEST(Processors, EvolveWords) {
	std::vector<Word> init = { Word(""), Word("a") };
	std::vector<std::shared_ptr<Rule> > ruleSet;
	ruleSet.push_back(std::make_shared<LeftInsertionRule>(LeftInsertionRule("a")));
	ruleSet.push_back(std::make_shared<LeftInsertionRule>(LeftInsertionRule("aa")));

	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());

	Processor p(init, ruleSet, freeFilter, freeFilter);
	
	Multiset<Word> expected;
	expected.add(Word("a"));
	expected.add(Word("aa"));
	expected.add(Word("aaa"));

	p.evolve();
	Processor::Configuration config = p.exportConfiguration();
	ASSERT_EQ(config.wordSet, expected);
}