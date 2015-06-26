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

const int MOD=int(1e9)+7;

int binom[1010][1010];

int main() {
    fillchar(binom, 0);
    repn(i, 1010) binom[i][0]=binom[i][i]=1;
    repn(i, 1010) rep(j, 1, i-1) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;

    static int k, a[1010];
    scanf("%d", &k); rep(i, 1, k) scanf("%d", &a[i]);
    int n=0;
    LL ans=1;
    rep(i, 1, k) {
        ans=ans*binom[n+a[i]-1][n]%MOD;
        n+=a[i];
    }
    printf("%d\n", (int)ans);
    return 0;
}
