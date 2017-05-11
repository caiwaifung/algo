#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../min-rep.h"

using namespace testing;

TEST(MinRep, SingleChar) {
    EXPECT_EQ(0, min_representation("a"));
}

TEST(MinRep, DoubleChar) {
    EXPECT_EQ(0, min_representation("xy"));
    EXPECT_EQ(1, min_representation("ub"));
}

TEST(MinRep, MultipleChar) {
    EXPECT_EQ(3, min_representation("abcaabc"));
}

TEST(MinRep, Same) {
    EXPECT_EQ(0, min_representation("aaaaa"));
    EXPECT_EQ(0, min_representation("abcabc"));
    EXPECT_EQ(1, min_representation("cabcab"));
    EXPECT_EQ(2, min_representation("bcabca"));
}
