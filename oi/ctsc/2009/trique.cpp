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

const int MAXN=1010;

int main() {
    static int a[1010], n;
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", &a[i]);
    while(n>0 && a[n]==1) --n;
    
    static int cnt[1010][4];
    fillchar(cnt, 0);
    rep(i, 1, n) {
        memcpy(cnt[i], cnt[i-1], sizeof(cnt[i]));
        cnt[i][a[i]]++;
    }

    static int f2[1010][1010];
    static int f3[1010][1010];
    fillchar(f2, 50);
    fillchar(f3, 50);
    f2[0][0]=f3[0][0]=0;
    int ans=1<<30;
    rep(i, 0, n-1) {
        int c1=cnt[i][1];
        irep(c, i, 0) {
            setmin(f2[i][0], f3[i][c]+c*2+c1);
            setmin(f3[i][0], f2[i][c]+c*2+c1);
        }
        rep(c, 0, i) {
            if(a[i+1]==1) setmin(f2[i+1][c], f2[i][c]+1);
            if(a[i+1]==2) setmin(f2[i+1][c+1], f2[i][c]+1);
            if(a[i+1]==3) setmin(f2[i+1][c], f2[i][c]+1);
            if(a[i+1]==1) setmin(f3[i+1][c], f3[i][c]+1);
            if(a[i+1]==2) setmin(f3[i+1][c], f3[i][c]+1);
            if(a[i+1]==3) setmin(f3[i+1][c+1], f3[i][c]+1);
        }
    }

    rep(c, 0, n) {
        int c1=cnt[n][1];
        setmin(ans, f2[n][c]+c*2+c1);
        setmin(ans, f3[n][c]+c*2+c1);
    }
    printf("%d\n", ans);

    return 0;
}
