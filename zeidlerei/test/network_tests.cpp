//#include "stdafx.h"
#include <iostream>
#include <memory>

#include "Word.h"
#include "FreeFilter.h"
#include "Processor.h"
#include "Network.h"
#include "RightInsertionRule.h"

#include "Simulator.h"

#include "gtest/gtest.h"

TEST(Networks, TwoNodesConnected)
{
	std::vector<Word> init = { Word(""), Word("a") };
	std::vector<std::shared_ptr<Rule> > ruleSet;
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	auto p1 = std::make_shared<Processor>(Processor(init, ruleSet, freeFilter, freeFilter));
	auto p2 = std::make_shared<Processor>(Processor(init, ruleSet, freeFilter, freeFilter));
	std::vector<std::shared_ptr<Processor> > processors = { p1, p2 };
	std::vector<Network::Edge> edges = { Network::Edge(p1,p2) };
	Network network(processors, edges);
}

TEST(Networks, ThreeNodesOneConnection)
{
	std::vector<Word> init = { Word(""), Word("a") };
	std::vector<std::shared_ptr<Rule> > ruleSet1, ruleSet2, ruleSet3;
	ruleSet1.push_back(std::make_shared<RightInsertionRule>(RightInsertionRule("b")));
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	auto p1 = std::make_shared<Processor>(Processor(init, ruleSet1, freeFilter, freeFilter));
	auto p2 = std::make_shared<Processor>(Processor(init, ruleSet2, freeFilter, freeFilter));
	auto p3 = std::make_shared<Processor>(Processor(init, ruleSet3, freeFilter, freeFilter));
	std::vector<std::shared_ptr<Processor> > processors = { p1, p2, p3 };
	std::vector<Network::Edge> edges = { Network::Edge(p1,p2) };
	Network network(processors, edges);
	ASSERT_TRUE(network.hasEdge(Network::Edge(p1, p2)));
	ASSERT_TRUE(network.hasEdge(Network::Edge(p2, p1)));
	ASSERT_FALSE(network.hasEdge(Network::Edge(p2, p3)));
	ASSERT_FALSE(network.hasEdge(Network::Edge(p3, p2)));
	ASSERT_FALSE(network.hasEdge(Network::Edge(p1, p3)));
	ASSERT_FALSE(network.hasEdge(Network::Edge(p3, p1)));
}