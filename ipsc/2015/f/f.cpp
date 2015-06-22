// 9:40
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

const int MAXN=1000010;
const LL MOD=LL(1e9)+7;

int lf[MAXN], rf[MAXN];
LL pair_cnt;
int n;
map<int, int> ls[MAXN];
set<int> rs[MAXN];

int gf(int f[], int x) {
    VI st;
    while(f[x]!=0) st.pb(x), x=f[x];
    for(int s: st) f[s]=x;
    return x;
}

void init() {
    pair_cnt=0;
    rep(i, 1, n) {
        lf[i]=rf[i]=0;
        ls[i].clear(); ls[i].insert(mp(i, 1));
        rs[i].clear(); rs[i].insert(i);
    }
}

void unite_l(int x, int y) {
    x=gf(lf, x), y=gf(lf, y);
    if(x==y) return;
    if(ls[x].size()<ls[y].size()) {
        unite_l(y, x); return;
    }
    for(PII p: ls[y]) {
        pair_cnt+=(LL)ls[x][p.fi]*(LL)p.se;
        ls[x][p.fi]+=p.se;
        rs[p.fi].erase(y);
        rs[p.fi].insert(x);
    }
    ls[y].clear();
    lf[y]=x;
}

void unite_r(int x, int y) {
    x=gf(rf, x), y=gf(rf, y);
    if(x==y) return;
    if(ls[x].size()<ls[y].size()) {
        unite_r(y, x); return;
    }
    for(int p: rs[y]) {
        rs[x].insert(p);
        if(ls[p].count(x))
            pair_cnt+=(LL)ls[p][x]*(LL)ls[p][y];
        ls[p][x]+=ls[p][y];
        ls[p].erase(ls[p].find(y));
    }
    rs[y].clear();
    rf[y]=x;
}

int main() {
    //freopen("f2.out", "w", stdout);
    int csn; scanf("%d", &csn);
    repn(cs, csn) {
        fprintf(stderr, "%d/%d\n", cs,csn);
        int q; scanf("%d%d", &n,&q);
        init();
        LL ans=0;
        repn(i, q) {
            int t, a, b;
            scanf("%d%d%d", &t,&a,&b);
            if(t==1) unite_l(a, b);
                else unite_r(a, b);
            ans=(ans+pair_cnt%MOD*(i+1))%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}
