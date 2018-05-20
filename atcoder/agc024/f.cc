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

int remove(int s, int i) {
    int low = s & ((1 << i) - 1);
    int high = s ^ low;
    if (high & (1 << i)) high ^= (1 << i);
    return (high >> 1) | low;
}

int length(int s) {
    int i = 0;
    while ((1 << i) <= s) ++i;
    return i;
}

int main() {
    int n = IN, k = IN;
    VI ss;
    rep(i, 0, n) {
        string s = read_string();
        repn(j, 1 << i) if (s[j] == '1') { ss.pb((1 << i) + j); }
    }
    static int f[1 << 21][21][2];
    static int cnt[1 << 21];
    fillchar(f, 0);
    fillchar(cnt, 0);
    for (int s : ss) {
        f[s][0][0]++;
        f[s][0][1]++;
        cnt[1]++;
    }
    irepn(s, 1 << (n + 1)) repn(i, n) repn(c, 2) {
        if ((1 << (i + 1)) > s) continue;
        const int cur = f[s][i][c];
        if ((s & (1 << i)) == (c << i)) {
            int b = 1 << (i + 1);
            cnt[b | (s & (b - 1))] += cur;
            f[s][i + 1][0] += cur;
            f[s][i + 1][1] += cur;
        } else {
            f[remove(s, i)][i][c] += cur;
        }
    }
    // repn(s, 1 << (n + 1)) cout << s << " " << cnt[s] << endl;

    int x = 1;
    repn(s, 1 << (n + 1)) if (cnt[s] >= k) {
        if (length(s) > length(x)) x = s;
    }
    string ans;
    while (x > 1) ans += char('0' + (x & 1)), x >>= 1;
    reverse(all(ans));
    cout << ans << endl;
    return 0;
}
