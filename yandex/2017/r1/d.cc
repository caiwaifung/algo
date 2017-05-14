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

const int N = 500000;

VI go(VPI as) {
    VI f(N + 1, -(1 << 27));
    f[0] = 0;
    for(const auto& a : as) {
        irep(i, N, a.fi + a.se) { setmax(f[i], f[i - a.fi - a.se] + a.se); }
    }
    rep(i, 1, N) setmax(f[i], f[i - 1]);
    return f;
}

int main() {
    int n;
    VPI as, bs, cs;
    scanf("%d", &n);
    repn(i, n) {
        char s[9];
        int x, y;
        scanf("%s%d%d", s, &x, &y);
        if(s[0] == 'W') {
            as.pb(mp(x, y));
        } else if(s[0] == 'D') {
            bs.pb(mp(x, y));
        } else {
            cs.pb(mp(x, y));
        }
    }
    VI fa = go(as);
    VI fb = go(bs);
    VI fc = go(cs);

    int ans = 0;
    rep(i, 0, N) { setmax(ans, fa[i] + fb[i] + fc[i] - i); }
    printf("%d\n", ans);
    return 0;
}
