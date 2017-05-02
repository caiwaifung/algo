#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../det-int.h"

TEST(Det, Small_2) { EXPECT_EQ(11, det({{6, 5}, {5, 6}}, 99)); }

TEST(Det, Small_3) { EXPECT_EQ(7, det({{1, 2, 3}, {4, 3, 3}, {7, 7, 7}}, 99)); }

TEST(Det, Mod) {
    EXPECT_EQ(
        470,
        det({{5, 5, 5, 5}, {9, 8, 9, 8}, {12, 89, 34, 34}, {54, 43, 32, 21}},
            1000));
}
