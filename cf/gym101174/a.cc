#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
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
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<LD,LD> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

int sgn(LD x, LD e=1e-8) {
    return x < -e ? -1 : x>e;
}

struct Point {
    LD x, y;
    Point() : x(0), y(0) {}
    Point(LD _x, LD _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x+p.x, y+p.y); }
    Point operator-(const Point& p) const { return Point(x-p.x, y-p.y); }
    Point operator*(LD b) const { return Point(x*b, y*b); }
    Point operator/(LD b) const { return Point(x/b, y/b); }
    bool operator==(const Point& p) const { return sgn(x-p.x)==0 && sgn(y-p.y)==0; }

    LD abs() const { return sqrtl(x*x+y*y); }
};

LD sqr(LD x) { return x*x; }

int cross_cc(Point p1, LD r1, Point p2, LD r2, Point *a1, Point *a2) {
    LD mx=p2.x-p1.x, sx=p2.x+p1.x, mx2=mx*mx;
    LD my=p2.y-p1.y, sy=p2.y+p1.y, my2=my*my;
    LD sq=mx2+my2, d=-(sq-sqr(r1-r2))*(sq-sqr(r1+r2));
    if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrtl(d);
    LD x=mx*((r1+r2)*(r1-r2) + mx*sx) + sx*my2;
    LD y=my*((r1+r2)*(r1-r2) + my*sy) + sy*mx2;
    LD dx=mx*d, dy=my*d; sq*=2.;
    *a1=Point((x-dy)/sq, (y+dx)/sq);
    *a2=Point((x+dy)/sq, (y-dx)/sq);
    if(sgn(d)>0) return 2; else return 1;
}

Point find(Point p, LD len, LD d) {
    if(p==Point()) {
        //assert(sgn(len-d)==0);
        return Point(0, len);
    }
    Point r1, r2;
    if(cross_cc(p, len, Point(), d, &r1,&r2)==0) {
        return p/(d+len)*d;
        //assert(false);
    }
    return r1;
}

LD read() { double x; scanf("%lf", &x); return x; }

int main() {
    int n; scanf("%d", &n);
    vector<LD> len(n);
    Point target;
    repn(i, n) len[i]=read();
    target.x=read(), target.y=read();

    vector<PDD> range(n+1);
    range[0]=mp(0,0);
    repn(i, n) {
        range[i+1].se=range[i].se+len[i];
        if(range[i].se>=len[i]) {
            range[i+1].fi=max((LD)0.0, range[i].fi-len[i]);
        } else {
            range[i+1].fi=len[i]-range[i].se;
        }
    }

    LD dis=max(min(target.abs(), range[n].se), range[n].fi);
    if(target==Point()) {
        target=Point(0, dis);
    } else {
        target=target/target.abs()*dis;
    }
    vector<Point> r;
    irepn(i, n) {
        r.pb(target);
        LD begin=max(range[i].fi, abs(dis-len[i]));
        LD end=min(range[i].se, dis+len[i]);
        LD d2=(begin+end)/2;
        Point t2=find(target, len[i], d2);
        target=t2, dis=d2;
    }
    reverse(all(r));
    for(const auto& p: r) {
        printf("%.9lf %.9lf\n", (double)p.x,(double)p.y);
    }
    /*
    printf("%.3lf\n", r[0].abs());
    repn(i, sz(r)-1) printf("%.3lf\n", (r[i+1]-r[i]).abs());
    printf("%.5lf\n", (r.back()-old_target).abs());
    */


    return 0;
}
