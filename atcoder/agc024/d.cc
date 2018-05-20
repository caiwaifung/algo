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

VI bfs(const VVI& es, int start) {
    const int n = len(es);
    VI pre(n, -1);
    queue<int> que;
    que.push(start), pre[start] = -2;
    int x = start;
    while (!que.empty()) {
        x = que.front(), que.pop();
        for (int y : es[x]) {
            if (pre[y] == -1) {
                pre[y] = x, que.push(y);
            }
        }
    }
    VI path;
    while (x >= 0) path.pb(x), x = pre[x];
    reverse(all(path));
    return path;
}

pair<int, LL> cal(const VVI& es, int x1, int x2 = -1) {
    VI maxd(1);
    const function<void(int, int, int)> dfs = [&](int x, int fa, int d) {
        if (d >= len(maxd)) maxd.pb(0);
        int cur = 0;
        for (int y : es[x]) {
            if (y != fa) {
                ++cur;
                dfs(y, x, d + 1);
            }
        }
        setmax(maxd[d], cur);
    };
    dfs(x1, x2, 0);
    if (x2 >= 0) dfs(x2, x1, 0);
    LL s = 1;
    // cout << x1 + 1 << " " << x2 + 1 << " " << maxd << endl;
    repn(i, len(maxd) - 1) s *= maxd[i];
    if (x2 >= 0) s *= 2;
    return {len(maxd), s};
}

int main() {
    const int n = IN;
    VVI es(n);
    repn(i, n - 1) {
        int a = IN - 1, b = IN - 1;
        es[a].pb(b), es[b].pb(a);
    }
    VI path = bfs(es, bfs(es, 0).back());
    pair<int, LL> ans;
    if (len(path) % 2 == 0) {
        int x = path[len(path) / 2 - 1], y = path[len(path) / 2];
        ans = cal(es, x, y);
        assert(ans.fi == len(path) / 2);
    } else {
        int x = path[len(path) / 2];
        ans = cal(es, x);
        for (int y : es[x]) setmin(ans, cal(es, x, y));
        assert(ans.fi == len(path) / 2 + 1);
    }
    cout << ans.fi << " " << ans.se << endl;

    return 0;
}
