#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
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
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

void sp(PII x, PII &l, PII &r) {
    if(x.fi>0) l=mp(0,0), r=x;
    else if(x.se<0) l=x, r=mp(0,0);
    else l=mp(x.fi,0), r=mp(0,x.se);
}
int go(PII x, PII y, PII z) {
    return (x.se-x.fi)*(y.se-y.fi)*(z.se-z.fi);
}

int main() {
    int cs; scanf("%d", &cs);
    while(cs--) {
        int x1, x2, y1, y2, z1, z2;
        scanf("%d%d%d%d%d%d", &x1,&x2,&y1,&y2,&z1,&z2);
        PII x=mp(x1, x2), y=mp(y1, y2), z=mp(z1, z2);
        PII xl, xr, yl, yr, zl, zr;
        sp(x, xl, xr);
        sp(y, yl, yr);
        sp(z, zl, zr);
        int v1=go(xr, yr, zr);
        int v2=go(xl, yr, zr);
        int v3=go(xl, yl, zr);
        int v4=go(xr, yl, zr);
        int v5=go(xr, yr, zl);
        int v6=go(xl, yr, zl);
        int v7=go(xl, yl, zl);
        int v8=go(xr, yl, zl);
        printf("%d %d %d %d %d %d %d %d\n", v1,v2,v3,v4,v5,v6,v7,v8);
    }
    return 0;
}
