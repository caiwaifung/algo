#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

struct Point {
    LL x, y;
    Point() {}
    Point(LL x, LL y) : x(x), y(y) {}
    Point operator -(const Point &p) const {
        return Point(x-p.x, y-p.y);
    }
    Point operator +(const Point &p) const {
        return Point(x+p.x, y+p.y);
    }
    bool operator <(const Point &p) const {
        return false;
    }
};

pair<int, PLL> a[50010];
Point ap[50010];
int n;

void init() {
    scanf("%d", &n);
    forint(i, 1, n) {
        int x, y;
        scanf("%d%d%d", &x,&y,&a[i].fi);
        a[i].se.fi=(LL)x*2-(LL)y*2;
        a[i].se.se=(LL)x*2+(LL)y*2;
    }
    sort(a+1, a+n+1);
    forint(i, 1, n) {
        ap[i].x=a[i].se.fi;
        ap[i].y=a[i].se.se;
    }
}

pair<Point,Point> merge(pair<Point,Point> a, pair<Point,Point> b) {
    pair<Point,Point> c;
    c.fi.x=max(a.fi.x, b.fi.x);
    c.fi.y=max(a.fi.y, b.fi.y);
    c.se.x=min(a.se.x, b.se.x);
    c.se.y=min(a.se.y, b.se.y);
    return c;
}

bool ok(LL r) {
    if(n==1) return true;

    Point rp(r, r);
    pair<Point, Point> area=MP(ap[1]-rp, ap[1]+rp);
    forint(i, 2, n) {
        LL t=a[i].fi-a[i-1].fi;
        Point m(t*2, t*2);
        area.fi=area.fi-m;
        area.se=area.se+m;
        area=merge(area, MP(ap[i]-rp, ap[i]+rp));
        if(area.fi.x>area.se.x) return false;
        if(area.fi.y>area.se.y) return false;
    }
    return true;
}

void solve(int cs) {
    LL le=0, ri=LL(5e9);
    while(le<ri) {
        LL mid=(le+ri)/2;
        if(ok(mid)) ri=mid;
            else le=mid+1;
    }
    LL x=le, y=2;
    if(x%2==0) x/=2, y/=2;
    printf("Case #%d:\n", cs);
    cout<<x<<"/"<<y<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
