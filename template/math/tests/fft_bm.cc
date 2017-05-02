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

BENCHMARK_MAIN();
