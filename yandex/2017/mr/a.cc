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

template <class T> struct CostNet {  // {{{
    const int s, t;

    explicit CostNet(int n) : s(n), t(n + 1), n_(n + 2), es_(n_) {}

    void* add_edge(int x, int y, T w, T c) { return add_(x, y, w, c); }

    // (flow, cost)
    pair<T, T> compute() { return compute_(); }
    T flow(void* e) { return flow_(e); }

private:
    struct Edge {
        int y;
        T w, c;
        Edge* oppo;
    };
    const int n_;
    T w0_ = 0, c0_ = 0;
    vector<vector<unique_ptr<Edge>>> es_;

    void* add_(int x, int y, T w, T c) {
        if(c >= 0) {
            Edge *e1, *e2;
            es_[x].emplace_back(e1 = new Edge{y, w, c, nullptr});
            es_[y].emplace_back(e2 = new Edge{x, 0, -c, nullptr});
            e1->oppo = e2, e2->oppo = e1;
            return static_cast<void*>(e1);
        } else {
            // ???
            w0_ += w;
            c0_ += w * (-c);
            add_(s, y, w, 0);
            add_(y, x, w, -c);
            add_(x, t, w, 0);
            return nullptr;
        }
    }

    pair<T, T> compute_() {
        pair<T, T> ans = {-w0_, -c0_};
        while(1) {
            vector<T> dis(n_, numeric_limits<T>::max());
            vector<T> flow(n_);
            vector<Edge*> pre(n_);
            dis[s] = 0;
            flow[s] = numeric_limits<T>::max();

            vector<bool> inside(n_, false);
            queue<int> que;
            inside[s] = true;
            que.push(s);
            while(!que.empty()) {
                const int x = que.front();
                que.pop();
                for(const auto& e : es_[x]) {
                    if(e->w > 0 && setmin(dis[e->y], dis[x] + e->c)) {
                        pre[e->y] = e.get();
                        flow[e->y] = min(flow[x], e->w);
                        if(!inside[e->y]) {
                            inside[e->y] = true;
                            que.push(e->y);
                        }
                    }
                }
                inside[x] = false;
            }
            if(dis[t] == numeric_limits<T>::max()) {
                return ans;
            }

            ans.fi += flow[t], ans.se += flow[t] * dis[t];
            for(int x = t; x != s; x = pre[x]->oppo->y) {
                pre[x]->w -= flow[t];
                pre[x]->oppo->w += flow[t];
            }
        }
        return ans;
    }

    T flow_(void* e) { return static_cast<Edge*>(e)->oppo->w; }
};
// }}}

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

//==============================================================================
// UTIL ENDS
//==============================================================================

vector<VPI> find_matches(int n, int m, int k, VPI p, VPI q) {
    CostNet<int> net(n * m * 2);
    const auto id = [&](int i, int j, int ind) {
        return (i * m + j) * 2 + ind;
    };
    for(const auto& u : p) net.add_edge(net.s, id(u.x, u.y, 0), 1, 0);
    for(const auto& u : q) net.add_edge(id(u.x, u.y, 1), net.t, 1, 0);
    static const int dx[4] = {0, 1, 0, -1};
    static const int dy[4] = {1, 0, -1, 0};
    static void* es[99][99][9];
    repn(i, n) repn(j, m) { net.add_edge(id(i, j, 0), id(i, j, 1), 1, 0); }
    repn(i, n) repn(j, m) {
        repn(dir, 4) {
            int i2 = i + dx[dir], j2 = j + dy[dir];
            if(i2 >= 0 && i2 < n && j2 >= 0 && j2 < m) {
                es[i][j][dir] = net.add_edge(id(i, j, 1), id(i2, j2, 0), 1, 1);
            }
        }
    }
    auto r = net.compute();
    //cout << r << endl;
    assert(r.fi == k);

    vector<vector<PII>> f(n, VPI(m, {-1, -1}));
    const function<PII(PII)> get = [&](PII u) {
        return f[u.x][u.y].x < 0 ? u : f[u.x][u.y] = get(f[u.x][u.y]);
    };
    repn(i, n) repn(j, m) repn(dir, 4) {
        int i2 = i + dx[dir], j2 = j + dy[dir];
        if(i2 >= 0 && i2 < n && j2 >= 0 && j2 < m) {
            if(net.flow(es[i][j][dir]) > 0) {
                PII u = get({i, j});
                PII v = get({i2, j2});
                if(u != v) f[u.x][u.y] = v;
            }
        }
    }
    vector<VPI> ans(k);
    repn(cur, k) {
        repn(i, n) repn(j, m) {
            if(get({i, j}) == get(p[cur])) ans[cur].pb({i, j});
        }
    }
    return ans;
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
