#include "stdafx.h"  
#include <iostream>
#include <vector>
#include "FreeFilter.h"

#include "gtest/gtest.h"

TEST(Filters, Free) {
	auto words = std::vector<Word>{ Word(""), Word("abcd"), Word("12345"), Word("(())()") };
	Filter *f = new FreeFilter();
	for (auto w : words) {
		ASSERT_TRUE(f->apply(w));
	}
}