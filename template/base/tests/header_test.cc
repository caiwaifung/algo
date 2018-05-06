#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../header.h"

TEST(StdExtensions, Sorted) {
    EXPECT_EQ(sorted(VI({3, 1, 6, 5, 4})), VI({1, 3, 4, 5, 6}));
    EXPECT_EQ(sorted(VS({"ab", "aac", "aa"})), VS({"aa", "aac", "ab"}));
}

TEST(StdExtensions, Reversed) {
    EXPECT_EQ(reversed(VI({3, 1, 6, 5, 4})), VI({4, 5, 6, 1, 3}));
    EXPECT_EQ(reversed(VS({"ab", "xy", "aa"})), VS({"aa", "xy", "ab"}));
}
