// 11:28 - eta 11:40
//       - 11:37 - re sample
//       - 11:42 - 
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

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    VVI es(n);
    VI cost(n);
    repn(i, n) scanf("%d", &cost[i]);
    repn(i, m) {
        int a, b;
        scanf("%d%d", &a, &b), --a, --b;
        es[a].pb(b);
    }

    int num = 0, counter = 0;
    VI dfn(n), low(n), belong(n, -1), stack;
    const function<void(int)> dfs = [&](int x) {
        dfn[x] = low[x] = counter++;
        belong[x] = -2;
        stack.pb(x);
        for(int y : es[x]) {
            if(belong[y] == -1) {
                dfs(y);
                setmin(low[x], low[y]);
            } else if(belong[y] == -2) {
                setmin(low[x], dfn[y]);
            }
        }
        if(low[x] == dfn[x]) {
            for(int y = -1; y != x;) {
                y = stack.back();
                stack.pop_back();
                belong[y] = num;
            }
            ++num;
        }
    };
    repn(i, n) if(belong[i] < 0) dfs(i);

    VVPI nes(num);
    repn(x, n) for(int y : es[x]) {
        if(belong[x] != belong[y]) {
            nes[belong[x]].pb(mp(belong[y], cost[y]));
        }
    }
    VI ans(n, 1 << 30);
    for(int y : es[0]) setmin(ans[belong[y]], cost[y]);
    irepn(i, num) for(const auto& e : nes[i]) {
        setmin(ans[e.fi], ans[i] + e.se);
    }
    printf("%d\n", ans[belong[n - 1]]);

    return 0;
}