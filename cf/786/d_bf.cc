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

const int N = 20010;

vector<pair<int, char>> es[N];
int fa[N], size[N], dep[N];
char fc[N];
int n, q;

void dfs(int x, int f, char c, int d) {
    fa[x] = f, fc[x] = c, dep[x] = d;
    size[x] = 1;
    for(const auto& e : es[x]) {
        if(e.fi != f) {
            dfs(e.fi, x, e.se, d + 1);
            size[x] += size[e.fi];
        }
    }
}

int get_size(int x, int y) { return fa[y] == x ? size[y] : n - size[x]; }

char arr[N];
int len;
struct Elem {
    int x, f, ind;
} stack[N];

int solve(int x, int y) {
    int l = 0, r = N;
    for(int u = x, v = y; u != v;) {
        if(dep[u] > dep[v]) {
            arr[l++] = fc[u];
            u = fa[u];
        } else {
            arr[--r] = fc[v];
            v = fa[v];
        }
    }
    len = l + N - r;
    memmove(arr + l, arr + r, N - r);

    int tot = -1;
    int top = 1;
    stack[0] = {x, -1, 0};
    while(top > 0) {
        const Elem cur = stack[--top];
        // printf("%d %d %d\n", cur.x, cur.f, cur.ind);
        ++tot;
        for(const auto& e : es[cur.x]) {
            if(e.fi != cur.f) {
                if(e.se < arr[cur.ind]) {
                    tot += get_size(cur.x, e.fi);
                } else if(cur.ind + 1 < len && e.se == arr[cur.ind]) {
                    stack[top++] = {e.fi, cur.x, cur.ind + 1};
                }
            }
        }
    }
    return tot;
}

void init() {
    scanf("%d%d", &n, &q);
    repn(i, n - 1) {
        int a, b;
        char c;
        scanf("%d%d %c", &a, &b, &c);
        --a, --b;
        es[a].pb(mp(b, c)), es[b].pb(mp(a, c));
    }
}

void init2() {
    n = q = 20000;
    repn(i, n - 1) {
        int a = i, b = i + 1;
        char c = 'a';
        es[a].pb(mp(b, c)), es[b].pb(mp(a, c));
    }
}

int main() {
    // init();
    init2();
    dfs(0, -1, '?', 0);

    map<PII, int> ans;
    while(q--) {
        int x, y;
        // scanf("%d%d", &x, &y);
        x = 1, y = n;
        --x, --y;
        if(ans.count(mp(x, y))) {
            printf("%d\n", ans[mp(x, y)]);
            // continue;
        }
        int r = solve(x, y);
        ans[mp(x, y)] = r;
        printf("%d\n", r);
    }

    return 0;
}
