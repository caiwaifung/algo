#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//{{{
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
template<class T> T absv(T _x) { return _x>0?_x:-_x; }
//}}}

int n;
double Ww, Wb, Lw, Lb;

void read_input() {
    cin>>n>>Ww>>Wb>>Lw>>Lb;
}

double power(double a, int b) {
    double c=1;
    for(; b>0; b>>=1, a*=a)
        if(b&1) c*=a;
    return c;
}

double go(double x, double y, double p0, int num) {
    // p' = x + y * p  for num times
    if(num==0) return p0;
    if(y==1) { assert(x==0); return p0; }
    double p=x/(y-1)+p0;
    double pn=p*power(y, num)-x/(y-1);
    return pn;
}

double solve() {
    if(n==1) { return Ww; }
    double u=min(Lw, Lb), v=max(Lw, Lb);
    double x=u, y=v-u;
    double p1=Lw;
    double p=go(x, y, p1, n-2);
    return p*max(Ww, Wb)+(1-p)*min(Ww, Wb);
}

int main() {
    freopen("/Users/fqw/Downloads/chess.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        double ans=solve();
        assert(ans>=0 && ans<=1);
        printf("Case #%d: %.17lf\n", cs, ans);
    }
    return 0;
}

