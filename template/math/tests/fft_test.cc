#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../fft.h"

#define IS_COMPLEX(r, i)                                               \
    testing::AllOf(                                                    \
        testing::ResultOf(real<double>, testing::DoubleNear(r, 1e-5)), \
        testing::ResultOf(imag<double>, testing::DoubleNear(i, 1e-5)))
#define IS_REAL(r) IS_COMPLEX(r, 0)

TEST(FFTComplex, Convolution_4) {
    vector<Complex> a = {1, 1, 0, 0}, b = {2, 3, 0, 0};
    fft(&a), fft(&b);
    repn(i, sz(a)) a[i] *= b[i];
    fft(&a, true);
    EXPECT_THAT(a, testing::ElementsAre(IS_REAL(2), IS_REAL(5), IS_REAL(3),
                                        IS_REAL(0)));
}

TEST(FFTComplex, Convolution_8) {
    vector<Complex> a = {1, 2, 3, 4, 0, 0, 0, 0};
    vector<Complex> b = {5, 4, 3, 2, 1, 0, 0, 0};
    fft(&a), fft(&b);
    repn(i, sz(a)) a[i] *= b[i];
    fft(&a, true);
    EXPECT_THAT(a, testing::ElementsAre(IS_REAL(5), IS_REAL(14), IS_REAL(26),
                                        IS_REAL(40), IS_REAL(30), IS_REAL(20),
                                        IS_REAL(11), IS_REAL(4)));
}
