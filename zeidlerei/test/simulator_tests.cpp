#include "stdafx.h"  
#include <iostream>

#include "Simulator.h"
#include "FreeFilter.h"
#include "LengthFilter.h"
#include "RegexFilter.h"
#include "RightInsertionRule.h"
#include "LeftInsertionRule.h"
#include "LeftDeletionRule.h"
#include "MaximumStepsHaltingCondition.h"
#include "SameConfigurationHaltingCondition.h"
#include "NonEmptyNodeHaltingCondition.h"

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

TEST(Simulators, ExecuteOneCommunicationStep)
{
	std::vector<Word> init1 = { Word(""), Word("a") }, init2 = { Word("b"), Word("ac") };
	std::vector<std::shared_ptr<Rule> > ruleSet1, ruleSet2;
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	Processor p1(init1, ruleSet1, freeFilter, freeFilter);
	Processor p2(init2, ruleSet2, freeFilter, freeFilter);
	std::vector<Processor*> processors = { &p1, &p2 };
	std::vector<Network::Edge> edges = { Network::Edge(&p1,&p2) };
	Network network(processors, edges);
	Simulator simulator(network, Simulator::StepType::evolution);
	simulator.executeStep();

	Multiset<Word> expected1, expected2;
	expected1.add(Word("b"));
	expected1.add(Word("ac"));
	expected2.add(Word(""));
	expected2.add(Word("a"));
	ASSERT_EQ(p1.exportConfiguration().wordSet, expected1);
	ASSERT_EQ(p2.exportConfiguration().wordSet, expected2);
}

TEST(Simulators, ExecuteLeftRightInsertionSimulation)
{
	std::vector<Word> init1 = { Word("a") }, init2 = { Word("b") };
	std::vector<std::shared_ptr<Rule> > ruleSet1 = { std::make_shared<LeftInsertionRule>(LeftInsertionRule("c")) };
	std::vector<std::shared_ptr<Rule> > ruleSet2 = { std::make_shared<RightInsertionRule>(RightInsertionRule("d")) };
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	Processor p1(init1, ruleSet1, freeFilter, freeFilter);
	Processor p2(init2, ruleSet2, freeFilter, freeFilter);
	std::vector<Processor*> processors = { &p1, &p2 };
	std::vector<Network::Edge> edges = { Network::Edge(&p1,&p2) };
	Network network(processors, edges);
	Simulator simulator(network);

	MaximumStepsHaltingCondition haltingCondition(5);
	simulator.executeSimulation(haltingCondition);

	Multiset<Word> expected1, expected2;
	expected1.add(Word("ccad"));
	expected2.add(Word("cbdd"));

	ASSERT_EQ(p1.exportConfiguration().wordSet, expected1);
	ASSERT_EQ(p2.exportConfiguration().wordSet, expected2);
}

TEST(Simulators, HaltWithSameConsecutiveSteps)
{
	std::vector<Word> init1 = { Word("b") }, init2 = { Word("ab"), Word("aaaaaa") };
	std::vector<std::shared_ptr<Rule> > ruleSet1 = { std::make_shared<LeftInsertionRule>(LeftInsertionRule("a")) };
	std::vector<std::shared_ptr<Rule> > ruleSet2 = { std::make_shared<LeftDeletionRule>(LeftDeletionRule("a")) };
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter()),
		regexFilter = std::make_shared<RegexFilter>(RegexFilter("b"));
	Processor p1(init1, ruleSet1, freeFilter, freeFilter);
	Processor p2(init2, ruleSet2, freeFilter, regexFilter);
	std::vector<Processor*> processors = { &p1, &p2 };
	std::vector<Network::Edge> edges = { Network::Edge(&p1,&p2) };
	Network network(processors, edges);
	Simulator simulator(network);

	SameConfigurationHaltingCondition haltingCondition(network);
	simulator.executeSimulation(haltingCondition);

	Multiset<Word> expected1, expected2;
	expected1.add(Word("ab"));
	expected2.add(Word("b"));
	expected2.add(Word(""));

	ASSERT_EQ(p1.exportConfiguration().wordSet, expected1);
	ASSERT_EQ(p2.exportConfiguration().wordSet, expected2);
}

TEST(Simulators, HaltWithOutputNode)
{
	std::vector<Word> init1 = { Word("ab"), Word("a") }, init2;
	std::vector<std::shared_ptr<Rule> > ruleSet1 = { std::make_shared<LeftInsertionRule>(LeftInsertionRule("c")) };
	std::vector<std::shared_ptr<Rule> > ruleSet2 = { std::make_shared<RightInsertionRule>(RightInsertionRule("d")) };
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter()),
		lengthFilter = std::make_shared<LengthFilter>(LengthFilter(LengthFilter::ComparisonType::greaterThan,4));
	Processor p1(init1, ruleSet1, freeFilter, lengthFilter);
	Processor p2(init2, ruleSet2, lengthFilter, freeFilter);
	std::vector<Processor*> processors = { &p1, &p2 };
	std::vector<Network::Edge> edges = { Network::Edge(&p1,&p2) };
	Network network(processors, edges);
	Simulator simulator(network);

	NonEmptyNodeHaltingCondition haltingCondition(&p2);
	simulator.executeSimulation(haltingCondition);

	Multiset<Word> expected1, expected2;
	expected1.add(Word("ccca"));
	expected2.add(Word("cccab"));

	ASSERT_EQ(p1.exportConfiguration().wordSet, expected1);
	ASSERT_EQ(p2.exportConfiguration().wordSet, expected2);
}