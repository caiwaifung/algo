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
    friend LL mult(const Point &p0, const Point &p1, const Point &p2) {
        return LL(p1.x-p0.x)*LL(p2.y-p0.y) - LL(p1.y-p0.y)*LL(p2.x-p0.x);
    }
    friend LL mult(const Point &p1, const Point &p2) {
        return (LL)p1.x*(LL)p2.y-(LL)p1.y*(LL)p2.x;
    }
    bool operator <(const Point &p) const {
        return mult(*this, p)<0;
    }
};

int cal(vector<Point> as) {
    if(as.size()<=2) return 0;

    vector<Point> xs, ys;
    for(auto &p: as) {
        if(p.y>0 || (p.y==0 && p.x>0))
            xs.PB(p);
        else
            ys.PB(p);
    }
    sort(all(xs));
    sort(all(ys));
    xs.insert(xs.end(), all(ys));
    size_t i=0, j=1;
    int ans=1<<30;
    for(; i<xs.size(); ++i) {
        while(j!=i && mult(xs[i], xs[j])<0) j=(j+1)%xs.size();
        int tmp=int(j-i)-1;
        if(tmp<0) tmp+=(int)xs.size();
        setmin(ans, tmp);
    }
    return ans;
}

int main() {
    int ncs; scanf("%d", &ncs);
    forint(cs, 1, ncs) {
        int n; scanf("%d", &n);
        static Point a[3030];
        forint(i, 1, n) scanf("%d%d",&a[i].x,&a[i].y);
        printf("Case #%d:\n", cs);
        forint(i, 1, n) {
            vector<Point> as;
            forint(j, 1, n) if(j!=i) {
                Point p;
                p.x=a[j].x-a[i].x;
                p.y=a[j].y-a[i].y;
                as.PB(p);
            }
            int ans=cal(as);
            printf("%d\n", ans);
        }
    }
    return 0;
}
