#include <gmock/gmock.h>
#include <gtest/gtest.h>

// clang-format off
#include "../../base/header.h"
#include "../ext-gcd.h"
#include "../chinese-remainder.h"
// clang-format on

using namespace testing;

TEST(ChineseRemainder, Simple) {
    LL x = chinese_remainder(5, 3, 6, 2);
    EXPECT_THAT(x, AllOf(Ge(0), Lt(30)));
    EXPECT_EQ(3, x % 5);
    EXPECT_EQ(2, x % 6);
}

TEST(ExtChineseRemainder, Simple) {
    LL x = ext_chinese_remainder(4, 2, 6, 4);
    EXPECT_THAT(x, AllOf(Ge(0), Lt(24)));
    EXPECT_EQ(2, x % 4);
    EXPECT_EQ(4, x % 6);
}

TEST(ExtChineseRemainder, NoSolution) {
    EXPECT_EQ(-1, ext_chinese_remainder(4, 3, 6, 4));
}