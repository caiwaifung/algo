#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../kmp.h"

using namespace testing;

TEST(KMP, Simple) {
    EXPECT_THAT(kmp("abcaabc", "abc"), ElementsAre(1, 2, 3, 1, 1, 2, 3));
}
