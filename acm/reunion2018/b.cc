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
#ifndef H_ALGO_HEADER
#define H_ALGO_HEADER

#define all(a) (a).begin(), (a).end()
template <class T> int len(const T& a) { return static_cast<int>(a.size()); }
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
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, len(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
int read_int() { int x; scanf("%d", &x); return x; }
LL read_ll() { LL x; scanf("%lld", &x); return x; }
string read_string() { string s; cin >> s; return s; }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
#define IN read_int()

template <class T> T sorted(T x) { sort(x.begin(), x.end()); return x; }
template <class T> T reversed(T x) { reverse(x.begin(), x.end()); return x; }

template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }

#endif
// clang-format on
// }}}

typedef double R;

R sqr(R x) { return x * x; }

const R EPS = 1e-10;
R sgn(R x) { return x < -EPS ? -1 : x > EPS; }
struct Point {
    R x, y;
    Point() {}
    Point(R _x, R _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(R b) const { return Point(x * b, y * b); }
    Point operator/(R b) const { return Point(x / b, y / b); }
    void rotate90() {
        swap(x, y);
        x = -x;
    }
    R len() const { return sqrt(x * x + y * y); }
    void normalize() { *this = *this / len(); }
    friend R mult(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
    friend R dot(Point p1, Point p2) { return p1.x * p2.x + p1.y * p2.y; }
    friend R mult(Point p0, Point p1, Point p2) {
        return mult(p1 - p0, p2 - p0);
    }
    friend R dot(Point p0, Point p1, Point p2) { return dot(p1 - p0, p2 - p0); }
    friend R dist(Point p1, Point p2) { return (p1 - p2).len(); }
    R lambda(Point s, Point t) const { // return c: p=s+(t-s)*c
        return dot(s, t, *this) / dot(s, t, t);
    }
};

LL det(LL x0, LL y0, LL x1, LL y1, LL x2, LL y2) {
    return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
}

struct P3 {
    LL x, y, z;
    void read() {
        auto t = read_vi(3);
        x = t[0], y = t[1], z = t[2];
    }
    friend R dis(P3 a, P3 b) {
        return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
    }
    friend bool online(P3 a, P3 b, P3 c) {
        if (det(a.x, a.y, b.x, b.y, c.x, c.y) != 0) return false;
        if (det(a.x, a.z, b.x, b.z, c.x, c.z) != 0) return false;
        if (det(a.y, a.z, b.y, b.z, c.y, c.z) != 0) return false;
        return true;
    }
};

int cross_cc(Point p1, R r1, Point p2, R r2, Point& ans1, Point& ans2) {
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (sgn(d) < 0) return 0;
    if (sgn(d) == 0)
        d = 0;
    else
        d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d;
    sq *= 2.;
    ans1 = Point((x - dy) / sq, (y + dx) / sq);
    ans2 = Point((x + dy) / sq, (y - dx) / sq);
    if (sgn(d) > 0)
        return 2;
    else
        return 1;
}

void find_points(R a, R b, R c, Point& p1, Point& p2, Point& p3) {
    p1 = Point(0, 0);
    p2 = Point(0, b);
    R cosC = (a * a + b * b - c * c) / 2 / a / b;
    if (cosC > 1) cosC = 1;
    if (cosC < -1) cosC = -1;
    R sinC = sqrt(1 - cosC * cosC);
    p3 = Point(a * sinC, a * cosC);
}

bool check2(Point p1, R r1, Point p2, R r2, Point p3, R r3) {
    Point c1, c2;
    if (cross_cc(p1, r1, p2, r2, c1, c2) == 0) return false;
    // cout << "cross ok " << (c1 - p3).len() << " " << r3 << " " << endl;
    if ((c1 - p3).len() <= r3 + EPS) return true;
    if ((c2 - p3).len() <= r3 + EPS) return true;
    return false;
}

bool inside(Point p1, R r1, Point p2, R r2) {
    return (p1 - p2).len() <= r2 - r1 + EPS;
}

bool check(Point p1, Point p2, Point p3, R length) {
    R r1 = length, r2 = length * 3 / 2, r3 = length * 3 / 2;
    if (inside(p1, r1, p2, r2) && inside(p1, r1, p3, r3)) {
        return true;
    }
    repn(__, 2) {
        swap(p1, p2), swap(r1, r2);
        repn(_, 3) {
            if (check2(p1, r1, p2, r2, p3, r3)) return true;
            auto p = p1;
            auto r = r1;
            p1 = p2, p2 = p3, p3 = p;
            r1 = r2, r2 = r3, r3 = r;
        }
    }
    return false;
}

R solve(P3 a, P3 b, P3 c) {
    if (online(a, b, c)) {
        R r = dis(a, b);
        setmax(r, dis(a, c));
        setmax(r, dis(b, c));
        return r / 6;
    }
    R da = dis(a, b), db = dis(b, c), dc = dis(a, c);
    Point p1, p2, p3;
    find_points(da, db, dc, p1, p2, p3);
    R le = 0, ri = 1e10;
    // R le = 3, ri = 3;
    repn(_, 100) {
        R mid = (le + ri) / 2;
        bool ok = false;
        repn(__, 3) {
            if (check(p1, p2, p3, mid)) ok = true;
            Point tmp = p1;
            p1 = p2, p2 = p3, p3 = tmp;
        }
        if (ok)
            ri = mid;
        else
            le = mid;
    }
    return le;
}

int main() {
    for (int num = IN, cs = 1; cs <= num; ++cs) {
        P3 a, b, c;
        a.read(), b.read(), c.read();
        double ans = solve(a, b, c);
        printf("Case #%d: %.15lf\n", cs, (double)ans);
    }
    return 0;
}
