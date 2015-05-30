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


// ------------------------ template ends here ------------------------ //

struct Point {
    int x, y;
    bool operator <(const Point &p) const {
        return x<p.x || (x==p.x && y<p.y);
    }
    friend LL mult(Point p0, Point p1, Point p2) {
        return (p1.x-p0.x)*LL(p2.y-p0.y) - (p1.y-p0.y)*LL(p2.x-p0.x);
    }
    friend LL dot(Point p1, Point p2) {
        return p1.x*(LL)p2.x+p1.y*(LL)p2.y;
    }
    double abs() {
        return sqrt((double)dot(*this,*this));
    }
};
Point a[4010];
int n;

void init() {
    static Point b[1010][4];
    scanf("%d", &n);
    forint(i, 1, n) forn(j, 4) scanf("%d%d", &b[i][j].x,&b[i][j].y);
    forint(i, 1, n) forn(j, 4) a[(i-1)*4+j+1]=b[i][j];
    n*=4;
}

Point c[8010]; int m;
void go_convex() {
    m=0;
    sort(a+1, a+n+1);
    forint(i, 1, n) {
        while(m>1 && mult(c[m-1], c[m], a[i])<=0) --m;
        c[++m]=a[i];
    }
    int t=m;
    forintdown(i, n, 1) {
        while(m>t && mult(c[m-1], c[m], a[i])<=0) --m;
        c[++m]=a[i];
    }
    --m;
}

void solve() {
    go_convex();
    forint(i, 1, m) c[m+i]=c[i];
    double tmp=1e50;
    forint(i, 1, m) {
        Point p1; 
        p1.x=c[i+1].x-c[i].x;
        p1.y=c[i+1].y-c[i].y;
        Point p2;
        p2.x=p1.y;
        p2.y=-p1.x;
        LL x1=1LL<<50, x2=-x1;
        LL y1=1LL<<50, y2=-y1;
        forint(j, 1, m) {
            setmin(x1, dot(p1,c[j])); setmax(x2, dot(p1,c[j]));
            setmin(y1, dot(p2,c[j])); setmax(y2, dot(p2,c[j]));
        }
        double ans=double(x2-x1)*double(y2-y1);
        ans/=p1.abs();
        ans/=p2.abs();
        setmin(tmp, ans);
        //printf("%.4lf %.3lf %.3lf\n", ans,p1.abs(),p2.abs());
    }
    
    printf("%.0lf\n", tmp);
    //printf("%d\n", (x2-x1)*(y2-y1));
}

int main() {
    int cs=0, csn; scanf("%d", &csn); 
    while(csn--) {
        init();
        printf("Case #%d:\n", ++cs);
        solve();
    }
    return 0;
}
