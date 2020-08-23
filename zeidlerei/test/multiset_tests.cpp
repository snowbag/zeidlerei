//#include "stdafx.h"
#include <iostream>

#include "Multiset.h"

#include "gtest/gtest.h"

TEST(Multisets, AddOneElement) {
	Multiset<std::string> ms;
	ms.add("abc");
	ASSERT_EQ(ms["abc"], 1);
	ASSERT_EQ(ms.size(), 1);
}

TEST(Multisets, ElementsTwice) {
	Multiset<std::string> ms;
	ms.add("abc");
	ms.add("abc");
	ms.add("efg",2);
	ASSERT_EQ(ms["abc"], 2);
	ASSERT_EQ(ms["efg"], 2);
	ASSERT_EQ(ms.size(), 4);
}

TEST(Multisets, AddAndRemoveElement) {
	Multiset<std::string> ms;
	ASSERT_FALSE(ms.contains("abc"));
	ms.add("abc");
	ASSERT_TRUE(ms.contains("abc"));
	ms.remove("abc");
	ASSERT_FALSE(ms.contains("abc"));
	ASSERT_EQ(ms.size(), 0);
}

TEST(Multisets, CombineMultisets)
{
	Multiset<std::string> ms1, ms2;
	ms1.add("abc", 1);
	ms1.add("def", 3);
	ms2.add("abc", 4);
	ms2.add("g", 2);
	ms1.addAll(ms2);
	ASSERT_EQ(ms1["abc"], 5);
	ASSERT_EQ(ms1["def"], 3);
	ASSERT_EQ(ms1["g"], 2);
	ASSERT_EQ(ms2["abc"], 4);
	ASSERT_EQ(ms2["g"], 2);
	ASSERT_EQ(ms1.size(), 10);
	ASSERT_EQ(ms2.size(), 6);
}
