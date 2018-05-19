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
#ifndef H_ALGO_HEADER
#define H_ALGO_HEADER

#define all(a) (a).begin(), (a).end()
template <class T> int len(const T& a) { return static_cast<int>(a.size()); }
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
typedef vector<bool> VB;
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
typedef vector<PDD> VPD;
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef vector<VD> VVD;
typedef vector<VB> VVB;
typedef vector<VS> VVS;
typedef vector<VPI> VVPI;
typedef vector<VPL> VVPL;

template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, len(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
int read_int() { int x; scanf("%d", &x); return x; }
LL read_ll() { LL x; scanf("%lld", &x); return x; }
string read_string() { string s; cin >> s; return s; }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
#define IN read_int()

template <class T> T sorted(T x) { sort(x.begin(), x.end()); return x; }
template <class T> T reversed(T x) { reverse(x.begin(), x.end()); return x; }

template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }

#endif
// clang-format on
// }}}

VS solve(VI a) {
    const int n = len(a);
    if (a[0] == 0 || a[n - 1] == 0) {
        return VS();
    }
    VI x(n, -1), y(n, -1);
    int cur = 0, dis = 0;
    repn(i, n) if (a[i] > 0) {
        x[i] = cur, y[i] = cur + a[i] - 1;
        cur += a[i];
        setmax(dis, abs(x[i] - i));
        setmax(dis, abs(y[i] - i));
    }
    VS r(dis + 1, string(n, '.'));
    repn(i, n) if (a[i] > 0) {
        int u = x[i], v = y[i];
        for (int j = 0; u != i || v != i; ++j) {
            assert(j + 1 < len(r));
            if (u < i) {
                r[j][u] = '\\';
                ++u, setmax(v, u);
            }
            if (v > i) {
                r[j][v] = '/';
                --v, setmin(u, v);
            }
        }
    }
    return r;
}

void check() {
    const int n = 55;
    while (1) {
        VI c(n);
        c[0] = c[n - 1] = 1;
        repn(i, n - 2) c[rand() % n]++;
        VS ans = solve(c);
        assert(len(ans) > 0);
        cout << c << endl;
        repn(i, len(ans)) {
            assert(len(ans[i]) == n);
            assert(ans[i][0] == '.' && ans[i][n - 1] == '.');
        }
        repn(i, n) assert(ans.back()[i] == '.');
        repn(i, n) {
            int x = 0, y = i;
            while (x < len(ans)) {
                if (ans[x][y] == '/')
                    --y;
                else if (ans[x][y] == '\\')
                    ++y;
                ++x;
            }
            --c[y];
        }
        repn(i, n) assert(c[i] == 0);
    }
}

int main() {
    // check();
    int num;
    scanf("%d", &num);
    rep(i, 1, num) {
        printf("Case #%d: ", i);
        VS ans = solve(read_vi());
        if (ans.empty()) {
            printf("IMPOSSIBLE\n");
        } else {
            printf("%d\n", len(ans));
            for (const string& s : ans) printf("%s\n", s.c_str());
        }
    }
    return 0;
}
