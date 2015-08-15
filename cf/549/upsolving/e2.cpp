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

typedef long double LD;
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

LD get_cos(Point a, Point b, Point p) {
    LD d=(LD)sqr_dis(a, b);
    LD u=(LD)sqr_dis(p, a);
    LD v=(LD)sqr_dis(p, b);
    LD cos_theta=(u+v-d)/(2*sqrtl(u*v));
    _debug("    get_cos: d=%.3lf u=%.3lf v=%.3lf cos=%.3lf\n",d,u,v,cos_theta);
    return cos_theta;
}

bool farthur(Point a, Point b, Point p, Point q) {
    return get_cos(a, b, p)>get_cos(a, b, q);
}

int shape(LD cosA, LD cosB) { // <0 if angA+angB>180 degree
    return sgn(cosA+cosB);
    //LD angA=acos(cosA), angB=acos(cosB);
    //LD v=PI-(angA+angB);
    //return sgn(v);
}

bool check(const VP &a, const VP &b, int i, int j) {
    _debug("CHECK i=%d j=%d\n",i,j);
    LD al=-1, ar=-1;
    repn(k, a.size()) {
        int m0=mult(a[i], a[j], a[k]);
        _debug(" a: k=%d m0=%d\n", k,m0);
        if(m0==0) {
            if(dot(a[k], a[i], a[j])<=0) continue;
            return false;
        }
        if(m0>0) {
            setmax(al, get_cos(a[i],a[j],a[k]));
        } else {
            setmax(ar, get_cos(a[i],a[j],a[k]));
        }
    }
    _debug("  al=%.5lf ar=%.5lf\n", al, ar);
    if(al>-1 && ar>-1 && shape(al, ar)>0)
        return false;

    LD bl=2, br=2;
    repn(k, b.size()) {
        int m0=mult(a[i], a[j], b[k]);
        _debug(" b: k=%d m0=%d\n", k,m0);
        if(m0==0) {
            if(dot(b[k], a[i], a[j])<=0) return false;
            continue;
        }
        if(m0>0) {
            setmin(bl, get_cos(a[i],a[j],b[k]));
        } else {
            setmin(br, get_cos(a[i],a[j],b[k]));
        }
    }
    _debug("  bl=%.5lf br=%.5lf\n", bl, br);
    if(bl<1 && br<1 && shape(bl, br)<=0)
        return false;

    if(sgn(bl-al)<=0) return false;
    if(sgn(br-ar)<=0) return false;

    return true;
}

bool go(const VP &a, const VP &b, int i, int j) {
    if(check(a, b, i, j))
        return true;
    _debug("CHECK_END\n");
    if(i+1<j) {
        int mid=i+1;
        rep(k, i+1, j-1)
            if(farthur(a[i], a[j], a[k], a[mid]))
                mid=k;
        if(go(a, b, i, mid)) 
            return true;
        if(go(a, b, mid, j))
            return true;
    }
    return false;
}

bool inside_convex(Point p, const VP &a) {
    if(a.size()<3) return false;
    repn(i, a.size())
        if(mult(a[i], a[(i+1)%a.size()], p)<0)
            return false;
    return true;
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
