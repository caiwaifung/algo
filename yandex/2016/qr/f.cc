#include <cassert>
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

const double eps=1e-7;

double px[55], py[55];
int n;
double ans, ax, ay;

void upt(double x, double y) {
    double s=0;
    rep(i, 1, n) {
        double d=sqrt((x-px[i])*(x-px[i])+(y-py[i])*(y-py[i]));
        d=max(1, int(d+1-eps));
        s+=1/d;
    }
    if(setmax(ans, s)) ax=x, ay=y;
}

void go(double x1, double x2, double y1, double y2) {
    upt((x1+x2)/2, (y1+y2)/2);
    if(x1+1e-7>x2) return;
    double maxp=0;
    rep(i, 1, n) {
        if(px[i]>=x1 && px[i]<=x2 && py[i]>=y1 && py[i]<=y2) {
            maxp+=1; continue;
        }
        double dx=px[i]<=x1 ? x1-px[i] : px[i]-x2;
        double dy=py[i]<=y1 ? y1-py[i] : py[i]-y2;
        double d=0;
        if(px[i]>=x1 && px[i]<=x2) {
            d=dx;
        } else if(py[i]>=y1 && py[i]<=y2) {
            d=dy;
        } else {
            d=sqrt(dx*dx+dy*dy);
        }
        d=max(1, int(d+1-eps));
        maxp+=1/d;
    }
    if(maxp<=ans+eps) return;
    double mx=(x1+x2)/2, my=(y1+y2)/2;
    go(x1, mx, y1, my);
    go(mx, x2, y1, my);
    go(x1, mx, my, y2);
    go(mx, x2, my, y2);
}

int main() {
    scanf("%d", &n); rep(i, 1, n) scanf("%lf%lf", &px[i],&py[i]);
    ans=ax=ay=-1;
    go(0, 50, 0, 50);
    printf("%.9lf\n", ans);
    printf("%.9lf %.9lf\n", ax,ay);
    return 0;
}
