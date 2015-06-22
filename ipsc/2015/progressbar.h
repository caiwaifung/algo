#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include <chrono>
#include <ctime>
#include <cstdio>

static double _pb_speed, _pb_last;
static std::chrono::steady_clock::time_point _pb_t;
static void progress_start() {
    _pb_speed = -1;
    _pb_last = 0;
    _pb_t = std::chrono::steady_clock::now();
}

static void progress_update(double proportion) {

    auto t = std::chrono::steady_clock::now();
    auto duration =  std::chrono::duration_cast<std::chrono::duration<double>> (t - _pb_t);
    _pb_t = t;
    double last_speed = (proportion - _pb_last) / duration.count();
    _pb_last = proportion;

    if (_pb_speed < 0)
        _pb_speed = last_speed;
    else
        _pb_speed = _pb_speed * 0.7 + last_speed * 0.3;
    double eta = (1 - proportion) / _pb_speed;
    fprintf(stderr, "percentage: %.3lf%%.  ETA: %.3lfs\n", proportion * 100, eta);
}

#endif

