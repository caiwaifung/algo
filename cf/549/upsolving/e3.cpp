// (8.14)
// 22:17 - 22:40 - re sample
//       - 23:22 - pass sample - wa 4
//       - 23:50 - wa 15
//       - 00:18 - wa 15
//       - 00:33 - tle 16
//       - 00:54 - wa 21
//       - 00:59 - re 34
//       - 01:01 - wa 51
// (retry: 8.15)
// 12:14 - 12:34 - wa 20
// (retry -> using cot method, no sqrt)
// 13:33 - 13:46 - ac
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }
template<class T> T sqr(T _a) { return _a*_a; }
template<class T> T absval(T _a) { return _a>0?_a:-_a; }

typedef double LD;
const LD PI=(LD)acosl(-1);
const LD EPS=1e-10;
int sgn(LD x) { return x<-EPS ? -1 : x>EPS; }

struct Point {
    int x, y;
    Point() { }
    Point(int _x, int _y) : x(_x), y(_y) { }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(int b) const { return Point(x*b, y*b); }
    Point operator /(int b) const { return Point(x/b, y/b); }
    void rotate90() { swap(x, y); x=-x; }
    bool operator <(const Point &p) const { return x<p.x || (x==p.x && y<p.y); }
    friend int mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
    friend int dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
    friend int mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend int dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
    friend bool on_line(Point p0, Point p1, Point p2) {
        return mult(p0, p1, p2)==0;
    }
    friend bool on_segment(Point p0, Point p1, Point p2) {
        return dot(p0, p1, p2)<=0 && mult(p0, p1, p2)==0;
    }
    friend int sqr_dis(Point p1, Point p2) {
        return sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
    }
    void read() { int u, v; scanf("%d%d", &u,&v); x=u, y=v; }
    void debug(const char *s) const { _debug("%s=(%d,%d) ", s,(int)x,(int)y); }
};
typedef vector<Point> VP;

VP cal_convex(VP a) {
    VP b; sort(all(a));
    for(const Point &p: a) {
        while(b.size()>1 && mult(b[b.size()-2], b[b.size()-1], p)<=0)
            b.pop_back();
        b.pb(p);
    }
    size_t t=b.size(); reverse(all(a));
    for(const Point &p: a) {
        while(b.size()>t && mult(b[b.size()-2], b[b.size()-1], p)<=0)
            b.pop_back();
        b.pb(p);
    }
    b.pop_back();
    return b;
}

bool check(const VP &a, const VP &b, int i, int j, int &mid) {
    mid=-1;
    LD le=-1e50, ri=1e50;
    repn(k, a.size()) {
        int m0=mult(a[i], a[j], a[k]);
        int d0=dot(a[k], a[i], a[j]);
        if(m0==0) {
            if(d0<=0) continue;
            return false;
        }
        LD r=LD(d0)/LD(m0);
        if(m0>0) {
            setmin(ri, -r);
        } else {
            if(setmax(le, -r)) mid=k;
        }
    }
    repn(k, b.size()) {
        int m0=mult(a[i], a[j], b[k]);
        int d0=dot(b[k], a[i], a[j]);
        if(m0==0) {
            if(d0<=0) return false;
            continue;
        }
        LD r=LD(d0)/LD(m0);
        if(m0>0) {
            setmax(le, -r);
        } else {
            setmin(ri, -r);
        }
    }
    if(sgn(le-ri)>=0)
        return false;
    return true;
}

bool go(const VP &a, const VP &b, int i, int j) {
    int mid=-1;
    if(check(a, b, i, j, mid))
        return true;
    if(mid>=0)
        return go(a, b, i, mid) || go(a, b, mid, j);
    return false;
}

bool solve(VP a, VP b) {
    if(a.size()==1) return true;
    if(a.size()>2) a=cal_convex(a);
    return go(a, b, 0, (int)a.size()-1);
}

int main() {
    VP a, b;
    int n, m; scanf("%d%d", &n,&m);
    a.resize(n); for(Point &p: a) p.read();
    b.resize(m); for(Point &p: b) p.read();
    bool ans=(solve(a, b) || solve(b, a));
    puts(ans?"YES":"NO");
    return 0;
}
