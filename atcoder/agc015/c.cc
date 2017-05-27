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

const int N = 2020;

int sr[N][N], sl[N][N], su[N][N], sd[N][N];
int s[N][N];
char board[N][N];
int n, m;

void prepare() {
    fillchar(sl, 0);
    fillchar(sr, 0);
    fillchar(su, 0);
    fillchar(sd, 0);
    fillchar(s, 0);
    const function<void(int, int)> dfs = [&](int x, int y) {
        board[x][y] = '*';
        constexpr int dx[4] = {1, 0, -1, 0};
        constexpr int dy[4] = {0, 1, 0, -1};
        repn(i, 4) {
            int x0 = x + dx[i], y0 = y + dy[i];
            if(board[x0][y0] == '1') {
                dfs(x0, y0);
                if(i == 0) ++sd[x][y];
                if(i == 1) ++sr[x][y];
                if(i == 2) ++su[x][y];
                if(i == 3) ++sl[x][y];
            }
        }
    };
    rep(i, 1, n) rep(j, 1, m) {
        if(board[i][j] == '1') {
            s[i][j] = 1;
            dfs(i, j);
        }
    }
    rep(i, 1, n) rep(j, 1, m) {
        sl[i][j] += sl[i - 1][j];
        sr[i][j] += sr[i - 1][j];
        su[i][j] += su[i][j - 1];
        sd[i][j] += sd[i][j - 1];
        s[i][j] += s[i][j - 1] + s[i - 1][j] - s[i - 1][j - 1];
    }
}

int main() {
    int q;
    scanf("%d%d%d", &n, &m, &q);
    fillchar(board, ' ');
    rep(i, 1, n) scanf("%s", board[i] + 1);
    prepare();
    while(q--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int ans = 0;
        ans += sr[x2][y1 - 1] - sr[x1 - 1][y1 - 1];
        ans += sl[x2][y2 + 1] - sl[x1 - 1][y2 + 1];
        ans += sd[x1 - 1][y2] - sd[x1 - 1][y1 - 1];
        ans += su[x2 + 1][y2] - su[x2 + 1][y1 - 1];
        ans += s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
        printf("%d\n", ans);
    }
    return 0;
}
