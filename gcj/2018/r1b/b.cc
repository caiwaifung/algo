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
#define len(a) static_cast<int>((a).size())
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
template <class T> ostream& operator<<(ostream& os, const unordered_set<T>& v) { os << "{"; for(T x: v) { os << x<<","; }; return os << "}"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, len(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
int read_int() { int x; scanf("%d", &x); return x; }
LL read_ll() { LL x; scanf("%lld", &x); return x; }
string read_string() { string s; cin >> s; return s; }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
#define IN read_int()
// clang-format on
// }}}

PII solve(VI xs, VI ys) {
    const int n = len(xs);
    int ans = 0, ansc = 0, target = 0;
    unordered_map<int, int> cx, cy;
    vector<unordered_set<int>> vx(1), vy(1);
    map<PII, int> es;
    for (int x : xs) vx[0].insert(x);
    for (int y : ys) vy[0].insert(y);
    const auto ok = [&]() {
        if (len(vx) - 1 + len(vy) - 1 > target) return true;
        if (len(vx) - 1 + len(vy) - 1 < target) return false;
        for (int x : vx.back()) {
            for (int y : vy.back()) {
                if (es[mp(x, y)] == 0) {
                    return true;
                }
            }
        }
        return false;
    };
    const auto add = [&](int i) {
        const int x = xs[i], y = ys[i];
        if (++es[mp(x, y)] > 1) return;
        ++target;
        assert(cx[x] < len(vx) && cy[y] < len(vy));
        vx[cx[x]].erase(x), vy[cy[y]].erase(y);
        cx[x]++, cy[y]++;
        if (cx[x] >= len(vx)) vx.pb({});
        if (cy[y] >= len(vy)) vy.pb({});
        assert(cx[x] < len(vx) && cy[y] < len(vy));
        vx[cx[x]].insert(x), vy[cy[y]].insert(y);
    };
    const auto remove = [&](int i) {
        const int x = xs[i], y = ys[i];
        if (--es[mp(x, y)] > 0) return;
        --target;
        assert(cx[x] < len(vx) && cy[y] < len(vy));
        vx[cx[x]].erase(x), vy[cy[y]].erase(y);
        if (vx.back().empty()) vx.pop_back();
        if (vy.back().empty()) vy.pop_back();
        cx[x]--, cy[y]--;
        assert(cx[x] < len(vx) && cy[y] < len(vy));
        vx[cx[x]].insert(x), vy[cy[y]].insert(y);
    };
    int l = 0;
    //cout << xs << endl << ys << endl;
    repn(r, n) {
        add(r);
        while (true) {
            //cout << l << " " << r << endl;
            //cout << "  cx: " << VPI(all(cx)) << endl;
            //cout << "  cy: " << VPI(all(cy)) << endl;
            //cout << "  vx: " << vx << endl;
            //cout << "  vy: " << vy << endl;
            //cout << "  target:" << target << endl;
            if (ok()) break;
            remove(l++);
        }
        int cur = r - l + 1;
        if (ans < cur) ans = cur, ansc = 0;
        if (ans == cur) ++ansc;
    }
    return {ans, ansc};
}

PII solve2(VI xs, VI ys) {
    int ans = 0, ansc = 0;
    const auto ok = [&](int l, int r) {
        replr(i, l, r + 1) replr(j, l, r + 1) {
            bool good = true;
            replr(k, l, r + 1) if (!(xs[k] == xs[i] || ys[k] == ys[j])) {
                good = false;
            }
            if (good) return true;
        }
        return false;
    };
    repn(i, len(xs)) replr(j, i, len(xs)) {
        if (ok(i, j)) {
            int cur = j - i + 1;
            if (ans < cur) ans = cur, ansc = 0;
            if (ans == cur) ansc++;
        }
    }
    return {ans, ansc};
}

void solve(int cs) {
    printf("Case #%d: ", cs);
    int n = IN;
    VI xs, ys;
    repn(i, n) {
        int d = IN, dr = IN, dl = IN, x = d - dl, y = d + dr;
        xs.pb(x), ys.pb(y);
    }
    auto ans = solve(xs, ys);
    printf("%d %d\n", ans.fi, ans.se);
}

int main() {
    //cout << solve({1, 2, 1, 0, 2}, {2, 1, 0, 2, 2});
    //return 0;
    while (1) {
        VI xs, ys;
        repn(i, 50) xs.pb(rand() % 3);
        repn(i, 50) ys.pb(rand() % 3);
        auto ans = solve(xs, ys), ans2 = solve2(xs, ys);
        if (ans != ans2) {
            cout << xs << endl << ys << endl << ans << " " << ans2 << endl;
            return 0;
        } else {
            cout << ans << endl;
        }
    }
    int num;
    scanf("%d", &num);
    rep(i, 1, num) { solve(i); }
    return 0;
}
