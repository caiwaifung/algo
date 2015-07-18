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

int days(int y, int m) {
    if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) return 31;
    if(m==4 || m==6 || m==9 || m==11) return 30;
    assert(m==2);
    if(y%4==0 && (y%100!=0 || y%400==0)) return 29;
        else return 28;
}

int cal(int x, int l) {
    int ans=0;
    const int c[10]={6,2,5,5,4,  5,6,3,7,6};
    while(l--) ans+=c[x%10], x/=10;
    return ans;
}

int main() {
    int cs; scanf("%d", &cs);
    repn(csi, cs) {
        int d, want; scanf("%d%d", &d,&want);
        int y=d/10000, m=d%10000/100; d=d%100;
        int t=0;
        while(1) {
            if(y>2999) { t=-1; break; }
            if(cal(y, 4)+cal(m, 2)+cal(d, 2)==want) break;
            ++t;
            ++d; 
            if(d>days(y, m)) {
                d=1; ++m;
                if(m>12) m=1, ++y;
            }
        }
        printf("%d\n", t);
    }
    return 0;
}
