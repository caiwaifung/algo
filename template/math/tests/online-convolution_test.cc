#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>
#include "../../base/header.h"

#include "../fft.h"
#include "../field-complex.h"
#include "../field-intmod.h"

#include "../online-convolution.h"

using namespace testing;

TEST(OnlineConvolution, Complex) {
    const vector<double> a = {1, 2, 3, 4};
    OnlineConvolution<ComplexField> oc(all(a));
    EXPECT_THAT(real(oc.add(1)), DoubleNear(1, 1e-6));
    EXPECT_THAT(real(oc.add(2)), DoubleNear(4, 1e-6));
    EXPECT_THAT(real(oc.add(3)), DoubleNear(10, 1e-6));
    EXPECT_THAT(real(oc.add(5)), DoubleNear(21, 1e-6));
    EXPECT_THAT(real(oc.add(1)), DoubleNear(28, 1e-6));
}

TEST(OnlineConvolution, Int) {
    const VI a = {1, 2, 3, 4};
    OnlineConvolution<IntModField> oc(all(a));
    EXPECT_THAT(oc.add(1), Eq(1));
    EXPECT_THAT(oc.add(2), Eq(4));
    EXPECT_THAT(oc.add(3), Eq(10));
    EXPECT_THAT(oc.add(5), Eq(21));
    EXPECT_THAT(oc.add(1), Eq(28));
}

TEST(OnlineConvolution, BigInt) {
    const int x = 1 << 30;
    const VI a = {x, x, x, x};
    OnlineConvolution<IntModField> oc(all(a));
    EXPECT_THAT(oc.add(x), Eq(LL(x) * LL(x) % MOD));
    EXPECT_THAT(oc.add(x), Eq(LL(x) * LL(x) * 2 % MOD));
    EXPECT_THAT(oc.add(x), Eq(LL(x) * LL(x) * 3 % MOD));
    EXPECT_THAT(oc.add(x), Eq(LL(x) * LL(x) * 4 % MOD));
    EXPECT_THAT(oc.add(x), Eq(LL(x) * LL(x) * 4 % MOD));
}

TEST(OnlineConvolution, BigArray) {
    const int n = 1 << 13;
    VI a(n), b(n), c(n);
    repn(i, n) a[i] = i, b[i] = n - i % 100;
    repn(i, n) rep(j, 0, i) c[i] = int((c[i] + LL(a[j]) * b[i - j]) % MOD);

    OnlineConvolution<IntModField> oc(all(a));
    repn(i, n) EXPECT_THAT(oc.add(b[i]), Eq(c[i]));
}
