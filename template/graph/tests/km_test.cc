#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../km.h"

using namespace testing;

TEST(KM, Simple) {
    EXPECT_THAT(mincost_match<int>({{1, 2, 3}, {4, 6, 4}, {3, 9, 6}}),
                Pair(Eq(9), ElementsAre(1, 2, 0)));
}

TEST(KM, InferFromVector) {
    vector<vector<int>> a = {{1, 2}, {3, 4}};
    EXPECT_THAT(mincost_match(a), Pair(Eq(5), _));

    vector<vector<LL>> b = {{7, 8}, {8, 4}};
    EXPECT_THAT(mincost_match(b), Pair(Eq(11), _));

    vector<vector<double>> c = {{1.5, 0.5}, {1.25, 0.5}};
    EXPECT_THAT(mincost_match(c), Pair(DoubleEq(1.75), _));
}

TEST(KM, NegativeValue) {
    EXPECT_THAT(mincost_match<int>({{-100, -200}, {-300, -600}}),
                Pair(Eq(-700), ElementsAre(0, 1)));
    EXPECT_THAT(mincost_match<int>({{100, 200}, {300, 600}}),
                Pair(Eq(500), ElementsAre(1, 0)));
}

TEST(KM, Int64) {
    LL big = 1ll << 58;
    EXPECT_THAT(mincost_match<LL>({{big * 3, big * 1}, {big * 5, big * 2}}),
                Pair(Eq(big * 5), _));
    EXPECT_THAT(mincost_match<LL>({{-big * 3, big * 2}, {-big * 5, big * 1}}),
                Pair(Eq(-big * 3), _));
}
