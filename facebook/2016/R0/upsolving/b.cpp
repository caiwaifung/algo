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

bool get(char cur, int l, int c, int side, int &r) {
    if(cur=='.') {
        if(l==0) {
            if(c) r=1;
            else {
                if(side) r=0; else r=2;
            }
            return true;
        } else if(l==1) {
            r=1; return true;
        } else { // l==2
            if(c) r=1; else r=2;
            return true;
        }
    } else {
        if(c==1) return false;
        if(l==2) return false;
        r=0;
        return true;
    }
}

void solve(int cs) {
    int n; scanf("%d", &n);
    static char a[2][1010];
    scanf("%s%s", a[0]+1,a[1]+1);

    static int f[1010][3][3];
    fillchar(f, 50);
    f[0][0][0]=0;
    rep(i, 1, n) repn(x, 3) repn(y, 3) {
        repn(p, 2) repn(q, 2) {
            int x0, y0;
            if(!get(a[0][i], x, p, q, x0)) continue;
            if(!get(a[1][i], y, q, p, y0)) continue;
            setmin(f[i][x0][y0], f[i-1][x][y]+p+q);
        }
    }

    int ans=1<<30;
    repn(x, 2) repn(y, 2) setmin(ans, f[n][x][y]);

    printf("Case #%d: %d\n", cs,ans);
}

int main() {
    int t; scanf("%d", &t);
    rep(cs, 1, t) solve(cs);
    return 0;
}
