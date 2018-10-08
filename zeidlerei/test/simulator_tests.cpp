#include "stdafx.h"  
#include <iostream>

#include "Simulator.h"
#include "FreeFilter.h"
#include "RightInsertionRule.h"

#include "gtest/gtest.h"

TEST(Simulators, ExecuteOneEvolutionaryStep)
{
	std::vector<Word> init = { Word(""), Word("a") };
	std::vector<std::shared_ptr<Rule> > ruleSet1, ruleSet2;
	ruleSet1.push_back(std::make_shared<RightInsertionRule>(RightInsertionRule("c")));
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	Processor p1(init, ruleSet1, freeFilter, freeFilter);
	Processor p2(init, ruleSet2, freeFilter, freeFilter);
	std::vector<Processor*> processors = { &p1, &p2 };
	std::vector<Network::Edge> edges = { Network::Edge(&p1,&p2) };
	Network network(processors, edges);
	Simulator simulator(network);
	simulator.executeStep();

	Multiset<Word> expected1, expected2;
	expected1.add(Word("c"));
	expected1.add(Word("ac"));
	expected2.add(Word(""));
	expected2.add(Word("a"));
	ASSERT_EQ(p1.exportConfiguration().wordSet, expected1);
	ASSERT_EQ(p2.exportConfiguration().wordSet, expected2);
}