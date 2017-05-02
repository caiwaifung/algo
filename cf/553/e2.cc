#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// {{{
// clang-format off
#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for (int i = int(a); i <= int(b); ++i)
#define irep(i, a, b) for (int i = int(a); i >= int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define popcount __builtin_popcount
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<double> VD;
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

typedef complex<double> Complex;
void fft(vector<Complex>* ptr_a, bool is_inv = false) {
    auto& a = *ptr_a;
    int n = sz(a);
    static vector<Complex> b;
    if(sz(b) < n) b.resize(n);

    double arg = acos(-1.0);
    for(int t = n / 2; t >= 1; t /= 2) {
        Complex w(cos(arg), is_inv ? sin(arg) : -sin(arg));
        Complex p(1.0, 0.0);
        for(int j = 0; j < n / 2; j += t, p *= w) {
            for(int i = 0; i < t; ++i) {
                Complex u = a[i + j * 2];
                Complex v = p * a[i + t + j * 2];
                b[i + j] = u + v;
                b[i + j + n / 2] = u - v;
            }
        }
        copy(b.begin(), b.begin() + n, a.begin());
        arg /= 2;
    }
    if(is_inv) {
        repn(i, n) a[i] /= n;
    }
}

class Convolution {
public:
    Convolution(const vector<double>& a) : n(sz(a)), data(all(a)) {
        assert((n & (n - 1)) == 0);
        if(n > S) fft(&data);
    }
    template <class Iter>
    void convolute_with(Iter b_begin, Iter b_end, double* out) {
        int len = int(b_end - b_begin);
        if(n > S) {
            vector<Complex> tmp(b_begin, b_end);
            tmp.resize(n);
            fft(&tmp);
            repn(i, n) tmp[i] *= data[i];
            fft(&tmp, true);
            repn(i, n) out[i] += real(tmp[i]);
        } else {
            repn(i, n) repn(j, min(len, n - i)) {
                out[i + j] += real(data[i]) * b_begin[j];
            }
        }
    }

private:
    static constexpr int S = 64;
    const int n;
    vector<Complex> data;
};

class OnlineConvolution {
public:
    OnlineConvolution(const vector<double>& a) : n(sz(a)), prep(n), r(1) {
        assert((n & (n - 1)) == 0);
        for(int i = 0, j = 1; i < n; i = j, j <<= 1) {
            vector<double> tmp((j - i) * 2);
            copy(a.begin() + i, a.begin() + j, tmp.begin());
            prep[i] = unique_ptr<Convolution>(new Convolution(tmp));
        }
    }

    double add(double bi) {
        b.pb(bi);
        for(int i = 0, j = 1; i < n; i = j, j <<= 1) {
            const int len = j - i;
            const int jm = (j - 1) >> 1;
            if(((sz(b) - 1) & jm) == jm) {
                ensure_r_len(j + sz(b));
                prep[i]->convolute_with(b.end() - len, b.end(),
                                        &r[i + sz(b) - len]);
            }
        }
        return r[sz(b) - 1];
    }

private:
    void ensure_r_len(int required_len) {
        int len = max(1, sz(r));
        while(len < required_len) len *= 2;
        r.resize(len);
    }

    const int n;
    vector<unique_ptr<Convolution>> prep;
    vector<double> b, r;
};

int main() {
    int n, m, t, fine;
    scanf("%d%d%d%d", &n, &m, &t, &fine);
    int len = 1;
    while(t > len) len *= 2;

    VI a(m), b(m), c(m);
    vector<VD> p(m), s(m);
    vector<VD> g(n, VD(n, 1e50));
    repn(i, m) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        --a[i], --b[i];
        p[i].resize(len);
        repn(j, t) {
            scanf("%lf", &p[i][j]);
            p[i][j] /= 100000;
        }
        s[i].resize(len + 1);
        irepn(j, len) s[i][j] = s[i][j + 1] + p[i][j];
        setmin(g[a[i]][b[i]], (double)c[i]);
    }
    repn(i, n) g[i][i] = 0;
    repn(k, n) repn(i, n) repn(j, n) setmin(g[i][j], g[i][k] + g[k][j]);

    vector<OnlineConvolution*> oc(m);
    repn(i, m) oc[i] = new OnlineConvolution(p[i]);
    vector<VD> f(n, VD(t + 1));
    repn(x, n) rep(cur, 0, t) f[x][cur] = (x == n - 1 ? 0 : fine + g[x][n - 1]);
    rep(cur, 1, t) {
        repn(i, m) {
            double v = oc[i]->add(f[b[i]][cur - 1]);
            v += s[i][cur] * (g[b[i]][n - 1] + fine);
            setmin(f[a[i]][cur], v + c[i]);
        }
    }
    printf("%.9lf\n", f[0][t]);
    return 0;
}
