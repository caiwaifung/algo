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

struct Point {
    LL x, y;
    Point() : x(0), y(0) {}
    Point(LL _x, LL _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point& p) const { return !(*this == p); }
    bool operator<(const Point& p) const { return x < p.x; }
    void read() { scanf("%lld%lld", &x, &y); }
    friend LL mult(Point p0, Point p1, Point p2) {
        return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
    }
    friend LL dot(Point p0, Point p1, Point p2) {
        return (p1.x - p0.x) * (p2.x - p0.x) + (p2.y - p0.y) * (p1.y - p0.y);
    }
    LL sqabs() const { return x * x + y * y; }
};

int rect_cover(vector<Point> a, LL r) {
    sort(all(a));
    int ans = 0;
    static int len, ys[555];
    const auto go = [&]() {
        int j = 0;
        sort(ys, ys + len);
        repn(i, len) {
            while(j < len && ys[j] <= ys[i] + r) ++j;
            setmax(ans, j - i);
        }
    };
    int j = 0;
    repn(i, sz(a)) {
        while(j < sz(a) && a[j].x <= a[i].x + r) ++j;
        len = 0;
        replr(k, i, j) ys[len++] = int(a[k].y);
        go();
    }
    return ans;
}

LD get_cos(Point p0, Point p1, Point p2) {
    LD a2 = (p0 - p1).sqabs(), b2 = (p0 - p2).sqabs(), c2 = (p1 - p2).sqabs();
    LD a = sqrtl(a2), b = sqrtl(b2);
    LD ans = (a2 + b2 - c2) / 2 / a / b;
    return ans;
}

void solve(int cs) {
    int n;
    LL r;
    scanf("%d%lld", &n, &r);
    vector<Point> a(n);
    repn(i, n) a[i].read();

    int ans = 0;
    const auto go = [&](VI is) {
        vector<bool> bi(n, false);
        for(int i : is) bi[i] = true;
        vector<Point> u, v;
        repn(i, n)(bi[i] ? u : v).pb(a[i]);
        setmax(ans, rect_cover(u, r) + rect_cover(v, r));
    };

    repn(i, n) {
        VI js;
        repn(j, n) if(a[j] == a[i]) js.pb(j);
        go(js);
    }
    repn(p, n) replr(q, p + 1, n) if(a[p] != a[q]) {
        set<int> js;
        vector<pair<LD, PII>> ls;
        repn(k, n) {
            if(mult(a[p], a[q], a[k]) == 0) {
                if(dot(a[k], a[p], a[q]) <= 0) {
                    js.insert(k);
                }
            } else {
                LD val = get_cos(a[k], a[p], a[q]);
                if(mult(a[p], a[q], a[k]) > 0) {
                    ls.pb(mp(-val, mp(k, -1)));
                } else {
                    ls.pb(mp(val, mp(k, 1)));
                }
            }
        }
        sort(all(ls));
        go(VI(all(js)));
        for(int i = 0, j; i < sz(ls); i = j) {
            for(j = i; j < sz(ls) && ls[j].fi < ls[i].fi + 1e-12;) ++j;
            replr(k, i, j) if(ls[k].se.se > 0) js.insert(ls[k].se.fi);
            go(VI(all(js)));
            replr(k, i, j) if(ls[k].se.se < 0) js.erase(ls[k].se.fi);
            go(VI(all(js)));
        }
    }

    printf("Case #%d: %d\n", cs, ans);
}

int main() {
    freopen("b.out", "w", stdout);
    int num;
    scanf("%d", &num);
    rep(i, 1, num) { 
        fprintf(stderr,"case %d\n", i);
        solve(i); }
    return 0;
}
