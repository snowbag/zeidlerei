//#include "stdafx.h"  
#include <iostream>
#include <vector>

#include "FreeFilter.h"
#include "LengthFilter.h"
#include "RegexFilter.h"
#include "PermitForbidFilter.h"

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

TEST(Filters, PermitForbid) {
	std::vector<Word> goodWords = { Word("caaaab"), Word("abc"), Word("12ab34c"), Word("c((???ab") };
	std::vector<Word> badWords = { Word("ab"), Word("c"), Word("abcd"), Word("abac") };
	PermitForbidFilter f({ "ab", "c" }, { "ba", "d" });
	for (auto w : goodWords) {
		ASSERT_TRUE(f.apply(w)) << w.getContent() << " returns false";
	}
	for (auto w : badWords) {
		ASSERT_FALSE(f.apply(w));
	}
}

TEST(Filters, PermitForbidInitializers) {
	std::vector<Word> goodWords = { Word("caaaab"), Word("abc"), Word("12ab34c"), Word("c((???ab") };
	std::vector<Word> others = { Word("ab"), Word("c"), Word("abcd"), Word("abac") };
	PermitForbidFilter f1("+ab+c-ba-d"), f2("+ab+c"), f3("-ba-d"), f4("+ab"), f5("-ba"), f6("+ab-ba"), f7("");

	for (auto w : goodWords) {
		EXPECT_TRUE(f1.apply(w)) << w.getContent() << " returns false";
		EXPECT_TRUE(f2.apply(w)) << w.getContent() << " returns false";
		EXPECT_TRUE(f3.apply(w)) << w.getContent() << " returns false";
		EXPECT_TRUE(f4.apply(w)) << w.getContent() << " returns false";
		EXPECT_TRUE(f5.apply(w)) << w.getContent() << " returns false";
		EXPECT_TRUE(f6.apply(w)) << w.getContent() << " returns false";
		EXPECT_TRUE(f7.apply(w)) << w.getContent() << " returns false";
	}

	int i = 0;
	//ab
	EXPECT_FALSE(f1.apply(others[i]));
	EXPECT_FALSE(f2.apply(others[i]));
	EXPECT_TRUE(f3.apply(others[i]));
	EXPECT_TRUE(f4.apply(others[i]));
	EXPECT_TRUE(f5.apply(others[i]));
	EXPECT_TRUE(f6.apply(others[i]));
	EXPECT_TRUE(f7.apply(others[i]));
	++i;
	//c
	EXPECT_FALSE(f1.apply(others[i]));
	EXPECT_FALSE(f2.apply(others[i]));
	EXPECT_TRUE(f3.apply(others[i]));
	EXPECT_FALSE(f4.apply(others[i]));
	EXPECT_TRUE(f5.apply(others[i]));
	EXPECT_FALSE(f6.apply(others[i]));
	EXPECT_TRUE(f7.apply(others[i]));
	++i;
	//abcd
	EXPECT_FALSE(f1.apply(others[i]));
	EXPECT_TRUE(f2.apply(others[i]));
	EXPECT_FALSE(f3.apply(others[i]));
	EXPECT_TRUE(f4.apply(others[i]));
	EXPECT_TRUE(f5.apply(others[i]));
	EXPECT_TRUE(f6.apply(others[i]));
	EXPECT_TRUE(f7.apply(others[i]));
	++i;
	//abac
	EXPECT_FALSE(f1.apply(others[i]));
	EXPECT_TRUE(f2.apply(others[i]));
	EXPECT_FALSE(f3.apply(others[i]));
	EXPECT_TRUE(f4.apply(others[i]));
	EXPECT_FALSE(f5.apply(others[i]));
	EXPECT_FALSE(f6.apply(others[i]));
	EXPECT_TRUE(f7.apply(others[i]));
	++i;
}