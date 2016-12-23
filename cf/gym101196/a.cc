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

typedef long double R;
typedef pair<R,R> PRR;

const R PI=acosl(-1);

int sgn(R x, R e=1e-15) {
    return x<-e ? -1 : x>e;
}

struct Point {
    R x, y;
    Point() : x(0), y(0) {}
    Point(R _x, R _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x+p.x, y+p.y); }
    Point operator-(const Point& p) const { return Point(x-p.x, y-p.y); }
    Point operator*(R b) const { return Point(x*b, y*b); } 
    Point operator/(R b) const { return Point(x/b, y/b); } 
    bool operator==(const Point& p) const { return sgn(x-p.x)==0 && sgn(y-p.y)==0; }
    R abs() const { return sqrtl(x*x+y*y); } 
};

struct Circle {
    Point c;
    R r;
};

R sqr(R x) { return x*x; }

int cross_cc(Point p1, R r1, Point p2, R r2, Point &c1, Point &c2) {
    R mx=p2.x-p1.x, sx=p2.x+p1.x, mx2=mx*mx;
    R my=p2.y-p1.y, sy=p2.y+p1.y, my2=my*my;
    R sq=mx2+my2, d=-(sq-sqr(r1-r2))*(sq-sqr(r1+r2));
    if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
    R x=mx*((r1+r2)*(r1-r2) + mx*sx) + sx*my2;
    R y=my*((r1+r2)*(r1-r2) + my*sy) + sy*mx2;
    R dx=mx*d, dy=my*d; sq*=2.;
    c1=Point((x-dy)/sq, (y+dx)/sq);
    c2=Point((x+dy)/sq, (y-dx)/sq);
    if(sgn(d)>0) return 2; else return 1;
}

bool inside(Point p, Circle c) {
    return sgn(sqr(p.x-c.c.x)+sqr(p.y-c.c.y)-sqr(c.r))<=0;
}

bool inside(Circle c1, Circle c2) {
    return sgn((c1.c-c2.c).abs()+c1.r-c2.r)<=0;
}

bool intersect(Circle c1, Circle c2, PRR* angles) {
    if(c1.c==c2.c) {
        if(sgn(c1.r-c2.r)>=0) {
            return false;
        } else {
            *angles=mp(-PI, PI);
            return true;
        }
    }
    if(inside(c1, c2)) {
        *angles=mp(-PI, PI);
        return true;
    }
    if(inside(c2, c1)) {
        return false;
    }

    Point p1, p2;
    if(cross_cc(c1.c, c1.r, c2.c, c2.r, p1, p2)<=1) {
        return false;
    }
    R a1=atan2l(p1.y-c1.c.y, p1.x-c1.c.x);
    R a2=atan2l(p2.y-c1.c.y, p2.x-c1.c.x);
    R a3=(a1<=a2 ? (a1+a2)/2 : (a1+a2)/2+PI);
    if(!inside(Point(c1.c.x+c1.r*cosl(a3), c1.c.y+c1.r*sinl(a3)), c2)) {
        swap(a1, a2);
    }
    *angles=mp(a1, a2);
    return true;
}

R cut_output(vector<PRR>* output, PRR ang) {
    if(sgn(ang.fi-ang.se)>0) {
        return cut_output(output, mp(ang.fi,PI))+cut_output(output, mp(-PI, ang.se));
    }
    vector<PRR> r;
    R ans=0;
    for(const auto u: *output) {
        if(sgn(u.se-ang.fi)<=0 || sgn(ang.se-u.fi)<=0) {
            r.pb(u); continue;
        }
        ans+=min(u.se, ang.se)-max(u.fi, ang.fi);
        if(sgn(u.se-ang.se)>0) {
            r.pb(mp(ang.se, u.se));
        }
        if(sgn(ang.fi-u.fi)>0) {
            r.pb(mp(u.fi, ang.fi));
        }
    }
    *output=r;
    return ans/PI/2;
}

struct Glass {
    Circle c;
    R height, volume;
    bool operator<(const Glass& g) const { return height>g.height; }
};

R solve(vector<Glass> glasses) {
    vector<vector<PRR>> es(sz(glasses));
    sort(all(glasses));
    es[0].pb(mp(0, 100));

    R ans=0;
    repn(i, sz(es)) {
        if(es[i].empty()) {
            return -1;
        }
        sort(all(es[i]));
        reverse(all(es[i]));
        R need=glasses[i].volume;
        while(1) {
            PRR e=es[i].back();
            es[i].pop_back();
            if(!es[i].empty()) {
                R t=es[i].back().fi-e.fi;
                R v=t*e.se;
                if(v<=need) {
                    need-=v;
                    es[i].back().se+=e.se;
                    continue;
                }
            }
            if(e.se<1e-8) return -1;
            R t=need/e.se;
            setmax(ans, e.fi+t);
            es[i].pb(mp(e.fi+t, e.se));
            break;
        }

        vector<PRR> output;
        output.pb(mp(-PI, PI));
        replr(j, i+1, sz(es)) {
            PRR cur;
            if(!intersect(glasses[i].c, glasses[j].c, &cur)) {
                continue;
            }
            R ratio=cut_output(&output, cur);
            if(sgn(ratio)>0) {
                for(const auto& e: es[i]) {
                    es[j].pb(mp(e.fi, e.se*ratio));
                }
            }
        }
    }
    return ans;
}

int main() {
    int n; scanf("%d", &n);
    vector<Glass> glasses(n);
    repn(i, n) {
        double x, y, z, r, v;
        scanf("%lf%lf%lf%lf%lf", &x,&y,&z,&r,&v);
        glasses[i].c.c=Point(x, y);
        glasses[i].c.r=r;
        glasses[i].height=z;
        glasses[i].volume=v;
    }
    R ans=solve(glasses);
    if(sgn(ans)<0) {
        printf("Invalid\n");
    } else {
        printf("%.2lf\n", double(ans));
    }
    return 0;
}
