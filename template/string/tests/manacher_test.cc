#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../manacher.h"

using namespace testing;

TEST(Manacher, Simple) {
    EXPECT_THAT(manacher("abacabad"), ElementsAre(1, 2, 1, 4, 1, 2, 1, 1));
}
