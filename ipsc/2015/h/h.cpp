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

int es[24];
int n;

int cnt[1<<24];
int _log[1<<24];
int bits[1<<24];

void solve() {
    scanf("%d", &n);
    int m; scanf("%d", &m);
    fillchar(es, 0);
    repn(i, m) {
        int x, y; scanf("%d%d", &x,&y);
        --x, --y;
        es[x]|=(1<<y);
        es[y]|=(1<<x);
    }

    cnt[0]=0;
    rep(s, 1, (1<<n)-1) {
        int lb=(s&-s);
        int i=_log[lb];
        int s0=s^lb;
        cnt[s]=cnt[s0]+bits[s0&es[i]];
        //printf("cnt[%d]=%d   s0=%d es=%d\n",s,cnt[s],s0,es[i]);
    }

    int ans1=0, ans2=1<<30;
    repn(s1, 1<<n) {
        if(!(s1&1)) continue;
        if((s1&2)) continue;
        int s2=((1<<n)-1)^s1;
        int v1=cnt[s1], v2=cnt[s2];
        setmax(ans1, v1+v2);
        setmin(ans2, abs(v1-v2));
    }
    cout<<ans1<<" "<<ans2<<endl;
}

int main() {
    repn(i, 24) _log[1<<i]=i;
    bits[0]=0;
    rep(s, 1, (1<<24)-1)
        bits[s]=bits[s^(s&-s)]+1;

    int csn; scanf("%d", &csn);
    repn(cs, csn) {
        solve();
    }
    return 0;
}
