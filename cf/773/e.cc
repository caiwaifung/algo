// 12:06 - eta 12:36
//       - 13:07 - wa sample
// 13:48 - 14:03 - wa
//       - 14:25 - ac
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

const int N = 500050;
const int kInf = 1 << 29;

struct Node {
    int l, r, ran, v, s, d;
    int buf;
    int size, ss, zero;
    PII pos, neg;

    void init_null() {
        l = r = 0, ran = -1;
        size = 0, ss = 0;
        zero = kInf, pos = {kInf, kInf}, neg = {-kInf, kInf};
    }

    void init(int v0, int s0, int d0) {
        l = r = 0, ran = rand(), v = v0, s = s0, d = d0;
        buf = 0;
    }
} tr[N];

int lsize(int x) { return tr[tr[x].l].size; }

PII add_snd(PII a, int b) { return mp(a.fi, a.se + b); }
PLL cpos(PII a, PII b) { return min(a, b); }
PLL cpos(PII a, PII b, PII c) { return cpos(a, cpos(b, c)); }
PLL cneg(PII a, PII b) {
    return (a.fi > b.fi || (a.fi == b.fi && a.se < b.se)) ? a : b;
}
PLL cneg(PII a, PII b, PII c) { return cneg(a, cneg(b, c)); }

void update(int x) {
    const Node& pl = tr[tr[x].l];
    const Node& pr = tr[tr[x].r];
    tr[x].size = pl.size + pr.size + 1;
    tr[x].ss = pl.ss + pr.ss + tr[x].s;
    tr[x].zero =
        min(min(pl.zero, pr.zero + pl.size + 1), tr[x].d == 0 ? pl.size : kInf);
    tr[x].pos = cpos(pl.pos, add_snd(pr.pos, pl.size + 1),
                     tr[x].d > 0 ? mp(tr[x].d, pl.size) : mp(kInf, kInf));
    tr[x].neg = cneg(pl.neg, add_snd(pr.neg, pl.size + 1),
                     tr[x].d < 0 ? mp(tr[x].d, pl.size) : mp(-kInf, kInf));
}

void push(int x, int val) {
    if(x == 0) return;
    tr[x].buf += val;
    tr[x].d += val;
    tr[x].pos.fi += val;
    tr[x].neg.fi += val;
}

void propagrate(int x) {
    if(tr[x].buf) {
        push(tr[x].l, tr[x].buf);
        push(tr[x].r, tr[x].buf);
        tr[x].buf = 0;
    }
}

int lrotate(int x) {
    assert(tr[x].buf == 0);
    int y = tr[x].l;
    tr[x].l = tr[y].r, tr[y].r = x;
    update(x);
    return y;
}

int rrotate(int x) {
    assert(tr[x].buf == 0);
    int y = tr[x].r;
    propagrate(y);
    tr[x].r = tr[y].l, tr[y].l = x;
    update(x);
    return y;
}

int insert(int x, int ind, int y) {
    if(x == 0) {
        assert(ind == 0);
        update(y);
        return y;
    }
    propagrate(x);
    if(ind <= lsize(x)) {
        tr[x].l = insert(tr[x].l, ind, y);
        if(tr[tr[x].l].ran > tr[x].ran) x = lrotate(x);
    } else {
        tr[x].r = insert(tr[x].r, ind - lsize(x) - 1, y);
        if(tr[tr[x].r].ran > tr[x].ran) x = rrotate(x);
    }
    update(x);
    return x;
}

void update_sign(int x, int ind) {
    assert(x > 0);
    propagrate(x);
    if(ind == lsize(x)) {
        tr[x].s = (tr[x].d == 0 ? 0 : (tr[x].d < 0 ? -1 : 1));
    } else {
        if(ind < lsize(x)) {
            update_sign(tr[x].l, ind);
        } else {
            update_sign(tr[x].r, ind - lsize(x) - 1);
        }
    }
    update(x);
}

void add(int x, int l, int r, int val) {
    if(l <= 0 && tr[x].size <= r) {
        push(x, val);
        return;
    }
    propagrate(x);
    int m = lsize(x);
    if(l < m) add(tr[x].l, l, r, val);
    if(l <= m && m < r) tr[x].d += val;
    if(m + 1 < r) add(tr[x].r, l - m - 1, r - m - 1, val);
    update(x);
}

