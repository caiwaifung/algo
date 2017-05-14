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

#define x first
#define y second

LL sqr(LL x) { return x * x; }

PLL radius(PLL p0, PLL p1, PLL p2) {
    p0.x *= 2, p0.y *= 2, p1.x *= 2, p1.y *= 2, p2.x *= 2, p2.y *= 2;
    LL a1 = p1.x - p0.x, b1 = p1.y - p0.y, c1 = (sqr(a1) + sqr(b1)) / 2;
    LL a2 = p2.x - p0.x, b2 = p2.y - p0.y, c2 = (sqr(a2) + sqr(b2)) / 2;
    LL d = a1 * b2 - a2 * b1;
    LL upper = sqr(c1 * b2 - c2 * b1) + sqr(a1 * c2 - a2 * c1);
    LL lower = d * d;
    LL g = gcd(upper, lower);
    return mp(upper / g, lower / g);
}

int main() {
    map<PLL, int> m;
    int n;
    cin >> n;
    while(n--) {
        PLL p0, p1, p2;
        cin >> p0.x >> p0.y;
        cin >> p1.x >> p1.y;
        cin >> p2.x >> p2.y;
        m[radius(p0, p1, p2)]++;
    }
    int ans = 0;
    for(const auto& kv : m) setmax(ans, kv.se);
    cout << ans << endl;
    return 0;
}
