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

void solve(int cs) {
    int n, m; scanf("%d%d", &n,&m);
    int rows[20];
    repn(i, n) {
        char s[22]; scanf("%s", s);
        rows[i]=0;
        repn(j, m) if(s[j]=='.') rows[i]|=(1<<j);
    }

    int bits[1<<20];
    bits[0]=0;
    rep(i, 1, (1<<m)-1) bits[i]=bits[i-(i&-i)]+1;
    int ans=1<<30;
    repn(first, 1<<m) {
        int last=(rows[0]^first^(first<<1)^(first>>1))&((1<<m)-1);
        int o0=first;
        int tot=bits[first];
        rep(i, 1, n-1) {
            int o=last;
            last=(rows[i]^o0^o^(o<<1)^(o>>1))&((1<<m)-1);
            tot+=bits[o];
            o0=o;
        }
        if(last==0) setmin(ans, tot);
    }
    if(ans>=(1<<30)) ans=-1;

    printf("Case #%d: %d\n", cs, ans);
}

int main() {
    freopen("/Users/fqw/Downloads/turn_on_the_lights.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) {
        fprintf(stderr, "[%d/%d]\n",cs,csn);
        solve(cs);
    }
    return 0;
}
