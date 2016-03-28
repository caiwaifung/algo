#include <iostream>
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

LL K, C, S;

void read_input() {
    cin>>K>>C>>S;
}

LL ind(VL is) {
    LL r=1, b=1;
    for(LL i: is) r+=(i-1)*b, b*=K;
    return r;
}

VL solve() {
    if(C*S<K) return VL();
    LL cur=1;
    VL r;
    while(cur<=K) {
        VL is;
        repn(z, C) is.pb(min(cur++, K));
        r.pb(ind(is));
    }
    return r;
}

int main() {
    //freopen("/Users/fqw/Downloads/in.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        VL ans=solve();
        printf("Case #%d: ", cs);
        if(ans.empty()) printf("IMPOSSIBLE\n");
        else { for(LL x: ans) printf(" %lld", x); printf("\n"); }
    }
    return 0;
}

