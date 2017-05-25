// 12:35
// 12:39 - eta 12:50
//       - 12:50 - wa sample
//       - 13:03 - wa
//       - 13:08 - tle
//       - 13:17 - ac
// 42
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

LL solve(LL n0) {
    VI n;
    while(n0 > 0) n.pb(n0 % 10), n0 /= 10;
    n.pb(0), n.pb(0);
    LL ans = 0;
    repn(b1, 10) replr(b2, b1, 10) replr(b3, b2, 10) {
        int sum = b1 + b2 + b3;
        if(sum == 0) continue;
        if(b1 == b2 && b2 == b3) {
            static LL f[22][4][2][30];
            fillchar(f, 0);
            f[sz(n)][0][1][0] = 1;
            irepn(i, sz(n)) repn(c, 4) {
                repn(eq, 2) repn(mod, sum) {
                    LL val = f[i + 1][c][eq][mod];
                    if(val == 0) continue;
                    repn(cur, 10) {
                        if(cur > b1 && cur != b2 && cur != b3) continue;
                        if(eq && cur > n[i]) break;
                        int cp = min(3, c + (cur == b1));
                        int eqp = eq && (cur == n[i]);
                        int modp = (mod * 10 + cur) % sum;
                        f[i][cp][eqp][modp] += val;
                    }
                }
            }
            repn(eq, 2) ans += f[0][3][eq][0];
        } else if(b1 == b2) {
            static LL f[22][3][2][2][30];
            fillchar(f, 0);
            f[sz(n)][0][0][1][0] = 1;
            irepn(i, sz(n)) repn(c1, 3) repn(c3, 2) {
                repn(eq, 2) repn(mod, sum) {
                    LL val = f[i + 1][c1][c3][eq][mod];
                    if(val == 0) continue;
                    repn(cur, 10) {
                        if(cur > b1 && cur != b2 && cur != b3) continue;
                        if(eq && cur > n[i]) break;
                        int c1p = min(2, c1 + (cur == b1));
                        int c3p = c3 + (cur == b3);
                        int eqp = eq && (cur == n[i]);
                        int modp = (mod * 10 + cur) % sum;
                        if(c3p <= 1) f[i][c1p][c3p][eqp][modp] += val;
                    }
                }
            }
            repn(eq, 2) ans += f[0][2][1][eq][0];
        } else if(b2 == b3) {
            static LL f[22][2][3][2][30];
            fillchar(f, 0);
            f[sz(n)][0][0][1][0] = 1;
            irepn(i, sz(n)) repn(c1, 2) repn(c3, 3) {
                repn(eq, 2) repn(mod, sum) {
                    LL val = f[i + 1][c1][c3][eq][mod];
                    if(val == 0) continue;
                    repn(cur, 10) {
                        if(cur > b1 && cur != b2 && cur != b3) continue;
                        if(eq && cur > n[i]) break;
                        int c1p = c1 || (cur == b1);
                        int c3p = c3 + (cur == b3);
                        int eqp = eq && (cur == n[i]);
                        int modp = (mod * 10 + cur) % sum;
                        if(c3p <= 2) f[i][c1p][c3p][eqp][modp] += val;
                    }
                }
            }
            repn(eq, 2) ans += f[0][1][2][eq][0];
        } else {
            static LL f[22][2][2][2][2][30];
            fillchar(f, 0);
            f[sz(n)][0][0][0][1][0] = 1;
            irepn(i, sz(n)) repn(c1, 2) repn(c2, 2) repn(c3, 2) {
                repn(eq, 2) repn(mod, sum) {
                    LL val = f[i + 1][c1][c2][c3][eq][mod];
                    if(val == 0) continue;
                    repn(cur, 10) {
                        if(cur > b1 && cur != b2 && cur != b3) continue;
                        if(eq && cur > n[i]) break;
                        int c1p = c1 || (cur == b1);
                        int c2p = c2 + (cur == b2);
                        int c3p = c3 + (cur == b3);
                        int eqp = eq && (cur == n[i]);
                        int modp = (mod * 10 + cur) % sum;
                        if(c2p <= 1 && c3p <= 1)
                            f[i][c1p][c2p][c3p][eqp][modp] += val;
                    }
                }
            }
            repn(eq, 2) ans += f[0][1][1][1][eq][0];
        }
    }
    return ans;
}

int main() {
    //repn(i, 200) solve(1ll << 55); return 0;
    int n;
    scanf("%d", &n);
    while(n--) {
        for(const auto& p : read_vpl(1)) {
            LL ans = solve(p.se);
            ans -= solve(p.fi - 1);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
