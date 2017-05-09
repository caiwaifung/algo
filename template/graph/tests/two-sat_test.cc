#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../two-sat.h"

using namespace testing;

TEST(TwoSat, HasSolution) {
    TwoSat sat(4);
    sat.add_conflict({0, 0}, {1, 0});
    sat.add_conflict({0, 1}, {1, 1});
    sat.add_conflict({2, 0}, {3, 0});
    sat.add_conflict({2, 1}, {3, 1});
    sat.add_conflict({0, 1}, {2, 0});
    sat.add_conflict({1, 0}, {3, 1});

    auto r = sat.solve();
    EXPECT_THAT(r, SizeIs(4));
    repn(i, 4) EXPECT_THAT(r[i], AnyOf(Eq(0), Eq(1)));
    EXPECT_FALSE(r[0] == 0 && r[1] == 0);
    EXPECT_FALSE(r[0] == 1 && r[1] == 1);
    EXPECT_FALSE(r[2] == 0 && r[3] == 0);
    EXPECT_FALSE(r[2] == 1 && r[3] == 1);
    EXPECT_FALSE(r[0] == 1 && r[2] == 0);
    EXPECT_FALSE(r[1] == 0 && r[3] == 1);
}

TEST(TwoSat, NoSolution) {
    TwoSat sat(3);
    sat.add_conflict({0, 0}, {1, 1});
    sat.add_conflict({0, 1}, {1, 1});
    sat.add_conflict({1, 0}, {2, 1});
    sat.add_conflict({1, 0}, {2, 0});
    sat.add_conflict({2, 0}, {0, 1});
    EXPECT_THAT(sat.solve(), IsEmpty());
}

TEST(TwoSat, SingleVar) {
    TwoSat sat(1);
    sat.add_conflict({0, 0}, {0, 1});
    auto r = sat.solve();
    EXPECT_THAT(r, SizeIs(1));
    EXPECT_THAT(r[0], AnyOf(Eq(0), Eq(1)));
}

TEST(TwoSat, ConflictWithItself) {
    TwoSat sat(1);
    sat.add_conflict({0, 0}, {0, 0});
    EXPECT_THAT(sat.solve(), ElementsAre(1));
}

TEST(TwoSat, BothOptionsAreBad) {
    TwoSat sat(1);
    sat.add_conflict({0, 0}, {0, 0});
    sat.add_conflict({0, 1}, {0, 1});
    EXPECT_THAT(sat.solve(), IsEmpty());
}
