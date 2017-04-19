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

const int INF = 1 << 30;

class Tree {
public:
    Tree(int n) : n(n), tr(n * 4, {INF, -INF}) {}

    void set(int i, int val) { set(0, 0, n, i, {val, val}); }
    void unset(int i) { set(0, 0, n, i, {INF, -INF}); }
    int get_min(int l, int r) { return get(0, 0, n, l, r).fi; }
    int get_max(int l, int r) { return get(0, 0, n, l, r).se; }

private:
    PII merge(PII a, PII b) { return mp(min(a.fi, b.fi), max(a.se, b.se)); }

    void set(int x, int l, int r, int i, PII val) {
        if(l + 1 == r) {
            tr[x] = val;
            return;
        }
        const int m = (l + r) / 2;
        if(i < m) {
            set(x * 2 + 1, l, m, i, val);
        } else {
            set(x * 2 + 2, m, r, i, val);
        }
        tr[x] = merge(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    PII get(int x, int l, int r, int st, int en) {
        if(st >= en) return {INF, -INF};
        if(st <= l && r <= en) {
            return tr[x];
        }
        const int m = (l + r) / 2;
        PII ans = {INF, -INF};
        if(st < m) ans = merge(ans, get(x * 2 + 1, l, m, st, en));
        if(m < en) ans = merge(ans, get(x * 2 + 2, m, r, st, en));
        return ans;
    }

    const int n;
    VPI tr;
};

int main() {
    int n;
    scanf("%d", &n);
    VI l(n), r(n), fa(n, -1), val(n);
    repn(i, n) {
        scanf("%d%d%d", &val[i], &l[i], &r[i]);
        if(l[i] > 0) --l[i], fa[l[i]] = i;
        if(r[i] > 0) --r[i], fa[r[i]] = i;
    }
    int root = int(find(all(fa), -1) - fa.begin());
    // printf("root=%d\n",root);
    VI pos(n), ind;
    const function<void(int)> prepare = [&](int x) {
        if(l[x] >= 0) prepare(l[x]);
        pos[x] = sz(ind), ind.pb(x);
        if(r[x] >= 0) prepare(r[x]);
    };
    prepare(root);

    Tree tr(n);
    unordered_set<int> oks;
    const function<void(int)> solve = [&](int x) {
        if(tr.get_max(0, pos[x]) <= val[x] &&
           tr.get_min(pos[x] + 1, n) >= val[x]) {
            oks.insert(val[x]);
        }
        tr.set(pos[x], val[x]);
        if(l[x] >= 0) solve(l[x]);
        if(r[x] >= 0) solve(r[x]);
        tr.unset(pos[x]);
    };
    solve(root);

    int ans = 0;
    for(int v : val) {
        if(oks.count(v) == 0) ans++;
    }
    printf("%d\n", ans);

    return 0;
}
