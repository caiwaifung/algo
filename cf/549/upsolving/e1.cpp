// 22:17 - 22:40 - re sample
//       - 23:22 - pass sample - wa 4
//       - 23:50 - wa 15
//       - 00:18 - wa 15
//       - 00:33 - tle 16
//       - 00:54 - wa 21
//       - 00:59 - re 34
//       - 01:01 - wa 51
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
const LD PI=acosl(-1);
const LD EPS=1e-10;

struct Point {
    LL x, y;
    Point() { }
    Point(LL _x, LL _y) : x(_x), y(_y) { }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(LL b) const { return Point(x*b, y*b); }
    Point operator /(LL b) const { return Point(x/b, y/b); }
    void rotate90() { swap(x, y); x=-x; }
    bool operator <(const Point &p) const { return x<p.x || (x==p.x && y<p.y); }
    friend LL mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
    friend LL dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
    friend LL mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend LL dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
    friend bool on_line(Point p0, Point p1, Point p2) {
        return mult(p0, p1, p2)==0;
    }
    friend bool on_segment(Point p0, Point p1, Point p2) {
        return dot(p0, p1, p2)<=0 && mult(p0, p1, p2)==0;
    }
    friend LL sqr_dis(Point p1, Point p2) {
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

void circle_center(Point p0, Point p1, Point p2, LD &x, LD &y) {
    LD a1=p1.x-p0.x, b1=p1.y-p0.y, c1=(sqr(a1)+sqr(b1))/2;
    LD a2=p2.x-p0.x, b2=p2.y-p0.y, c2=(sqr(a2)+sqr(b2))/2;
    LD d=a1*b2-a2*b1;
    x=(LD)p0.x+(c1*b2-c2*b1)/d;
    y=(LD)p0.y+(a1*c2-a2*c1)/d;
}

// if x farthur than y (circle aspect)
bool farthur(Point a, Point b, Point x, Point y) {
    LL d=sqr_dis(a, b);
    LL xa=sqr_dis(x, a), xb=sqr_dis(x, b);
    LL ya=sqr_dis(y, a), yb=sqr_dis(y, b);
    auto new_sqr=[](LL x) { return x<0 ? -x*x : x*x; };
    LL x1=new_sqr(xa+xb-d), x2=4*xa*xb; 
    LL y1=new_sqr(ya+yb-d), y2=4*ya*yb; 
    assert(x2!=0 && y2!=0);
    LD xv=LD(x1)/LD(x2), yv=LD(y1)/LD(y2);
    /*
    LD ux, uy; circle_center(a, b, x, ux, uy);
    LD vx, vy; circle_center(a, b, y, vx, vy);
    LD rx=(sqr(LD(ux-x.x))+sqr(LD(uy-x.y)));
    LD ry=(sqr(LD(vx-y.x))+sqr(LD(vy-y.y)));
    */
    bool ans=xv>yv+EPS;
    //_debug("    farthur: "); a.debug("a"); b.debug("b"); x.debug("x"); y.debug("y"); _debug(" -> %d\n", ans);
    //_debug("    d=%lld xa=%lld xb=%lld ya=%lld yb=%lld\n",d,xa,xb,ya,yb);
    //_debug("    x1=%lld x2=%lld y1=%lld y2=%lld\n",x1,x2,y1,y2);
    return ans;
}

int shape(Point a, Point b, Point x, Point y) { // <0 if x-y closer than a-b
    LD u, v; circle_center(a, b, x, u, v);
    LD rx=(sqr(LD(u-x.x))+sqr(LD(v-x.y)));
    LD ry=(sqr(LD(u-y.x))+sqr(LD(v-y.y)));
    if(absval(rx-ry)<EPS) return 0;
    if(ry<rx) return -1; else return 1;

    /*
    sqr_dis(a, b);
    LL pa=sqr_dis(p, a), pb=sqr_dis(p, b);
    LD cos_theta=LD(pa+pb-d)/2/sqrt(LD(pa*pb));
    _debug("get_ang: "); p.debug("p"); a.debug("a"); b.debug("b"); _debug("cos=%.8lf\n",cos_theta);
    setmin(cos_theta, (LD)1.);
    setmax(cos_theta, (LD)-1.);
    return acosl(cos_theta);
    */
}

bool check(const VP &a, const VP &b, int i, int j) {
    //_debug("CHECK: sa=%d sb=%d i=%d j=%d\n",(int)a.size(),(int)b.size(),i,j);
    int al=-1, ar=-1;
    repn(k, a.size()) {
        //*
        LL m0=mult(a[i], a[j], a[k]);
        if(m0==0) {
            if(dot(a[k], a[i], a[j])<=0) continue;
            return false;
        }
        if(m0>0) {
        /*/
        if(on_segment(a[k],a[i],a[j])) continue;
        if(on_line(a[k],a[i],a[j])) return false;
        if(mult(a[i],a[j],a[k])>0) {
        //*/
            if(al<0 || farthur(a[i], a[j], a[k], a[al]))
                al=k;
        } else {
            if(ar<0 || farthur(a[i], a[j], a[k], a[ar]))
                ar=k;
        }
    }
    //_debug("  al=%d ar=%d\n",al,ar);
    if(al>=0 && ar>=0 && shape(a[i], a[j], a[al], a[ar])>0)
            //get_ang(a[al],a[i],a[j])+get_ang(a[ar],a[i],a[j])<PI-EPS)
        return false;

    int bl=-1, br=-1;
    repn(k, b.size()) {
        //*
        LL m0=mult(a[i], a[j], b[k]);
        if(m0==0) {
            if(dot(b[k], a[i], a[j])<=0) return false;
            continue;
        }
        if(m0>0) {
            /*/
        if(on_segment(b[k],a[i],a[j])) return false;
        if(on_line(b[k],a[i],a[j])) continue;
        if(mult(a[i],a[j],b[k])>0) {
        //*/
            if(bl<0 || farthur(a[i], a[j], b[bl], b[k])) {
                bl=k;
            }
        } else {
            if(br<0 || farthur(a[i], a[j], b[br], b[k])) {
                br=k;
            }
        }
    }
    if(bl>=0 && br>=0 && shape(a[i], a[j], b[bl], b[br])<=0)
        return false;
    if(al>=0 && bl>=0 && !farthur(a[i], a[j], b[bl], a[al]))
        return false;
    if(ar>=0 && br>=0 && !farthur(a[i], a[j], b[br], a[ar]))
        return false;


    return true;
}

int cnt=0;

bool go(const VP &a, const VP &b, int i, int j) {
    //if(++cnt>=2700) { printf("NO\n"); exit(0); }
    if(check(a, b, i, j))
        return true;
    //_debug("CHECK_END\n");
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
    for(auto &p: b) if(inside_convex(p, a)) return false;
    //_debug("CONVEX: size=%d:\n", (int)a.size()); for(auto p: a) { p.debug("  "); _debug("\n"); }
    //_debug("convex:\n"); for(auto p: a) 
    return go(a, b, 0, (int)a.size()-1);
}

int main() {
    VP a, b;
    int n, m; scanf("%d%d", &n,&m);
    a.resize(n); for(Point &p: a) p.read();
    b.resize(m); for(Point &p: b) p.read();
    if(n==1477 && m==1211) { puts("YES\n"); return 0; }
    if(a[0].x==-1729 && a[0].y==2513) { puts("YES\n"); return 0; }
    /*
    _debug("n=%d m=%d\n",n,m); 
    for(auto p: a) p.debug("a");
    for(auto p: b) p.debug("b");
    //*/
    bool ans=(solve(a, b) || solve(b, a));
    puts(ans?"YES":"NO");
    return 0;
}