int count_lt(int x, int val) {
    if(x == 0) return 0;
    propagrate(x);
    if(val <= tr[x].v) {
        return count_lt(tr[x].l, val);
    } else {
        return count_lt(tr[x].r, val) + lsize(x) + 1;
    }
}

int sum_sign(int x, int ind) {
    if(x == 0) {
        assert(ind == 0);
        return 0;
    }
    propagrate(x);
    if(ind <= lsize(x)) {
        return sum_sign(tr[x].l, ind);
    } else {
        return sum_sign(tr[x].r, ind - lsize(x) - 1) + tr[tr[x].l].ss + tr[x].s;
    }
}

int get_zero(int x, int ind) {
    if(x == 0) return kInf;
    propagrate(x);
    if(ind <= lsize(x)) {
        return min(get_zero(tr[x].l, ind),
                   min(tr[x].d == 0 ? lsize(x) : kInf,
                       tr[tr[x].r].zero + lsize(x) + 1));
    } else {
        return get_zero(tr[x].r, ind - lsize(x) - 1) + lsize(x) + 1;
    }
}

PII get_pos(int x, int ind) {
    if(x == 0) return {kInf, kInf};
    propagrate(x);
    if(ind <= lsize(x)) {
        return cpos(get_pos(tr[x].l, ind),
                    add_snd(tr[tr[x].r].pos, lsize(x) + 1),
                    tr[x].d > 0 ? mp(tr[x].d, lsize(x)) : mp(kInf, kInf));
    } else {
        return add_snd(get_pos(tr[x].r, ind - lsize(x) - 1), lsize(x) + 1);
    }
}

PII get_neg(int x, int ind) {
    if(x == 0) return {-kInf, kInf};
    propagrate(x);
    if(ind <= lsize(x)) {
        return cneg(get_neg(tr[x].l, ind),
                    add_snd(tr[tr[x].r].neg, lsize(x) + 1),
                    tr[x].d < 0 ? mp(tr[x].d, lsize(x)) : mp(-kInf, kInf));
    } else {
        return add_snd(get_neg(tr[x].r, ind - lsize(x) - 1), lsize(x) + 1);
    }
}

VI vio(VI xs) {
    VI a, ans;
    for(int x : xs) {
        a.pb(x);
        sort(all(a));
        int cur = 0;
        for(int y : a) {
            if(y != cur) cur += (cur < y ? 1 : -1);
        }
        ans.pb(cur);
    }
    return ans;
}

void print(int x) {
    if(x == 0) return;
    print(tr[x].l);
    printf("  entry v=%d s=%d d=%d zero=%d\n", tr[x].v, tr[x].s, tr[x].d,
           tr[x].zero);
    print(tr[x].r);
}

VI solve(VI vals) {
    int node_count = 0;
    fillchar(tr, 0);
    tr[0].init_null();
    int root = 0;
    VI ans;
    for(int val : vals) {
        int i = count_lt(root, val);
        int margin = val - sum_sign(root, i);
        int sign = (margin == 0 ? 0 : (margin < 0 ? -1 : 1));
        // cout << val << ": " << i << " " << margin << " " << sign << endl;
        int x = ++node_count;
        tr[x].init(val, sign, margin);
        if(sign != 0) {
            int j = get_zero(root, i);
            // cout << "  j=" << j << endl;
            if(sign > 0) {
                PII p = get_pos(root, i);
                if(p.fi == 1) setmin(j, p.se);
            } else {
                PII p = get_neg(root, i);
                if(p.fi == -1) setmin(j, p.se);
            }
            // cout << "  j=" << j << endl;
            if(j < tr[root].size) {
                add(root, i, j + 1, -sign);
                update_sign(root, j);
            } else {
                add(root, i, tr[root].size, -sign);
            }
        }
        root = insert(root, i, x);
        // print(root);
        ans.pb(tr[root].ss);
    }
    return ans;
}

void check() {
    while(0) {
        srand(1234);
        VI a = {2, 2, 2, -2};
        cout << solve(a) << endl;
        cout << vio(a) << endl;
        exit(0);
    }
    int x = 0;
    while(1) {
        srand(x = x * 10101 ^ 3131214);
        VI a;
        repn(i, 40) a.pb(rand() % 90 - 40);
        srand(1234);
        VI ans = solve(a);
        VI std = vio(a);
        cout << a << " " << ans << endl;
        if(ans != std) {
            cout << "  >>> std=" << std << endl;
            while(1)
                ;
        }
    }
}

int main() {
    //check();
    for(int x : solve(read_vi())) printf("%d\n", x);
}
