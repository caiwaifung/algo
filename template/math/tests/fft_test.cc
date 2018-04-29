#include "../../base/header.h"
#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#include "../fft.h"

double Real(complex<double> x) { return x.real(); }
double Imag(complex<double> x) { return x.imag(); }

#define IS_COMPLEX(r, i)                                                       \
    testing::AllOf(testing::ResultOf(Real, testing::DoubleNear(r, 1e-5)),      \
                   testing::ResultOf(Imag, testing::DoubleNear(i, 1e-5)))
#define IS_REAL(r) IS_COMPLEX(r, 0)

TEST(FFTComplex, Convolution_4) {
    vector<complex<double>> a = {1, 1, 0, 0}, b = {2, 3, 0, 0};
    fft<ComplexField>(all(a)), fft<ComplexField>(all(b));
    repn(i, len(a)) a[i] *= b[i];
    fft<ComplexField>(all(a), true);
    EXPECT_THAT(a, testing::ElementsAre(IS_REAL(2), IS_REAL(5), IS_REAL(3),
                                        IS_REAL(0)));
}

TEST(FFTComplex, Convolution_8) {
    vector<complex<double>> a = {1, 2, 3, 4, 0, 0, 0, 0};
    vector<complex<double>> b = {5, 4, 3, 2, 1, 0, 0, 0};
    fft<ComplexField>(all(a)), fft<ComplexField>(all(b));
    repn(i, len(a)) a[i] *= b[i];
    fft<ComplexField>(all(a), true);
    EXPECT_THAT(a, testing::ElementsAre(IS_REAL(5), IS_REAL(14), IS_REAL(26),
                                        IS_REAL(40), IS_REAL(30), IS_REAL(20),
                                        IS_REAL(11), IS_REAL(4)));
}

TEST(FFTComplex, LengthMustBePowerOfTwo) {
    vector<complex<double>> a = {1, 2, 3};
    EXPECT_DEATH(fft<ComplexField>(all(a)), "");
}

TEST(FFTInt, Convolution_4) {
    VI a = {1, 1, 0, 0}, b = {2, 3, 0, 0};
    fft<IntModField>(all(a)), fft<IntModField>(all(b));
    repn(i, len(a)) a[i] = LL(a[i]) * b[i] % IntModField::MOD;
    fft<IntModField>(all(a), true);
    EXPECT_THAT(a, testing::ElementsAre(2, 5, 3, 0));
}

TEST(FFTInt, Convolution_8) {
    VI a = {1, 2, 3, 4, 0, 0, 0, 0};
    VI b = {5, 4, 3, 2, 1, 0, 0, 0};
    fft<IntModField>(all(a)), fft<IntModField>(all(b));
    repn(i, len(a)) a[i] = LL(a[i]) * b[i] % IntModField::MOD;
    fft<IntModField>(all(a), true);
    EXPECT_THAT(a, testing::ElementsAre(5, 14, 26, 40, 30, 20, 11, 4));
}
