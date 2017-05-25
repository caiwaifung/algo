// 13:55
// 14:04 - eta 14:20
//       - 14:29 - wa sample
//       - 14:37 - tle
//       - 14:51 - tle
//       - 15:14 - ac
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

const int N = 100010;

VPI factors[N];
VL primes[N];

void prepare() {
    replr(n, 1, N) {
        LL x = n;
        for(LL y = 2; y * y <= x; ++y) {
            if(x % y == 0) {
                while(x % y == 0) x /= y;
                primes[n].pb(y);
            }
        }
        if(x > 1) {
            primes[n].pb(x);
        }
        repn(s, 1 << sz(primes[n])) {
            int t = 1, sign = 1;
            repn(i, sz(primes[n])) if(s & (1 << i)) {
                t *= primes[n][i];
                sign = -sign;
            }
            factors[n].pb(mp(t, sign));
        }
        sort(all(factors[n]));
    }
}

LL count_le(LL n, LL x) {
    LL ans = 0;
    for(const auto& p : factors[n]) {
        LL cur = x / p.fi;
        if(cur == 0) break;
        ans += p.se * cur;
    }
    return ans;
}

LL index(LL n, LL a, LL b, LL lim = 1ll << 60) {
    LL ans = 0;
    rep(cb, 1, n) {
        LL ca = cb * a / b;
        ans += count_le(cb, ca);
        if(ans > lim) break;
    }
    return ans;
}

void solve1(LL n, LL ind) {
    if(ind == 0) {
        printf("0/1\n");
        return;
    }
    if(ind > index(n, 1, 1)) {
        printf("none\n");
        return;
    }
    LL l = 1, r = n;
    while(l < r) {
        LL mid = (l + r) / 2;
        if(index(n, mid, n, ind) >= ind) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    LL need = ind - index(n, l - 1, n, ind);
    VPL ps;
    rep(b, 1, n) {
        LL a = l * b / n;
        if(a * n > (l - 1) * b && gcd(a, (LL)b) == 1) ps.pb({a, b});
    }
    assert(sz(ps) >= need);
    sort(all(ps),
         [](const PLL& u, const PLL& v) { return u.fi * v.se < u.se * v.fi; });
    printf("%lld/%lld\n", ps[need - 1].fi, ps[need - 1].se);
}

void solve2(LL n, LL a, LL b) {
    LL g = gcd(a, b);
    a /= g, b /= g;
    if(b > n || a > b || gcd(a, b) != 1) {
        printf("none\n");
        return;
    }
    if(a == 0) {
        printf("0\n");
    } else {
        printf("%lld\n", index(n, a, b));
    }
}

int main() {
    prepare();
    int qn;
    scanf("%d", &qn);
    while(qn--) {
        int t;
        LL n;
        scanf("%d%lld", &t, &n);
        if(t == 0) {
            LL ind;
            scanf("%lld", &ind);
            solve1(n, ind);
        } else {
            LL a, b;
            scanf("%lld%lld", &a, &b);
            solve2(n, a, b);
        }
    }
    return 0;
}
