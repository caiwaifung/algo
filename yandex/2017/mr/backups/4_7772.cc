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
template <class T> class Net {  // {{{
public:
    Net(int n0, int s, int t)
        : n(n0 + 2),
          original_s(s),
          original_t(t),
          super_s(n),
          super_t(n + 1),
          es(n),
          dis(n) {}

    void* add(int x, int y, T w) {
        assert(x >= 0 && x < n && y >= 0 && y < n);
        Edge *e1, *e2;
        es[x].emplace_back(e1 = new Edge{y, w, nullptr});
        es[y].emplace_back(e2 = new Edge{x, 0, nullptr});
        e1->oppo = e2, e2->oppo = e1;
        return e1;
    }
    void* add(int x, int y, pair<T, T> w) {
        assert(w.fi <= w.se);
        if(w.fi > 0) {
            add(super_s, y, w.fi);
            add(x, super_t, w.fi);
            super_total += w.fi;
        }
        return add(x, y, w.se - w.fi);
    }

    // returns -1 if no solution.
    T compute() {
        if(super_total > 0) {
            add(original_t, original_s, numeric_limits<T>::max());
            LL r = 0, tmp;
            while((tmp = augment(super_s, super_t)) > 0) {
                r += tmp;
            }
            if(r != super_total) return -1;
        }
        T ans = 0, tmp;
        while((tmp = augment(original_s, original_t)) > 0) {
            ans += tmp;
        }
        return ans;
    }

    T flow(void* e) const { return static_cast<Edge*>(e)->oppo->w; }
    bool on_cut(void* e) const {
        return dis[static_cast<Edge*>(e)->oppo->y] > 0 &&
               dis[static_cast<Edge*>(e)->y] == 0;
    }
    VI left() const {
        VI r;
        repn(i, n) if(dis[i] > 0) r.pb(i);
        return r;
    }

private:
    struct Edge {
        int y;
        T w;
        Edge* oppo;
    };

    T augment(int s, int t) {
        dis.resize(n);
        fill(all(dis), 0);
        dis[s] = 1;
        queue<int> que;
        que.push(s);
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            for(const auto& e : es[x]) {
                if(e->w > 0 && dis[e->y] == 0) {
                    dis[e->y] = dis[x] + 1;
                    que.push(e->y);
                }
            }
        }
        if(dis[t] == 0) return 0;

        vector<size_t> ce(n);
        const function<T(int, T)> dfs = [&](int x, T rest) {
            if(x == t) return rest;
            T r = 0;
            for(size_t& i = ce[x]; i < es[x].size(); ++i) {
                const auto& e = es[x][i];
                if(e->w > 0 && dis[e->y] > dis[x]) {
                    T cur = dfs(e->y, min(e->w, rest));
                    e->w -= cur, e->oppo->w += cur;
                    r += cur, rest -= cur;
                    if(rest == 0) break;
                }
            }
            return r;
        };
        return dfs(s, numeric_limits<T>::max());
    }

    const int n, original_s, original_t, super_s, super_t;
    T super_total = 0;
    vector<vector<unique_ptr<Edge>>> es;
    VI dis;
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

template <class T> void rand_shuffle(vector<T>* a) {
    repn(i, sz(*a)) swap((*a)[i], (*a)[rand_uniform(i + 1)]);
}

template <class T> vector<T> rand_shuffled(const vector<T>& a) {
    auto b = a;
    rand_shuffle(&b);
    return b;
}
// }}}

//==============================================================================
// UTIL ENDS
//==============================================================================

const int N = 50;

int n, m, k;
VPI ps, qs;
int occupied[N][N];
VPI neighbors[N][N];
VVI assignment;

