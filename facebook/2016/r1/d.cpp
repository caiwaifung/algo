// 2:07
// 2:17 - 2:37
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

int win[22];
int n;

void read_input() {
    scanf("%d", &n);
    fillchar(win, false);
    repn(i, n) repn(j, n) {
        int x; scanf("%d", &x);
        if(x==1) win[i]|=(1<<j);
    }
}

int compete(int x, int y) {
    int s=0;
    repn(i, n) {
        if(x&(1<<i)) if(win[i]&y) s|=(1<<i);
        if(y&(1<<i)) if(win[i]&x) s|=(1<<i);
    }
    return s;
}

VPI solve() {
    static int cnt[1<<16], log[1<<16];
    cnt[0]=0;
    rep(i, 1, (1<<n)-1) {
        assert((i^(i&-i)) == (i&(i-1)));
        cnt[i]=1+cnt[i&(i-1)];
    }
    repn(i, n) log[1<<i]=i;

    static int f[1<<16];
    fillchar(f, 0);
    rep(s, 1, (1<<n)-1) {
        int c=cnt[s]; if((c&(c-1))>0) continue;
        if(c==1) { f[s]=s; continue; }
        for(int s0=(s-1); s0>0; s0=(s0-1)&s) {
            int c0=cnt[s0]; if(c0*2!=c) continue;
            f[s]|=compete(f[s0], f[s^s0]);
        }
    }

    VPI ans((size_t)n);
    for(PII& p: ans) p.fi=9999999, p.se=1;
    rep(s, 1, (1<<n)-1) {
        int c=cnt[s]; if((c&(c-1))>0) continue;
        repn(i, n) if(s&(1<<i)) {
            if(f[s]&(1<<i))
                setmin(ans[(size_t)i].fi, n/c/2+1);
            if(f[s]^(1<<i))
                setmax(ans[(size_t)i].se, n/c+1);
        }
    }

    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/boomerang_tournament.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        VPI ans=solve();
        printf("Case #%d:\n", cs);
        for(PII p: ans) printf("%d %d\n",p.fi,p.se);
    }
    return 0;
}

