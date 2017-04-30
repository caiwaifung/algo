#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../ext-gcd.h"

TEST(Inv, Definition) {
    EXPECT_TRUE(inv(1, 12) * 1 % 12 == 1);
    EXPECT_TRUE(inv(5, 12) * 5 % 12 == 1);
    EXPECT_TRUE(inv(7, 12) * 7 % 12 == 1);
    EXPECT_TRUE(inv(11, 12) * 11 % 12 == 1);
}
