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

const LL MOD=1051962371;

LL c[110][110];
LL fac[110];

int main() {
    fac[0]=1; rep(i, 1, 100) fac[i]=fac[i-1]*i%MOD;
    fillchar(c, 0);
    rep(i, 0, 100) c[i][0]=c[i][i]=1;
    rep(i, 1, 100) rep(j, 1, i-1) c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
    LL f[110][110];
    fillchar(f, 0); f[0][0]=1;
    rep(i, 1, 100) rep(j, 0, i) {
        if(j>0) (f[i][j]+=f[i-1][j-1]) %= MOD;
        rep(k, 2, i) (f[i][j]+=f[i-k][j]*c[i-1][k-1]%MOD*fac[k-1])%=MOD;
    }
    int t; scanf("%d", &t);
    rep(tt, 1, t) { int x, y ;scanf("%d%d", &x,&y);
    LL ans=0; rep(i, y, x) (ans+=f[x][i])%=MOD;
    printf("Case #%d: %d\n",tt,(int)ans); }
    return 0;
}
