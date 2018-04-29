#include "../base/header.h"

struct ComplexField {
    typedef complex<double> value_t;
    static value_t root_of_unity(int n, bool is_inv = false) {
        static constexpr double PI = 3.14159265358979323846264;
        const double ang = PI * 2.0 / n;
        return value_t(cos(ang), is_inv ? sin(ang) : -sin(ang));
    }
    static value_t add(const value_t& a, const value_t& b) { return a + b; }
    static value_t sub(const value_t& a, const value_t& b) { return a - b; }
    static value_t mul(const value_t& a, const value_t& b) { return a * b; }
    static value_t div(const value_t& a, const value_t& b) { return a / b; }
};

struct IntModField {
    static constexpr int MOD = 998244353;
    typedef int value_t;
    static value_t root_of_unity(int n, bool is_inv = false) {
        int root = int(powmod(G, GN / n, MOD));
        return is_inv ? inv(root) : root;
    }
    static int add(int a, int b) { return a += b, a < MOD ? a : a - MOD; }
    static int sub(int a, int b) { return a -= b, a >= 0 ? a : a + MOD; }
    static int mul(int a, int b) { return int(a * LL(b) % MOD); }
    static int div(int a, int b) { return mul(a, inv(b)); }

  private:
    static constexpr int GN = MOD - 1;
    static constexpr int G = 3;
    static int inv(int a) { return int(powmod(a, MOD - 2, MOD)); }
};

template <class Field, class RandomIt>
void fft(RandomIt a, RandomIt a_end, bool is_inv = false) {
    typedef typename Field::value_t value_t;
    const int n = int(a_end - a);
    assert((n & (n - 1)) == 0);
    static vector<value_t> b;
    if (len(b) < n) b.resize(n);

    for (int t = n / 2; t >= 1; t /= 2) {
        value_t w = Field::root_of_unity(n / t, is_inv);
        value_t p = 1;
        for (int j = 0; j < n / 2; j += t, p = Field::mul(p, w)) {
            repn(i, t) {
                value_t u = a[i + j * 2];
                value_t v = Field::mul(p, a[i + t + j * 2]);
                b[i + j] = Field::add(u, v);
                b[i + j + n / 2] = Field::sub(u, v);
            }
        }
        copy(b.begin(), b.begin() + n, a);
    }
    if (is_inv) {
        repn(i, n) a[i] = Field::div(a[i], n);
    }
}
