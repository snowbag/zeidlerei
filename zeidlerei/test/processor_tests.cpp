#include "stdafx.h"
#include <iostream>
#include <memory>

#include "Word.h"
#include "Rule.h"
#include "FreeFilter.h"
#include "Processor.h"

#include "gtest/gtest.h"

TEST(Processors, Initialize) {
	auto init = std::vector<Word>{ Word("") };
	auto ruleSet = std::vector <std::shared_ptr<Rule> >();
	auto freeFilter = std::make_shared<FreeFilter>(FreeFilter());
	Processor p(init, ruleSet, freeFilter, freeFilter);
}