void init() {
    cin >> n >> m >> k;
    ps.resize(k), qs.resize(k);
    repn(i, k) cin >> ps[i].x >> ps[i].y;
    repn(i, k) cin >> qs[i].x >> qs[i].y;

    fillchar(occupied, -1);
    for(const auto& p : ps) occupied[p.x][p.y] = 1;
    for(const auto& q : qs) occupied[q.x][q.y] = 2;

    repn(x, n) repn(y, m) {
        static const int dx[4] = {0, 1, 0, -1};
        static const int dy[4] = {1, 0, -1, 0};
        repn(i, 4) {
            int x2 = x + dx[i], y2 = y + dy[i];
            if(x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
                neighbors[x][y].pb({x2, y2});
            }
        }
    }
    assignment = VVI(n, VI(m, -1));
}

double score(int nc, int ne) {
    assert(nc > 0 && ne > 0);
    return double(nc) / double(ne) / double(ne);
}

VPI find_path(const VVI& a, PII start, PII end) {
    if(a[start.x][start.y] >= 0) return {};
    if(start == end) return {start};

    vector<VPI> pre(n, VPI(m, {-1, -1}));
    queue<PII> que;
    pre[start.x][start.y] = start, que.push(start);
    while(!que.empty()) {
        const PII u = que.front();
        que.pop();
        for(const auto& v : rand_shuffled(neighbors[u.x][u.y])) {
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

vector<VPI> find_matches() {
    CostNet<int> net(n * m * 2);
    const auto id = [&](int i, int j, int ind) {
        return (i * m + j) * 2 + ind;
    };
    for(const auto& u : ps) net.add_edge(net.s, id(u.x, u.y, 0), 1, 0);
    for(const auto& u : qs) net.add_edge(id(u.x, u.y, 1), net.t, 1, 0);
    static void* es[99][99][9];
    repn(i, n) repn(j, m) { net.add_edge(id(i, j, 0), id(i, j, 1), 1, 0); }
    repn(i, n) repn(j, m) {
        repn(d, sz(neighbors[i][j])) {
            const auto& p = neighbors[i][j][d];
            es[i][j][d] = net.add_edge(id(i, j, 1), id(p.x, p.y, 0), 1, 1);
        }
    }
    auto r = net.compute();
    assert(r.fi == k);

    vector<vector<PII>> f(n, VPI(m, {-1, -1}));
    const function<PII(PII)> get = [&](PII u) {
        return f[u.x][u.y].x < 0 ? u : f[u.x][u.y] = get(f[u.x][u.y]);
    };
    repn(i, n) repn(j, m) {
        repn(d, sz(neighbors[i][j])) {
            if(net.flow(es[i][j][d]) > 0) {
                PII u = get({i, j});
                PII v = get(neighbors[i][j][d]);
                if(u != v) f[u.x][u.y] = v;
            }
        }
    }
    vector<VPI> ans(k);
    repn(cur, k) {
        repn(i, n) repn(j, m) {
            if(get({i, j}) == get(ps[cur])) ans[cur].pb({i, j});
        }
    }
    return ans;
}

void expand() {
    queue<PII> que;
    repn(i, n) repn(j, m) {
        if(assignment[i][j] >= 0) que.push(mp(i, j));
    }
    while(!que.empty()) {
        const PII u = que.front();
        que.pop();
        for(const auto& v : rand_shuffled(neighbors[u.x][u.y])) {
            if(assignment[v.x][v.y] < 0) {
                assignment[v.x][v.y] = assignment[u.x][u.y];
                que.push(v);
            }
        }
    }
}

void adjust_pair(int c1, int c2) {
    VPI paths[2];
    repn(cur, 2) {
        VVI b = assignment;
        PII start, end;
        repn(i, n) repn(j, m) if(b[i][j] == (cur == 0 ? c1 : c2)) {
            b[i][j] = -1;
            if(occupied[i][j] == 1) start = mp(i, j);
            if(occupied[i][j] == 2) end = mp(i, j);
        }
        paths[cur] = find_path(b, start, end);
        assert(!paths[cur].empty());
    }
    VVI id(n, VI(m, -1));
    VPI id2p;
    repn(i, n) repn(j, m) {
        if(assignment[i][j] == c1 || assignment[i][j] == c2) {
            assignment[i][j] = c2;
            id[i][j] = sz(id2p);
            id2p.pb({i, j});
        }
    }
    int s = sz(id2p), t = s + 1;
    Net<int> net(sz(id2p) + 2, s, t);
    for(PII u : paths[0]) net.add(s, id[u.x][u.y], 1 << 30);
    for(PII u : paths[1]) net.add(id[u.x][u.y], t, 1 << 30);
    repn(i, n) repn(j, m) if(id[i][j] >= 0) {
        for(const auto& u : neighbors[i][j]) {
            if(id[u.x][u.y] >= 0) {
                net.add(id[i][j], id[u.x][u.y], 1);
            }
        }
    }
    net.compute();
    VI left = net.left();
    for(int i : left) {
        if(i != s) assignment[id2p[i].x][id2p[i].y] = c1;
    }
}

void adjust() {
    int did = 0;
    repn(_, 200) {
        VPI pairs;
        repn(i, k) replr(j, i + 1, k) pairs.pb(mp(i, j));
        rand_shuffle(&pairs);
        for(const auto& pair : pairs) {
            vector<vector<bool>> adj(k, vector<bool>(k, false));
            repn(i, n) repn(j, m) for(PII u : neighbors[i][j]) {
                int c1 = assignment[i][j];
                int c2 = assignment[u.x][u.y];
                adj[c1][c2] = true;
            }
            if(!adj[pair.fi][pair.se]) continue;
            adjust_pair(pair.fi, pair.se);
            ++did;
            if(did > 100) return;
        }
    }
}

void adjust2() {
    VI cells(k), edges(k);
    repn(x, n) repn(y, m) {
        int e = 4 - sz(neighbors[x][y]);
        for(const auto& u : neighbors[x][y]) {
            if(assignment[x][y] != assignment[u.x][u.y]) {
                ++e;
            }
        }
        cells[assignment[x][y]]++;
        edges[assignment[x][y]] += e;
    }
    repn(i, k) assert(cells[i] > 0);
    while(1) {
        bool found = false;
        VPI allpos;
        repn(x, n) repn(y, m) allpos.pb({x, y});
        rand_shuffle(&allpos);
        for(const auto& u : allpos) {
            if(occupied[u.x][u.y] >= 0) continue;
            unordered_set<int> colors;
            for(const auto& v : neighbors[u.x][u.y]) {
                colors.insert(assignment[v.x][v.y]);
            }
            colors.erase(assignment[u.x][u.y]);
            for(int c2 : colors) {
                int c1 = assignment[u.x][u.y];
                int e1 = 4, e2 = 4;
                for(const auto& v : neighbors[u.x][u.y]) {
                    int c = assignment[v.x][v.y];
                    if(c == c1) e1 -= 2;
                    if(c == c2) e2 -= 2;
                }
                double old_score =
                    score(cells[c1], edges[c1]) + score(cells[c2], edges[c2]);
                double new_score = score(cells[c1] - 1, edges[c1] - e1) +
                                   score(cells[c2] + 1, edges[c2] + e2);
                if(old_score < new_score) {
                    assignment[u.x][u.y] = c2;
                    cells[c1]--, edges[c1] -= e1;
                    cells[c2]++, edges[c2] += e2;
                    found = true;
                }
            }
        }
        if(!found) break;
    }
}

void answer() {
    for(const auto& row : assignment) {
        string s;
        for(int i : row) {
            assert(i >= 0 && i < 20);
            s += char('a' + i);
        }
        cout << s << endl;
    }
}

int main() {
    init();

    vector<VPI> matches = find_matches();
    assert(sz(matches) == k);
    repn(i, k) {
        for(const auto u : matches[i]) {
            assignment[u.x][u.y] = i;
            if(occupied[u.x][u.y] < 0) occupied[u.x][u.y] = 3;
        }
    }
    expand();
    adjust();
    adjust2();
    answer();

    return 0;
}
