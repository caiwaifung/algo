// 20:11 - est. 20:25
//       - 20:19 - wa sample
//       - 20:29 - pass
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
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef vector<VD> VVD;
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
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    VVI es(n);
    repn(i, m) {
        int a, b;
        scanf("%d%d", &a, &b), --a, --b;
        es[a].pb(b), es[b].pb(a);
    }

    vector<bool> valid(n, true);
    VI vis(n, 0);
    const function<void(int, int)> mark = [&](int x, int fa) {
        vis[x] = -1;
        VI es0 = es[x];
        es[x].clear();
        for(int y : es0) {
            if(y != fa) {
                if(vis[y] == 1) continue;
                if(vis[y] == -1) {
                    assert(valid[x] && valid[fa]);
                    valid[x] = valid[fa] = false;
                }
                if(vis[y] == 0) {
                    es[x].pb(y);
                    mark(y, x);
                }
            }
        }
        vis[x] = 1;
    };
    valid[0] = false;
    mark(0, -1);

    VVI f(n, VI(2, 0));
    int ans = 0;
    const function<void(int)> dfs = [&](int x) {
        int dp[2][2];
        repn(i, 2) repn(j, 2) dp[i][j] = -(1 << 30);
        dp[1][0] = 0;
        for(int y : es[x]) {
            dfs(y);
            if(valid[y]) {
                int tmp[2][2];
                memmove(tmp, dp, sizeof(dp));
                repn(i, 2) repn(j, 2) dp[i][j] = -(1 << 30);
                repn(i, 2) repn(j, 2) repn(k, 2) {
                    int val = tmp[i][j] + f[y][k];
                    setmax(dp[i][j | k], val);
                    if(i && k) setmax(dp[0][j], val + 1);
                    if(j && k) setmax(dp[i][0], val + 1);
                }
            }
        }
        repn(i, 2) f[x][i] = max(dp[i][0], dp[i][1]);
        setmax(f[x][0], f[x][1]);
        if(!valid[x]) ans += f[x][1];
    };
    dfs(0);
    printf("%d\n", ans);

    return 0;
}
