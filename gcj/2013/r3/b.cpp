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
typedef pair<int,int> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

struct Point {
    int x, y;
    Point() { }
    Point(int x, int y) : x(x), y(y) { }
    bool operator <(const Point &p) const {
        return x<p.x || (x==p.x && y<p.y);
    }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(int b) const { return Point(x*b, y*b); }
    Point operator /(int b) const { return Point(x/b, y/b); }
    void rotate90() { swap(x, y); x=-x; }
    friend int mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
    friend int dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
    friend int mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend int dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
};


Point a[11]; int n; Point b[11];
Point c[11]; int m;
void go_convex() {
    m=0;
    memmove(b, a, sizeof(a));
    sort(b+1, b+n+1);
    forint(i, 1, n) {
        while(m>1 && mult(c[m-1], c[m], b[i])<=0) --m;
        c[++m]=b[i];
    }
    int t=m;
    forintdown(i, n, 1) {
        while(m>t && mult(c[m-1], c[m], b[i])<=0) --m;
        c[++m]=b[i];
    }
    --m;
}

void init() {
    cin>>n;
    forint(i, 1, n) cin>>a[i].x>>a[i].y;
    go_convex();
}

void solve(int cs) {
    LL area1=0;
    forint(i, 1, m-1) area1+=mult(c[1], c[i], c[i+1]);

    LL ans=0;
    int best_p[11], p[11];
    forint(i, 1, n) p[i]=i;
    do {
        LL tmp=0;
        p[0]=p[n];

        bool ok=true;
        forint(i, 1, n) forint(j, 1, n) {
            if(p[i-1]==p[j-1] || p[i-1]==p[j]) continue;
            if(p[i]==p[j-1] || p[i]==p[j]) continue;
            Point a1=a[p[i-1]], a2=a[p[i]];
            Point b1=a[p[j-1]], b2=a[p[j]];
            if(mult(a1, a2, b1)*mult(a1, a2, b2)>=0) continue;
            if(mult(b1, b2, a1)*mult(b1, b2, a2)>=0) continue;
            ok=false;
        //forint(i, 1, n) printf("%d ", p[i]-1); printf(": bad %d %d\n",i,j); break;
        }
        //*
        forint(i, 1, n) forint(j, 1, n)
            if(j!=p[i-1] && j!=p[i]) {
                Point a1=a[p[i-1]], a2=a[p[i]];
                Point b=a[j];
                if(mult(b, a1, a2)==0 && dot(b, a1, a2)<=0)
                    ok=false;
            }
            //*/
        if(ok) {
            forint(i, 1, n-1) tmp+=mult(a[p[1]], a[p[i]], a[p[i+1]]);
        //forint(i, 1, n) printf("%d ", p[i]-1); printf(": ok tmp=%lld (%lld)\n",tmp,area1);
        }

        if(tmp>ans) {
            ans=tmp; forint(i, 1, n) best_p[i]=p[i];
        }
    } while(next_permutation(p+2, p+n+1));

    printf("Case #%d: ", cs);
    printf("%.3lf (%lld, %lld) ", ans/(double)area1,ans,area1);
    if(ans*2>area1) {
        forint(i, 1, n) printf("%d ", best_p[i]-1);
        printf("\n");
    }
    else printf("ERROR %lld %lld\n",ans, area1);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
