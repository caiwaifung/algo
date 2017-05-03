#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../mu.h"

using namespace testing;

int mu(int n) {
    int r = 1;
    for(int x = 2; x <= n; ++x) {
        int c = 0;
        while(n % x == 0) {
            ++c, n /= x;
        }
        if(c == 1) r = -r;
        if(c > 1) return 0;
    }
    return r;
}

TEST(Mu, First10) {
    EXPECT_THAT(compute_mu(10),
                ElementsAreArray({0, 1, -1, -1, 0, -1, 1, -1, 0, 0, 1}));
}

TEST(Mu, First2000) {
    auto r = compute_mu(2000);
    EXPECT_THAT(r, SizeIs(2001));
    rep(i, 1, 2000) EXPECT_EQ(mu(i), r[i]);
}

TEST(Mu, At200000) {
    auto r = compute_mu(200000);
    EXPECT_THAT(r, SizeIs(200001));
    repn(i, 20) EXPECT_EQ(mu(200000 - i), r[200000 - i]);
}
