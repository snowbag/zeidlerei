#include "stdafx.h"  
#include <iostream>
#include <vector>

#include "FreeFilter.h"

#include "gtest/gtest.h"

TEST(Filters, Free) {
	std::vector<Word> words = { Word(""), Word("abcd"), Word("12345"), Word("(())()") };
	FreeFilter f;
	for (auto w : words) {
		ASSERT_TRUE(f.apply(w));
	}
}