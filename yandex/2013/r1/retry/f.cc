// 10:41 - 10:48 - wa
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
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

int main() {
    int n, d;
    cin >> n >> d;
    VS ws(n);
    repn(i, n) cin >> ws[i];
    string s;
    cin >> s;

    static int match[50][51][10001];
    repn(i, n) irep(ip, d, 0) irep(sp, sz(s), 0) {
        if(ip == d || sp == sz(s) || ws[i][ip] != s[sp]) {
            match[i][ip][sp] = 0;
        } else {
            match[i][ip][sp] = 1 + match[i][ip + 1][sp + 1];
        }
    }
    VI f(sz(s) + 1, 1 << 30), g(sz(s) + 1, 1 << 30);
    const int kInf = f[0];
    g[0] = 0;
    repn(sp, sz(s)) {
        repn(ip, d) {
            int rlen = d - ip;
            if(ip > sp || sp + rlen > sz(s)) continue;
            repn(i, n) {
                int len = match[i][ip][sp];
                int val = f[sp];
                if(ip == 0 || match[i][0][sp - ip] >= ip) {
                    setmin(val, g[sp]);
                }
                if(len == rlen) {
                    setmin(f[sp + len], val + 1);
                } else {
                    setmin(g[sp + len], val + 1);
                }
            }
        }
    }
    int ans = f[sz(s)];
    if(ans == kInf) {
        cout << "NO" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
