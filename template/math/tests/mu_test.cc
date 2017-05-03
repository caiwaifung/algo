#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <random>

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

TEST(Mu, MobiusInversion) {
    // g(n) = sum_{d\n} f(d) <=>
    // f(n) = sum_{d\n} g(d) mu(n/d)
    const int N = 1000;
    VI f(N + 1), g(N + 1);
    std::uniform_real_distribution<int> distr(-1000, 1000);
    std::default_random_engine gen;
    rep(n, 1, N) f[n] = distr(gen);
    rep(n, 1, N) rep(d, 1, n) if(n % d == 0) g[n] += f[d];

    auto m = compute_mu(N);
    rep(n, 1, N) {
        int res = 0;
        rep(d, 1, n) if(n % d == 0) res += g[d] * m[n / d];
        EXPECT_EQ(res, f[n]);
    }
}
