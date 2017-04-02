// 14:49 - 15:23
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

struct Barrier {
    int u, l, r, s;
    void read() {
        scanf("%d%d%d%d", &u, &l, &r, &s);
        --l;
    }
    bool operator<(const Barrier& b) const { return u < b.u; }
};

struct Query {
    int x, y, *ans;
    bool* label = nullptr;
};

class DS {
    const int n;
    vector<vector<Query>> tr;

    void add(int x, int l, int r, int ind, Query q) {
        tr[x].pb(q);
        if(l + 1 == r) {
            return;
        }
        const int m = (l + r) / 2;
        if(ind < m) {
            add(x * 2 + 1, l, m, ind, q);
        } else {
            add(x * 2 + 2, m, r, ind, q);
        }
    }

    void cleanup(int x) {
        while(!tr[x].empty() && !*(tr[x].back().label)) {
            tr[x].pop_back();
        }
    }

    bool pop(int x, int l, int r, int st, int en, int maxy, Query* q) {
        cleanup(x);
        if(tr[x].empty()) {
            return false;
        }
        if(st <= l && r <= en) {
            if(tr[x].back().y <= maxy) {
                *q = tr[x].back();
                tr[x].pop_back();
                *(q->label) = false;
                return true;
            }
            return false;
        }
        const int m = (l + r) / 2;
        if(st < m) {
            if(pop(x * 2 + 1, l, m, st, en, maxy, q)) return true;
        }
        if(m < en) {
            if(pop(x * 2 + 2, m, r, st, en, maxy, q)) return true;
        }
        return false;
    }

public:
    DS(int n) : n(n), tr(n * 4) {}

    void push_query(Query q) {
        q.label = new bool;
        *(q.label) = true;
        add(0, 0, n, q.x, q);
    }
    bool pop_query(int l, int r, int maxy, Query* q) {
        return pop(0, 0, n, l, r, maxy, q);
    }
};

int main() {
    int h, w, n;
    scanf("%d%d%d", &h, &w, &n);
    vector<Barrier> a(n);
    repn(i, n) a[i].read();
    sort(all(a));

    VI start(w, -1), downl(n, -1), downr(n, -1);
    DS d(w);
    repn(i, w) d.push_query(Query{i, h + 1, &start[i]});
    irepn(i, n) {
        while(1) {
            Query q;
            if(!d.pop_query(a[i].l, a[i].r, a[i].u + a[i].s, &q)) {
                break;
            }
            *(q.ans) = i;
        }
        const int l = a[i].l - 1, r = a[i].r;
        d.push_query(Query{l >= 0 ? l : r, a[i].u, &downl[i]});
        d.push_query(Query{r < w ? r : l, a[i].u, &downr[i]});
    }

    const LL MOD = LL(1e9) + 7;
    VL val(n);
    repn(i, n) {
        LL vl = 1, vr = 1;
        if(downl[i] >= 0) vl = val[downl[i]];
        if(downr[i] >= 0) vr = val[downr[i]];
        val[i] = (vl + vr) % MOD;
    }
    LL ans = 0;
    repn(i, w) {
        LL tmp = 1;
        if(start[i] >= 0) tmp = val[start[i]];
        (ans += tmp) %= MOD;
    }
    printf("%d\n", int(ans));

    return 0;
}
