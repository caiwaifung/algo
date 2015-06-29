#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
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
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

typedef long double Real;

const int MAXN=3030;
const Real EPS=1e-8;
int sgn(Real x) { return x<-EPS?-1:x>EPS; }
template<class T> T sqr(T x) { return x*x; }
const Real PI=acos(-1);

struct Point {
    Real x, y;
    Point(Real _x=0, Real _y=0) : x(_x), y(_y) { }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(Real b) const { return Point(x*b, y*b); }
    Point operator /(Real b) const { return Point(x/b, y/b); }
    Point operator -() const { return Point(-x, -y); }
    void rotate90() { swap(x, y); x=-x; }
    friend Real mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
    friend Real dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
    friend Real mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend Real dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
    Real lambda(Point s, Point t) const { // return c: p=s+(t-s)*c
        return dot(s, t, *this)/dot(s, t, t);
    }
    void print() const { printf("(%.4lf, %.4lf) ",(double)x,(double)y); }
};
struct Line {
    Real a, b, c;
    void read() {
        int x, y, z;
        scanf("%d%d%d", &x,&y,&z);
        a=x, b=y, c=z;
        if(b>0 || (b==0 && a>0)) a=-a, b=-b, c=-c;
    }
    bool operator <(const Line &l) const {
        Real tmp=a*l.b-b*l.a;
        return tmp>0;
    }
    Point cross_line(Line l) const {
        Real t=a*l.b-b*l.a;
        Real x=b*l.c-c*l.b;
        Real y=c*l.a-a*l.c;
        return Point(x/t, y/t);
    }
};

struct Circle {
    Point p; Real r;
    Circle() { }
    Circle(Point _p, Real _r) : p(_p), r(_r) { }
    int cross_line(Line l, Point &p1, Point &p2) const {
        Real a=l.a, b=l.b, c=l.c; Real aa=a*a, bb=b*b, s=aa+bb;
        Real d=r*r*s-sqr(a*p.x+b*p.y+l.c);
        if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
        Real ab=a*b, bd=b*d, ad=a*d;
        Real xx=bb*p.x-ab*p.y-a*c;
        Real yy=aa*p.y-ab*p.x-b*c;
        p2=Point((xx+bd)/s, (yy-ad)/s);
        p1=Point((xx-bd)/s, (yy+ad)/s);
        if(sgn(d)>0) return 2; else return 1;
    }
    Real area() const {
        return r*r*PI;
    }
    Real arc_area(Point p1, Point p2) const {
        Real a1=atan2(p1.y-p.y, p1.x-p.x);
        Real a2=atan2(p2.y-p.y, p2.x-p.x);
        Real ang=a2-a1;
        if(ang<0) ang+=PI*2;
        assert(ang+EPS>=0 && ang-EPS<=PI*2);
        return r*r*ang/2;
    }
};


Line lines[MAXN];
int n;

Real cal(Circle c, Point p, Line l2, Line l1, Point d2, Point d1) {
    Point t1, t2;
    c.cross_line(l1, t1, t2); Point p1=dot(t1-p, d1)>0?t1:t2;
    c.cross_line(l2, t1, t2); Point p2=dot(t1-p, d2)>0?t1:t2;

    Real ans=c.arc_area(p2, p1);
    ans-=mult(c.p, p2, p1)/2;
    ans+=mult(p, p2, p1)/2;
    return ans;
}

int main() {
    scanf("%d", &n);
    rep(i, 1, n) lines[i].read();
    rep(i, 1, n-1) rep(j, i+1, n)
        if(lines[j]<lines[i])
            swap(lines[i], lines[j]);
    
    const Real R=1e7;
    Circle c(Point(0,0), R);


    Real ans=0, cnt=0;
    rep(i, 1, n) rep(j, i+1, n) {
        Point p=lines[i].cross_line(lines[j]);
        Point d1(lines[i].a, lines[i].b); d1.rotate90();
        Point d2(lines[j].a, lines[j].b); d2.rotate90();
        Line l1=lines[i], l2=lines[j];

        ans+=cal(c, p, l2, l1, d2, -d1)*(n-j);
        ans+=cal(c, p, l1, l2, -d1, -d2)*(j-i-1);
        ans+=cal(c, p, l2, l1, -d2, d1)*(i-1);
        cnt+=n-2;
    }
    ans=c.area()-ans*3/cnt;
    printf("%.9lf\n", (double)ans);

    return 0;
}
