#include "stdafx.h"  
#include <iostream>
#include <vector>

#include "FreeFilter.h"
#include "LengthFilter.h"
#include "RegexFilter.h"

#include "gtest/gtest.h"

TEST(Filters, Free) {
	std::vector<Word> words = { Word(""), Word("abcd"), Word("12345"), Word("(())()") };
	FreeFilter f;
	for (auto w : words) {
		ASSERT_TRUE(f.apply(w));
	}
}

TEST(Filters, LengthGreaterThanThree) {
	std::vector<Word> goodWords = { Word("abcd"), Word("12345"), Word("(())()") };
	std::vector<Word> badWords = { Word(""), Word("abc"), Word("12"), Word("((") };
	LengthFilter f(LengthFilter::ComparisonType::greaterThan, 3);
	for (auto w : goodWords) {
		ASSERT_TRUE(f.apply(w));
	}
	for (auto w : badWords) {
		ASSERT_FALSE(f.apply(w));
	}
}

TEST(Filters, LengthEqualsFour) {
	std::vector<Word> goodWords = { Word("abcd"), Word("1234"), Word("(())") };
	std::vector<Word> badWords = { Word(""), Word("abc"), Word("1984o"), Word("((???") };
	LengthFilter f(LengthFilter::ComparisonType::equals, 4);
	for (auto w : goodWords) {
		ASSERT_TRUE(f.apply(w));
	}
	for (auto w : badWords) {
		ASSERT_FALSE(f.apply(w));
	}
}

TEST(Filters, PrefixAlphanumericSuffixAb) {
	std::vector<Word> goodWords = { Word(".ab"), Word("abbabab"), Word("1234test4321ab"), Word("((???ab") };
	std::vector<Word> badWords = { Word(""), Word("ab"), Word("ab1984o"), Word("sg ab") };
	RegexFilter f("(\\S+ab)");
	for (auto w : goodWords) {
		ASSERT_TRUE(f.apply(w));
	}
	for (auto w : badWords) {
		ASSERT_FALSE(f.apply(w));
	}
}