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

int find(VVI a, int color) {
    const function<int(int, int)> dfs = [&](int x, int y) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {1, 0, -1, 0};
        a[x][y] = -1;
        int ans = 1;
        repn(i, 4) {
            int x0 = x + dx[i], y0 = y + dy[i];
            if (x0 < 0 || x0 >= len(a) || y0 < 0 || y0 >= len(a[0])) continue;
            if (a[x0][y0] != color) continue;
            ans += dfs(x0, y0);
        }
        return ans;
    };
    int ans = 0;
    repn(i, len(a)) repn(j, len(a[0])) {
        if (a[i][j] == color) setmax(ans, dfs(i, j));
    }
    return ans;
}

int solve(VS ss) {
    const int n = len(ss), m = len(ss[0]);
    VVI a(n, VI(m));
    repn(i, n) repn(j, m) a[i][j] = (ss[i][j] == 'W');

    int ans = max(find(a, 0), find(a, 1));
    repn(i, n) replr(j, 1, m) {
        VVI b = a;
        repn(x, n) repn(y, m) b[x][y] ^= (y < j ? a[i][j - 1] : a[i][j]);
        setmax(ans, find(b, 0));
    }
    replr(i, 1, n) repn(j, m) {
        VVI b = a;
        repn(x, n) repn(y, m) b[x][y] ^= (x < i ? a[i - 1][j] : a[i][j]);
        setmax(ans, find(b, 0));
    }
    bool has[2][2][2][2];
    fillchar(has, false);
    repn(i, n - 1) repn(j, m - 1) {
        has[a[i][j]][a[i][j + 1]][a[i + 1][j]][a[i + 1][j + 1]] = true;
    }
    repn(c0, 2) repn(c1, 2) repn(c2, 2) repn(c3, 2) if (has[c0][c1][c2][c3]) {
        replr(i, 1, n) replr(j, 1, m) {
            VVI b = a;
            repn(x, n) repn(y, m) {
                if (x < i && y < j)
                    b[x][y] ^= c0;
                else if (x < i)
                    b[x][y] ^= c1;
                else if (y < j)
                    b[x][y] ^= c2;
                else
                    b[x][y] ^= c3;
            }
            // cout << b << " " << i << " " << j << " " << c0 << c1 << c2 << c3
            //<< " -> " << find(b, 0) << endl;
            setmax(ans, find(b, 0));
        }
    }
    return ans;
}

bool connected(VVB b) {
    const function<void(int, int)> dfs = [&](int x, int y) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {1, 0, -1, 0};
        b[x][y] = false;
        repn(i, 4) {
            int x0 = x + dx[i], y0 = y + dy[i];
            if (x0 >= 0 && x0 < len(b) && y0 >= 0 && y0 < len(b[0]) &&
                b[x0][y0]) {
                dfs(x0, y0);
            }
        }
    };
    int cnt = 0;
    repn(i, len(b)) repn(j, len(b[0])) {
        if (b[i][j]) {
            dfs(i, j), ++cnt;
        }
    }
    return cnt <= 1;
}

static VVB best;

int solve0(VS ss) {
    const int n = len(ss), m = len(ss[0]);
    int t = 1;
    while (t < n || t < m) t *= 2;
    VS big;
    repn(i, n) {
        string cur;
        repn(j, m) repn(k, t) cur += ss[i][j];
        repn(k, t) big.pb(cur);
    }
    // cout << big << endl;
    int ans = 0;
    repn(st, 1 << (n * m)) {
        VVB b(n, VB(m, false));
        int cur = 0;
        repn(i, n) repn(j, m) {
            if (st & (1 << (i * m + j))) {
                ++cur, b[i][j] = true;
            }
        }
        if (connected(b)) {
            bool ok = false;
            repn(i, len(big)) repn(j, len(big[0])) {
                bool this_ok = true;
                repn(x, n) repn(y, m) if (b[x][y]) {
                    if (i + x < len(big) && j + y < len(big[0]) &&
                        big[i + x][j + y] == ss[x][y]) {
                        continue;
                    }
                    this_ok = false;
                    break;
                }
                if (this_ok) {
                    ok = true;
                    break;
                }
            }
            if (ok) {
                if (setmax(ans, cur)) best = b;
            }
        }
    }
    return ans;
}

void check() {
    const int n = 3, m = 5;
    while (1) {
        VS ss(n);
        repn(i, n) repn(j, m) ss[i] += (rand() % 2 == 0 ? 'B' : 'W');
        int r1 = solve(ss);
        int r2 = solve0(ss);
        cout << ss << " " << r1 << " " << r2 << endl;
        if (r1 != r2) {
            repn(i, n) {
                repn(j, m) printf("%d", (int)best[i][j]);
                printf("\n");
            }
        }
        assert(r1 == r2);
    }
}

int main() {
    check();
    int num;
    scanf("%d", &num);
    rep(cs, 1, num) {
        VS ss(IN);
        (void)IN;
        repn(i, len(ss)) ss[i] = read_string();
        int ans = solve(ss);
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}
