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

const LL MOD = LL(1e9) + 7;

int main() {
    int n;
    scanf("%d", &n);
    VVI es(n);
    repn(i, n - 1) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        es[a].pb(b), es[b].pb(a);
    }
    VL p2(n + 10);
    p2[0] = 1;
    replr(i, 1, sz(p2)) p2[i] = p2[i - 1] * 2 % MOD;

    VL b(n);
    VI d(n);
    const function<void(int, int)> dfs = [&](int x, int fa) {
        for(int y : es[x]) {
            if(y != fa) {
                dfs(y, x);
                (b[x] += b[y]) %= MOD;
                setmax(d[x], d[y] + 1);
            }
        }
        (b[x] += p2[d[x]]) %= MOD;
    };
    dfs(0, -1);

    VL ans(n);
    const function<void(int, int, LL, int)> dfs2 = [&](int x, int fa, LL bf,
                                                       int df) {
        VI ys;
        ans[x] = bf;
        for(int y : es[x]) {
            if(y != fa) {
                ys.pb(y);
                (ans[x] += b[y]) %= MOD;
            }
        }

        VL bl(sz(ys) + 1), br(sz(ys) + 1);
        VI dl(sz(ys) + 1), dr(sz(ys) + 1);
        bl[0] = bf, dl[0] = df + 1;
        repn(i, sz(ys)) {
            bl[i + 1] = (bl[i] + b[ys[i]]) % MOD;
            dl[i + 1] = max(dl[i], d[ys[i]] + 1);
        }
        irepn(i, sz(ys)) {
            br[i] = (br[i + 1] + b[ys[i]]) % MOD;
            dr[i] = max(dr[i + 1], d[ys[i]] + 1);
        }
        repn(i, sz(ys)) {
            int y = ys[i];
            LL curb = (bl[i] + br[i + 1]) % MOD;
            int curd = max(dl[i], dr[i + 1]);
            (curb += p2[curd]) %= MOD;
            dfs2(y, x, curb, curd);
        }

    };
    dfs2(0, -1, 0, -1);
    repn(i, n) printf("%lld\n", ans[i]);

    return 0;
}
