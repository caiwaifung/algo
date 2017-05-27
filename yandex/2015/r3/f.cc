// 10:55
// 11:08 - eta 11:15
//       - 11:17 - wa sample
//       - 11:20 - wa
//       - 11:29 - ac
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
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

typedef pair<LL, int> PLI;

VL bfs(const VVPI& es, int start) {
    VL dis(sz(es), 1ll << 60);
    VB vis(sz(es), false);
    priority_queue<PLI, vector<PLI>, greater<PLI>> que;
    dis[start] = 0;
    que.push({dis[start], start});
    while(!que.empty()) {
        int x = que.top().se;
        que.pop();
        if(vis[x]) continue;
        vis[x] = true;
        for(const auto& e : es[x]) {
            if(setmin(dis[e.fi], dis[x] + e.se)) {
                que.push({dis[e.fi], e.fi});
            }
        }
    }
    return dis;
}

LL solve() {
    int n, m, s, t, a, b;
    scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &a, &b);
    if(s == t) return 0;
    --s, --t;
    VVPI es(n);
    LL ans = 1ll << 60;
    vector<pair<PII, PII>> ps;
    repn(i, m) {
        int u, v, w, c;
        scanf("%d%d%d%d", &u, &v, &w, &c);
        --u, --v;
        if(w < 0) return 0;
        setmin(ans, LL(w + 1) * LL(c));
        es[u].pb({v, w});
        es[v].pb({u, w});
        ps.pb({{u, v}, {w, c}});
    }
    VL ds = bfs(es, s);
    VL dt = bfs(es, t);
    for(const auto& kv : ps) {
        int u = kv.fi.fi, v = kv.fi.se, w = kv.se.fi, c = kv.se.se;
        LL increase = min(ds[u] + dt[v], ds[v] + dt[u]) + w;
        LL need = max(0ll, increase + a - b);
        setmin(ans, need * c);
    }
    return ans;
}

int main() {
    LL ans = solve();
    printf("%lld\n", ans);
    return 0;
}
