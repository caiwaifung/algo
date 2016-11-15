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
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

int sgn(double x, double e=1e-8) {
    return x<-e ? -1 : x>e;
}

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x+p.x, y+p.y); }
    Point operator-(const Point& p) const { return Point(x-p.x, y-p.y); }
    Point operator*(double c) const { return Point(x*c, y*c); }
    Point operator/(double c) const { return Point(x/c, y/c); }
    friend double mult(Point p0, Point p1, Point p2) {
        return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
    }
    friend double dot(Point p0, Point p1, Point p2) {
        return (p1.x-p0.x)*(p2.x-p0.x)+(p2.y-p0.y)*(p1.y-p0.y);
    }
};
typedef vector<Point> VP;

Point read_point() {
    Point p;
    scanf("%lf%lf", &p.x,&p.y);
    return p;
}

VP read_convex() {
    int n; scanf("%d", &n);
    VP a; repn(i, n) a.pb(read_point());
    double s=0;
    repn(i, n) s+=mult(a[0], a[i], a[(i+1)%sz(a)]);
    if(sgn(s)<0) reverse(all(a));
    return a;
}

VP move_convex(const VP& a, Point offset) {
    VP b;
    for(const auto& p: a) b.pb(p+offset);
    return b;
}

double lambda(Point p, Point dir, Point q) {
    if(sgn(dir.x)!=0) {
        return (q.x-p.x)/dir.x;
    } else {
        return (q.y-p.y)/dir.y;
    }
}

double hit_time(Point p, Point dir, Point q1, Point q2) {
    if(sgn(dir.x)==0 && sgn(dir.y)==0) {
        return -1;
    }
    double m1=mult(p, p+dir, q1);
    double m2=mult(p, p+dir, q2);
    if(sgn(m1)*sgn(m2)>0) {
        return -1;
    }
    if(sgn(m1-m2)==0) {
        return min(lambda(p, dir, q1), lambda(p, dir, q2));
    }
    Point t;
    t.x=(q1.x*m2-q2.x*m1)/(m2-m1);
    t.y=(q1.y*m2-q2.y*m1)/(m2-m1);
    return lambda(p, dir, t);
}

VP cut_convex(VP a, Point p1, Point p2) {
    VP r;
    repn(i, sz(a)) {
        Point a1=a[i], a2=a[(i+1)%sz(a)];
        double m1=mult(p1, p2, a1);
        double m2=mult(p1, p2, a2);
        if(sgn(m1)*sgn(m2)<0) {
            Point t;
            t.x=(a1.x*m2-a2.x*m1)/(m2-m1);
            t.y=(a1.y*m2-a2.y*m1)/(m2-m1);
            r.pb(t);
        }
        if(sgn(m2)>=0) {
            r.pb(a2);
        }
    }
    return r;
}

double intersect_convex(VP a, VP b) {
    repn(i, sz(a)) {
        b=cut_convex(b, a[i], a[(i+1)%sz(a)]);
    }
    double s=0;
    repn(i, sz(b)) s+=mult(b[0], b[i], b[(i+1)%sz(b)]);
    return s/2;
}

int main() {
    VP a=read_convex();
    Point va=read_point();
    VP b=read_convex();
    Point vb=read_point();

    vector<double> criticals;
    repn(tt, 2) {
        repn(i, sz(a)) repn(j, sz(b)) {
            double t=hit_time(a[i], va-vb, b[j], b[(j+1)%sz(b)]);
            if(sgn(t)>0) {
                criticals.pb(t);
            }
        }
        swap(a, b), swap(va, vb);
    }
    sort(all(criticals));
    pair<double, double> ans(-1, -1);
    const auto update=[&](double t) {
        double s=intersect_convex(move_convex(a, (va-vb)*t), b);
        if(sgn(s-ans.fi)>0 || (sgn(s-ans.fi)==0 && t<ans.se)) {
            ans=mp(s, t);
        }
        return s;
    };
    repn(i, sz(criticals)) {
        update(criticals[i]);
    }
    repn(i, sz(criticals)-1) {
        double le=criticals[i], ri=criticals[i+1];
        repn(tt, 100) {
            double m1=(le*2+ri)/3, m2=(le+ri*2)/3;
            double s1=update(m1), s2=update(m2);
            if(s1>s2) {
                ri=m2;
            } else {
                le=m1;
            }
        }
    }

    if(sgn(ans.fi)<0) {
        printf("never\n");
    } else {
        printf("%.9lf\n", ans.se);
    }
    return 0;
}
