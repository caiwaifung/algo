#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../fft-int.h"

TEST(FFTInt, Convolution_4) {
    VI a = {1, 1, 0, 0}, b = {2, 3, 0, 0};
    fft(&a), fft(&b);
    repn(i, sz(a)) a[i] = LL(a[i]) * b[i] % MOD;
    fft(&a, true);
    EXPECT_THAT(a, testing::ElementsAre(2, 5, 3, 0));
}

TEST(FFTInt, Convolution_8) {
    VI a = {1, 2, 3, 4, 0, 0, 0, 0};
    VI b = {5, 4, 3, 2, 1, 0, 0, 0};
    fft(&a), fft(&b);
    repn(i, sz(a)) a[i] = LL(a[i]) * b[i] % MOD;
    fft(&a, true);
    EXPECT_THAT(a, testing::ElementsAre(5, 14, 26, 40, 30, 20, 11, 4));
}
