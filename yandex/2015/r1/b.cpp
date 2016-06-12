#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

const double PI=acos(-1.);

struct Point {
    int x, y, v;
    double ang;
    void read() { scanf("%d%d%d", &x,&y,&v); }
    bool operator<(const Point& p) const {
        return ang<p.ang;
    }
};
typedef vector<Point> VP;

int go(VP a, int v0) {
    vector<pair<double, int>> d;
    for(const auto& p: a) d.pb(mp(p.ang, p.v));
    for(const auto& p: a) d.pb(mp(p.ang+PI*2, p.v));
    int ans=1<<30, tot=0;
    repn(i, sz(a)) tot+=a[i].v;
    int j=0, s=0;
    repn(i, sz(a)) {
        while(d[j].fi<d[i].fi+PI) {
            s+=d[j].se; ++j;
        }
        setmin(ans, abs(s+v0-(tot-s)));
        setmin(ans, abs(s-(tot-s+v0)));
        s-=d[i].se;
    }
    return ans;
}

int main() {
    int n; scanf("%d", &n);
    static Point p[1010];
    rep(i, 1, n) p[i].read();

    if(n==1) {
        printf("%d\n", p[1].v); return 0;
    }
    if(n==2) {
        printf("%d\n", abs(p[1].v-p[2].v)); return 0;
    }

    int ans=1<<30;
    rep(i, 1, n) {
        VP a;
        rep(j, 1, n) if(j!=i) {
            Point cur;
            cur.x=p[j].x-p[i].x;
            cur.y=p[j].y-p[i].y;
            cur.v=p[j].v;
            cur.ang=atan2(double(cur.y), double(cur.x));
            a.pb(cur);
        }
        sort(all(a));
        setmin(ans, go(a, p[i].v));
    }
    printf("%d\n", ans);

    return 0;
}
