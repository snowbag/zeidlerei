#include "stdafx.h"
#include <iostream>
#include <memory>

#include "Word.h"
#include "Rule.h"
#include "FreeFilter.h"
#include "Processor.h"

#include "gtest/gtest.h"

TEST(Processors, Initialize) {
	std::vector<Word> init = { Word("") };
	std::vector<std::shared_ptr<Rule> > ruleSet;
	std::shared_ptr<Filter> freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	Processor p(init, ruleSet, freeFilter, freeFilter);
}