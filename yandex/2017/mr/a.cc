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
#include <random>
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
#define x first
#define y second
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
typedef vector<VI> VVI;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

VI mincost_match(const VVI& a) {  // {{{
    const int n = sz(a);
    VI x(n, -1000), y(n), matched(n, -1);
    repn(cur, n) {
        VI slack(n, 1 << 30), pre(n, -1);
        vector<bool> vis(n, false);
        int j0 = -1;
        while(1) {
            const int i0 = (j0 < 0 ? cur : matched[j0]);
            if(i0 < 0) break;
            int minv = 1 << 30, minj = -1;
            repn(j, n) if(!vis[j]) {
                if(setmin(slack[j], a[i0][j] - x[i0] - y[j])) {
                    pre[j] = j0;
                }
                if(setmin(minv, slack[j])) {
                    minj = j;
                }
            }
            x[cur] += minv;
            repn(j, n) if(vis[j]) {
                x[matched[j]] += minv;
                y[j] -= minv;
            }
            else {
                slack[j] -= minv;
            }
            j0 = minj, vis[j0] = true;
        }
        while(j0 >= 0) {
            const int j = pre[j0];
            matched[j0] = (j < 0 ? cur : matched[j]), j0 = j;
        }
    }
    VI ans(n);
    repn(j, n) ans[matched[j]] = j;
    return ans;
}  // }}}

int rand_uniform(int n) {  // {{{
    static default_random_engine gen;
    uniform_int_distribution<int> distr(0, n - 1);
    return distr(gen);
}

VI rand_perm(int n) {
    VI a(n);
    iota(all(a), 0);
    repn(i, n) swap(a[i], a[rand_uniform(i + 1)]);
    return a;
}
// }}}

// const int kInf = 1 << 30;

/*
// -1: unvisited; >=0: blocked
void bfs(VVI* a, int x, int y) {
    if((*a)[x][y] >= 0) return;
    // TODO
}

VVI bfs_func(const VVI& a, int x, int y) {
    VVI tmp = a;
    bfs(&tmp, x, y);
    return tmp;
}
*/

VPI find_path(const VVI& a, PII start, PII end) {
    if(a[start.x][start.y] >= 0) return {};
    if(start == end) return {start};

    const int n = sz(a), m = sz(a[0]);
    vector<VPI> pre(n, VPI(m, {-1, -1}));
    queue<PII> que;
    pre[start.x][start.y] = start, que.push(start);
    while(!que.empty()) {
        const PII u = que.front();
        que.pop();
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {1, 0, -1, 0};
        const VI directions = rand_perm(4);
        for(int i : directions) {
            const PII v = {u.x + dx[i], u.y + dy[i]};
            if(v.x < 0 || v.x >= n || v.y < 0 || v.y >= m) continue;
            if(a[v.x][v.y] < 0 && pre[v.x][v.y].x < 0) {
                pre[v.x][v.y] = u, que.push(v);
                if(v == end) {
                    VPI ans;
                    for(PII p = end; p != start; p = pre[p.x][p.y]) {
                        ans.pb(p);
                    }
                    ans.pb(start);
                    return ans;
                }
            }
        }
    }
    return {};
}

//==============================================================================
// UTIL ENDS
//==============================================================================

vector<VPI> find_matches(int n, int m, int k, VPI p, VPI q) {
    while(1) {
        // TODO: randomize this match.
        VVI cost(k, VI(k));
        repn(i, k) repn(j, k) {
            cost[i][j] = abs(p[i].x - q[i].x) + abs(p[i].y - q[i].y);
        }
        VI matches = mincost_match(cost);
        vector<VPI> ans;
        VVI a(n, VI(m, -1));
        bool ok = true;
        repn(i, k) {
            VPI path = find_path(a, p[i], q[matches[i]]);
            if(path.empty()) {
                ok = false;
                break;
            }
            ans.pb(path);
            for(const auto& u : path) a[u.x][u.y] = i;
        }
        if(ok) return ans;
    }
}

void expand(int n, int m, VVI& a) {
    queue<PII> que;
    repn(i, n) repn(j, m) if(a[i][j] >= 0) que.push(mp(i, j));
    while(!que.empty()) {
        const PII u = que.front();
        que.pop();
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {1, 0, -1, 0};
        const VI directions = rand_perm(4);
        for(int i : directions) {
            const PII v = {u.x + dx[i], u.y + dy[i]};
            if(v.x < 0 || v.x >= n || v.y < 0 || v.y >= m) continue;
            if(a[v.x][v.y] < 0) {
                a[v.x][v.y] = a[u.x][u.y];
                que.push(v);
            }
        }
    }
}

void answer(const VVI& a) {
    for(const auto& row : a) {
        string s;
        for(int i : row) {
            assert(i >= 0 && i < 20);
            s += char('a' + i);
        }
        cout << s << endl;
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    VPI p(k), q(k);
    repn(i, k) cin >> p[i].x >> p[i].y;
    repn(i, k) cin >> q[i].x >> q[i].y;

    vector<VPI> matches = find_matches(n, m, k, p, q);
    assert(sz(matches) == k);

    VVI a(n, VI(m, -1));
    repn(i, k) {
        for(const auto u : matches[i]) a[u.x][u.y] = i;
    }
    expand(n, m, a);

    answer(a);

    return 0;
}
