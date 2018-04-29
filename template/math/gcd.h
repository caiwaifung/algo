#include "../base/header.h"

// Finds x and y: a x + b y = gcd(a, b).  Returns gcd(a, b).
//
// Must: |a| + |b| > 0.
LL ext_gcd(LL a, LL b, LL *x, LL *y) {
    if (b == 0) {
        *x = 1, *y = 0;
        return a;
    }
    LL nx, ny;
    LL d = ext_gcd(b, a % b, &nx, &ny);
    *x = ny, *y = nx - (a / b) * ny;
    return d;
}

// Returns x: (a * x) % m = 1.
//
// Must: gcd(a, m) = 1.
// Guarantee: 0 <= x < m.
LL inv(LL a, LL m) {
    LL x, y;
    LL g = ext_gcd(a, m, &x, &y);
    assert(g == 1);
    if (x < 0) x += m;
    return x;
}

// Finds x that x % ni = ai, for i = {1,2}.
//
// Must: gcd(n1, n2) = 1.
// Guarantee: 0 <= x < n1*n2.
LL chinese_remainder(LL n1, LL a1, LL n2, LL a2) {
    LL m = n1 * n2;
    return (a1 * n2 * inv(n2, n1) + a2 * n1 * inv(n1, n2)) % m;
}

// Supports cases that gcd(n1, n2) > 1.
// Returns -1 if no solution.
// There is a solution iff a1 % g = a2 % g, where g = gcd(n1, n2).
//
// Guarantee: 0 <= x < lcm(n1, n2).
LL ext_chinese_remainder(LL n1, LL a1, LL n2, LL a2) {
    LL g = gcd(n1, n2);
    if (a1 % g != a2 % g) return -1;
    LL x = chinese_remainder(n1 / g, a1 / g, n2 / g, a2 / g);
    return x * g + a1 % g;
}
