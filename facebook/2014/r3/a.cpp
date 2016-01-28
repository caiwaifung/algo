// 10:12
// 10:15 - 10:25 - wa sam
//       - 10:27 - pass sam - ac
#include <cassert>
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

const int MAXN=110;
const LL MOD=LL(1e9)+7;

int n, tot, a[MAXN];

void read_input() {
    scanf("%d", &n);
    tot=0; rep(i, 1, n) scanf("%d", &a[i]), tot+=a[i];
}

LL C[MAXN][MAXN], P[MAXN][MAXN];

int solve() {
    fillchar(C, 0);
    repn(i, MAXN) C[i][0]=C[i][i]=1;
    repn(i, MAXN) rep(j, 1, i-1) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
    fillchar(P, 0);
    repn(i, MAXN) {
        P[i][0]=1;
        rep(j, 1, i) P[i][j]=(P[i][j-1]*(i-j+1))%MOD;
    }

    static LL f[MAXN][MAXN][MAXN];
    fillchar(f, 0);
    f[0][0][0]=1;
    rep(i, 1, n) rep(x, 0, tot) rep(y, 0, tot) {
        LL val=f[i-1][x][y]; if(val==0) continue;
        rep(lout, 0, a[i]) rep(lin, 0, a[i]) {
            if(lout<=x && lin<=y) {
                int x0=x-lout+(a[i]-lin);
                int y0=y-lin+(a[i]-lout);
                LL tmp=val;
                (tmp*=C[a[i]][lout])%=MOD;
                (tmp*=C[a[i]][lin])%=MOD;
                (tmp*=P[x][lout])%=MOD;
                (tmp*=P[y][lin])%=MOD;
                (f[i][x0][y0]+=tmp)%=MOD;
            }
        }
    }
    LL ans=f[n][0][0];
    return (int)ans;
}

int main() {
    freopen("/Users/fqw/Downloads/secret_santa.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

