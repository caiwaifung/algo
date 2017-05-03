#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../phi.h"

using namespace testing;

int phi(int n) {
    int r = 1;
    rep(i, 2, n - 1) if(gcd(n, i) == 1)++ r;
    return r;
}

TEST(Phi, First10) {
    EXPECT_THAT(compute_phi(10),
                ElementsAreArray({0, 1, 1, 2, 2, 4, 2, 6, 4, 6, 4}));
}

TEST(Phi, First2000) {
    auto r = compute_phi(2000);
    EXPECT_THAT(r, SizeIs(2001));
    rep(i, 1, 2000) EXPECT_EQ(phi(i), r[i]);
}

TEST(Phi, At200000) {
    auto r = compute_phi(200000);
    EXPECT_THAT(r, SizeIs(200001));
    repn(i, 20) EXPECT_EQ(phi(200000 - i), r[200000 - i]);
}
