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

template <class T> struct CostNet {
    const int s, t;

    explicit CostNet(int n) : s(n), t(n + 1), n_(n + 2), es_(n_) {}

    void* add_edge(int x, int y, T w, T c) { return add_(x, y, w, c); }

    // (flow, cost)
    pair<T, T> compute() { return compute_(); }
    T flow(void* e) { return flow_(e); }

private:  //{{{
    struct Edge {
        int y;
        T w, c;
        Edge* oppo;
    };
    const int n_;
    T w0_ = 0, c0_ = 0;
    vector<vector<unique_ptr<Edge>>> es_;

    void* add_(int x, int y, T w, T c) {
        Edge *e1, *e2;
        es_[x].emplace_back(e1 = new Edge{y, w, c, nullptr});
        es_[y].emplace_back(e2 = new Edge{x, 0, -c, nullptr});
        e1->oppo = e2, e2->oppo = e1;
        return static_cast<void*>(e1);
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
    // }}}
};

int main() {
    while(1) {
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        if(n == 0) break;
        CostNet<int> net(n + m);
        vector<PII> intervals(n);
        vector<void*> edges(n);
        int ans = 0;
        repn(i, n) {
            int l, r, c;
            scanf("%d%d%d", &l, &r, &c);
            --l;
            intervals[i] = mp(l, r);
            int in = n + l, out = (r == m ? net.t : n + r);
            ans += c;
            edges[i] = net.add_edge(in, i, 1, -c);
            net.add_edge(i, out, 1, 0);
        }
        net.add_edge(net.s, n, p, 0);
        repn(i, m - 1) net.add_edge(n + i, n + i + 1, 1 << 30, 0);
        net.add_edge(n + m - 1, net.t, 1 << 30, 0);

        ans += net.compute().se;
        set<PII> events;
        repn(i, n) if(net.flow(edges[i])) {
            events.insert(mp(intervals[i].fi, i));
        }
        vector<VI> assignment(p);
        VI left(p);
        iota(all(left), 0);
        while(!events.empty()) {
            const auto e = *events.begin();
            events.erase(events.begin());
            if(e.se >= 0) {
                int worker = left.back();
                left.pop_back();
                assignment[worker].pb(e.se);
                events.insert(mp(intervals[e.se].se, -worker - 1));
            } else {
                int worker = -e.se - 1;
                left.pb(worker);
            }
        }
        printf("%d\n", ans);
        repn(i, p) {
            repn(j, sz(assignment[i])) {
                if(j > 0) printf(" ");
                printf("%d", assignment[i][j]+1);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
