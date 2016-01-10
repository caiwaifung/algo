// 12:40 - 
#include <cassert>
#include <algorithm>
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

const int N=100010;

int f[2][N];
int a[N], n, k;

void solve() {
    int p; scanf("%d%d%d", &k,&n,&p);
    rep(i, 1, n) {
        int w, d, r; scanf("%d%d%d", &w,&d,&r);
        a[i]=r*12-w*d*p;
    }

    int o1=0, o2=1;
    fillchar(f, 0);
    rep(j, 1, k) {
        fillchar(f[o2], 0);
        int cur=0;
        rep(i, 1, n) {
            setmax(cur, f[o1][i-1]);
            cur+=a[i];
            f[o2][i]=cur;
        }
        rep(i, 1, n) setmax(f[o2][i], f[o2][i-1]);
        swap(o1, o2);
    }
    printf("%d\n", f[o1][n]);
}

int main() {
    int cs; scanf("%d", &cs);
    while(cs--) solve();
    return 0;
}
