#include <algorithm>
#include <cassert>
#include <cmath>
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
// clang-format on
// }}}

void solve(int cs) {
    const LL inf = 1ll << 50;
    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    vector<VL> g(n, VL(n, inf));
    repn(i, n) g[i][i] = 0;
    repn(i, m) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a, --b;
        setmin(g[a][b], (LL)c), setmin(g[b][a], (LL)c);
    }
    repn(k, n) repn(i, n) repn(j, n) { setmin(g[i][j], g[i][k] + g[k][j]); }
    VI start(p), end(p);
    repn(i, p) {
        scanf("%d%d", &start[i], &end[i]);
        --start[i], --end[i];
    }

    vector<VL> f(p, VL(2, inf));
    f[0][0] = g[0][start[0]];
    LL ans = inf;
    repn(i, p) {
        if(i + 1 < p) {
            setmin(f[i + 1][1], f[i][0] + g[start[i]][start[i + 1]]);
            setmin(f[i + 1][0],
                   f[i][0] + g[start[i]][end[i]] + g[end[i]][start[i + 1]]);
            if(i > 0) {
                setmin(f[i + 1][1], f[i][1] + g[start[i]][end[i - 1]] +
                                        g[end[i - 1]][start[i + 1]]);
                setmin(f[i + 1][0], f[i][1] + g[start[i]][end[i - 1]] +
                                        g[end[i - 1]][end[i]] +
                                        g[end[i]][start[i + 1]]);
            }
        } else {
            setmin(ans, f[i][0] + g[start[i]][end[i]]);
            if(i > 0) {
                setmin(ans, f[i][1] + g[start[i]][end[i - 1]] +
                                g[end[i - 1]][end[i]]);
            }
        }
    }
    if(ans == inf) ans = -1;
    printf("Case #%d: ", cs);
    printf("%lld\n", ans);
}

int main() {
    int num;
    scanf("%d", &num);
    rep(i, 1, num) { solve(i); }
    return 0;
}
