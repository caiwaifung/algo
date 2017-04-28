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
// clang-format on
// }}}

int main() {
    rep(n, 2, 8) rep(m, 1, n - 1) {
        printf("%d %d: ", n, m);
        int en = n * (n - 1) / 2;
        repn(s, 1 << en) {
            vector<vector<bool>> g(n, vector<bool>(n));
            int cur = 0;
            repn(i, n) replr(j, i + 1, n) {
                g[i][j] = g[j][i] = (s & (1 << (cur++))) > 0;
            }
            assert(cur == en);
            bool ok = true;
            for(bool color : {true, false}) {
                vector<VI> d(n, VI(n, 1 << 28));
                repn(i, n) d[i][i] = 0;
                repn(i, n) repn(j, n) if(i != j && g[i][j] == color) d[i][j] =
                    1;
                repn(k, n) repn(i, n) repn(j, n)
                    setmin(d[i][j], d[i][k] + d[k][j]);
                int maxd = 0;
                repn(i, n) repn(j, n) setmax(maxd, d[i][j]);
                if(maxd != m) ok = false;
            }
            if(ok) {
                /*
                repn(i, n) replr(j, i + 1, n) if(g[i][j]) {
                    printf("%d %d\n", i, j);
                }
                */
                printf("yes\n");
                goto end;
            }
        }
        printf("no\n");
    end : {}
    }
    return 0;
}
