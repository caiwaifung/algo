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

const int N = 200000;

struct BaseBuilder {
    int head[31];
    BaseBuilder() { fillchar(head, 0); }
    void add(int x) {
        irep(i, 30, 0) if(x & (1 << i)) {
            if(head[i] == 0) {
                head[i] = x;
                break;
            } else {
                x ^= head[i];
            }
        }
    }
    VI build() const {
        VI r;
        irep(i, 30, 0) if(head[i]) r.pb(head[i]);
        return r;
    }
};

struct Value {
    int le;
    VI bases;

    void operator^=(int x) { le ^= x; }
    Value operator+(const Value& v) const {
        BaseBuilder builder;
        for(int x : bases) builder.add(x);
        for(int x : v.bases) builder.add(x);
        builder.add(le ^ v.le);
        Value r;
        r.le = le;
        r.bases = builder.build();
        return r;
    }
};

Value tr[N];
int buf[N];

void release(int x) {
    if(buf[x] != 0) {
        tr[x * 2 + 1] ^= buf[x];
        buf[x * 2 + 1] ^= buf[x];
        tr[x * 2 + 2] ^= buf[x];
        buf[x * 2 + 2] ^= buf[x];
        buf[x] = 0;
    }
}

void modify(int x, int l, int r, int st, int en, int val) {
    if(st <= l && r <= en) {
        tr[x] ^= val;
        buf[x] ^= val;
        return;
    }
    release(x);
    const int m = (l + r) / 2;
    if(st < m) modify(x * 2 + 1, l, m, st, en, val);
    if(m < en) modify(x * 2 + 2, m, r, st, en, val);
    tr[x] = tr[x * 2 + 1] + tr[x * 2 + 2];
}

Value get(int x, int l, int r, int st, int en) {
    if(st <= l && r <= en) {
        return tr[x];
    }
    release(x);
    const int m = (l + r) / 2;
#define L get(x * 2 + 1, l, m, st, en)
#define R get(x * 2 + 2, m, r, st, en)
    if(st < m && m < en) {
        return L + R;
    } else if(st < m) {
        return L;
    } else {
        return R;
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    repn(i, n) {
        int x;
        scanf("%d", &x);
        modify(0, 0, n, i, i + 1, x);
    }
    while(q--) {
        int type, l, r;
        scanf("%d%d%d", &type, &l, &r);
        --l;
        if(type == 1) {
            int x;
            scanf("%d", &x);
            modify(0, 0, n, l, r, x);
        } else {
            Value ret = get(0, 0, n, l, r);
            //cout << ret.le << " " << ret.bases << endl;
            BaseBuilder builder;
            for(int x : ret.bases) builder.add(x);
            builder.add(ret.le);
            int ans = 1 << sz(builder.build());
            printf("%d\n", ans);
        }
    }
    return 0;
}
