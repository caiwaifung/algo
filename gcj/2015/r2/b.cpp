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

const double EPS=1e-6;

double r[111], s[111], c[111], X, V;
int n;

void init() {
    scanf("%d", &n);
    double a, b;
    scanf("%lf%lf", &a,&b); 
    V=int(a*10000+.5), X=int(b*10000+.5);
    forint(i, 1, n) {
        scanf("%lf%lf", &a,&b); 
        r[i]=int(a*10000+.5), c[i]=int(b*10000+.5);
    }
    forint(i, 1, n) forint(j, i+1, n)
        if(c[i]>c[j]) {
            swap(r[i], r[j]);
            swap(c[i], c[j]);
        }
}

bool ok(double t) {
    double rest=V, temp=0;
    forint(i, 1, n) {
        s[i]=min(rest, r[i]*t);
        rest-=s[i];
        temp+=s[i]*c[i];
    }
    if(temp>V*X+EPS) return false;
    if(rest>EPS) return false;
    rest=V, temp=0;
    forintdown(i, n, 1) {
        s[i]=min(rest, r[i]*t);
        rest-=s[i];
        temp+=s[i]*c[i];
    }
    if(temp<V*X-EPS) return false;
    return true;
}

void solve(int cs) {
    printf("Case #%d: ", cs);
    bool b1=false, b2=false;
    forint(i, 1, n) {
        if(c[i]-EPS<X) b1=true;
        if(c[i]+EPS>X) b2=true;
    }
    if(!b1 || !b2) {
        //printf("%.4lf %.4lf:\n",X,V);
        //forint(i, 1, n) printf("%.4lf %.4lf\n", r[i],c[i]);
        printf("IMPOSSIBLE\n"); return;
    }
    double le=0, ri=1e10;
    forn(tt, 299) {
        double mid=(le+ri)/2;
        if(ok(mid)) ri=mid;
            else le=mid;
    }
    printf("%.9lf\n", ri);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
