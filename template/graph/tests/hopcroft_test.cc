#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../hopcroft.h"

using namespace testing;

TEST(Hopcroft, LeftIsFullMatch) {
    EXPECT_THAT(max_match({{0, 2}, {1, 2}, {2}, {0, 1, 4}}),
                Pair(Eq(4), ElementsAre(0, 1, 2, 4)));
}

TEST(Hopcroft, LeftIsNotFullMatch) {
    EXPECT_THAT(max_match({{0, 2}, {1, 2}, {0, 1}, {0, 1}}), Pair(Eq(3), _));
}

TEST(Hopcroft, LeftHasIsolated) {
    EXPECT_THAT(max_match({{0, 2}, {1, 2}, {}, {2}, {}}),
                Pair(Eq(3), ElementsAre(0, 1, -1, 2, -1)));
}

TEST(Hopcroft, CompleteGraph) {
    VI ys(990);
    iota(all(ys), 0);
    EXPECT_THAT(max_match(vector<VI>(1010, ys)), Pair(Eq(990), _));
}
