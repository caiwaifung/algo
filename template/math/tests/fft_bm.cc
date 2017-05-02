#include <benchmark/benchmark.h>
#include <random>
#include "../../base/header.h"

#include "../fft.h"
#include "../field-complex.h"
#include "../field-intmod.h"

static void BM_FFTComplex(benchmark::State& state) {
    vector<complex<double>> a(state.range(0));
    std::uniform_real_distribution<double> distr(-100, 100);
    std::default_random_engine gen;
    for(auto& c : a) c = {distr(gen), distr(gen)};

    while(state.KeepRunning()) {
        fft<ComplexField>(all(a));
    }
}
BENCHMARK(BM_FFTComplex)
    ->Unit(benchmark::kMicrosecond)
    ->Arg(1 << 14)
    ->Arg(1 << 16)
    ->Arg(1 << 18)
    ->Arg(1 << 20);

static void BM_FFTIntMod(benchmark::State& state) {
    vector<int> a(state.range(0));
    std::uniform_real_distribution<int> distr(-(1 << 30), 1 << 30);
    std::default_random_engine gen;
    for(int& x : a) x = distr(gen);

    while(state.KeepRunning()) {
        fft<IntModField>(all(a));
    }
}
BENCHMARK(BM_FFTIntMod)
    ->Unit(benchmark::kMicrosecond)
    ->Arg(1 << 14)
    ->Arg(1 << 16)
    ->Arg(1 << 18)
    ->Arg(1 << 20);

static void BM_FFTComplex_Convolute(benchmark::State& state) {
    vector<double> a(state.range(0)), b(state.range(0)), c(state.range(0));
    std::uniform_real_distribution<double> distr(-100, 100);
    std::default_random_engine gen;
    for(double& c : a) c = distr(gen);
    for(double& c : b) c = distr(gen);

    if(state.range(1) == 0) {
        vector<complex<double>> ca(all(a)), cb(all(b));
        while(state.KeepRunning()) {
            fft<ComplexField>(all(ca));
            fft<ComplexField>(all(cb));
            repn(i, sz(a)) a[i] *= b[i];
            fft<ComplexField>(all(ca), true);
            repn(i, sz(a)) c[i] = real(ca[i]);
        }
    } else {
        while(state.KeepRunning()) {
            repn(i, sz(a)) repn(j, sz(a) - i) c[i + j] += a[i] * b[j];
        }
    }
    benchmark::DoNotOptimize(c);
}
BENCHMARK(BM_FFTComplex_Convolute)
    ->ArgPair(32, 0)
    ->ArgPair(32, 1)
    ->ArgPair(64, 0)
    ->ArgPair(64, 1)
    ->ArgPair(128, 0)
    ->ArgPair(128, 1)
    ->ArgPair(256, 0)
    ->ArgPair(256, 1)
    ->ArgPair(512, 0)
    ->ArgPair(512, 1);

BENCHMARK_MAIN();
