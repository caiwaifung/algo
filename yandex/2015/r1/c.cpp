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


// f[1][1][0/1][1] = 1
//
// g[n][k][t][c] = f[n][k][t][1] + ... + f[n][k][t][c]
//
// f[n][k][0][c]
//   <- f[n-1][k-1][1][n-1] + ... + f[n-1][k-1][1][n-c]
//   <- f[n-1][k][0][c-1] + ... + f[n-1][k][0][1]
// f[n][k][1][c]
//   <- f[n-1][k-1][1][c-1] + ... + f[n-1][k-1][1][1]
//   <- f[n-1][k][0][n-1] + ... + f[n-1][k][0][n-c]

const LL MOD=(1e9)+7;
const int N=510;

LL f[N][2][N], g[N][2][N];

int main() {
    int n0, k0; scanf("%d%d", &n0,&k0);

    fillchar(f, 0);
    f[1][0][1]=f[1][1][1]=1;
    rep(n, 2, n0) {
        fillchar(g, 0);
        rep(k, 1, n-1) repn(t, 2) {
            rep(c, 1, n) g[k][t][c]=g[k][t][c-1]+f[k][t][c];
        }
        fillchar(f, 0);
        rep(k, 1, n) rep(c, 1, n) {
            (f[k][0][c]+=g[k-1][1][n-1]-g[k-1][1][max(0,n-c-1)])%=MOD;
            (f[k][0][c]+=g[k][0][c-1])%=MOD;
            (f[k][1][c]+=g[k-1][1][c-1])%=MOD;
            (f[k][1][c]+=g[k][0][n-1]-g[k][0][max(0,n-c-1)])%=MOD;
        }
    }

    LL ans=f[k0][0][n0];
    /*
    rep(c, 1, n0) {
        (ans+=f[k0][0][c])%=MOD;
        if(c<n0) (ans+=f[k0][1][c])%=MOD;
    }
    */
    printf("%d\n", (int)ans);

    return 0;
}
