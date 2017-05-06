#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
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
int uniform(int minv, int maxv) {  // {{{
    static mt19937 gen{
        (unsigned)std::chrono::system_clock::now().time_since_epoch().count()};
    uniform_int_distribution<int> distr(minv, maxv);
    return distr(gen);
}

VI rand_perm(int n) {
    VI a(n);
    iota(all(a), 0);
    repn(i, n) swap(a[i], a[uniform(0, i)]);
    return a;
}
// }}}

void gen1(int n, int m, int k, string case_name) {
    ofstream f;
    f.open(string("in/") + case_name + ".in");
    f << n << " " << m << " " << k << endl;
    set<PII> used;
    repn(i, 2 * k) {
        while(1) {
            PII p = {uniform(0, n - 1), uniform(0, m - 1)};
            if(used.count(p) == 0) {
                used.insert(p);
                f << p.fi << " " << p.se << endl;
                break;
            }
        }
    }
    f.close();
}

void gen2(int n, int m, int k, int d, string case_name) {
    ofstream f;
    f.open(string("in/") + case_name + ".in");
    f << n << " " << m << " " << k << endl;
    set<PII> used;
    VPI ps, qs;
    repn(i, k) {
        PII p, q;
        do {
            p = {uniform(0, n - 1), uniform(0, m - 1)};
            int x1 = max(0, p.fi - d), x2 = min(n - 1, p.fi + d);
            int y1 = max(0, p.se - d), y2 = min(m - 1, p.se + d);
            q = {uniform(x1, x2), uniform(y1, y2)};
        } while(used.count(p) || used.count(q) || p == q);
        ps.pb(p), used.insert(p);
        qs.pb(q), used.insert(q);
    }
    for(const auto& p : ps) f << p.fi << " " << p.se << endl;
    for(const auto& p : qs) f << p.fi << " " << p.se << endl;
    f.close();
}

void gen3(int n, int m, int k, string case_name) {
    int s;
    while(1) {
        int l = (k + 7) / 4, r = min(n, m) / 2;
        if(l <= r) {
            s = uniform(l, r);
            break;
        }
        k = uniform(3, 16);
    }
    int x1, y1, x2, y2;
    while(1) {
        x1 = uniform(0, n - s), y1 = uniform(0, m - s);
        x2 = uniform(0, n - s), y2 = uniform(0, m - s);
        if(abs(x1 - x2) < s && abs(y1 - y2) < s) continue;
        break;
    }
    ofstream f;
    f.open(string("in/") + case_name + ".in");
    f << n << " " << m << " " << k << endl;
    set<PII> used;
    repn(i, k * 2) {
        PII p;
        do {
            p = {uniform(0, s - 1), uniform(0, s - 1)};
            if(i < k) {
                p.fi += x1, p.se += y1;
            } else {
                p.fi += x2, p.se += y2;
            }
        } while(used.count(p));
        used.insert(p);
        f << p.fi << " " << p.se << endl;
    }
    f.close();
}

int main() {
    rep(i, 0, 9) {
        gen1(uniform(3, 50), uniform(3, 50), uniform(3, 16), to_string(i));
    }
    rep(i, 10, 19) {
        gen2(uniform(3, 50), uniform(3, 50), uniform(3, 16), uniform(1, 4),
             to_string(i));
    }
    rep(i, 20, 24) {
        gen3(uniform(3, 50), uniform(3, 50), uniform(3, 16), to_string(i));
    }
    return 0;
}
