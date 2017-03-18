#include <algorithm>
#include <cassert>
#include <cmath>
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
// clang-format on
// }}}

double f[21][21][410];

void prepare() {
    fillchar(f, 0);
    rep(die, 1, 20) {
        f[die][0][0] = 1;
        repn(i, 20) rep(s, 0, die * i) {
            rep(cur, 1, die) {
                f[die][i + 1][s + cur] += f[die][i][s] / double(die);
            }
        }
    }
}

double get(int die, int times, int need) {
    double r = 0;
    rep(s, max(need, 0), die * times) { r += f[die][times][s]; }
    return r;
}

void solve(int cs) {
    int need, n;
    scanf("%d%d", &need, &n);
    double ans = 0;
    repn(i, n) {
        char buf[99];
        scanf("%s", buf);
        string s(buf);
        auto p = s.find('d');
        auto q = s.find('+');
        if(q == string::npos) q = s.find('-');
        int times = stoi(s.substr(0, p));
        int die = stoi(s.substr(p + 1, q - p - 1));
        int delta = 0;
        if(q != string::npos) {
            delta = stoi(s.substr(q + 1));
            if(s[q] == '-') delta = -delta;
        }
        setmax(ans, get(die, times, need - delta));
    }
    printf("Case #%d: ", cs);
    printf("%.9lf\n", ans);
}

int main() {
    prepare();

    int num;
    scanf("%d", &num);
    rep(i, 1, num) { solve(i); }
    return 0;
}