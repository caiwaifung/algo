#include <algorithm>
#include <set>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
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
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const LL MOD=LL(1e9)+7;

int main() {
    int n, m, k; scanf("%d%d%d", &n,&m,&k);
    vector<VI> es(n);
    repn(i, m) {
        int a, b; scanf("%d%d", &a,&b);
        --a, --b;
        es[a].pb(b), es[b].pb(a);
    }

    VI vis(n, 0), dfn(n), low(n);
    vector<VPI> comps;
    VPI stack;
    int label=0;
    const function<void(int, int)> dfs=[&](int x, int fa) {
        dfn[x]=low[x]=label++;
        vis[x]=-1;
        for(int y: es[x]) if(y!=fa && vis[y]<=0) {
            stack.pb(mp(x, y));
            if(vis[y]==0) {
                dfs(y, x);
                if(low[y]>=dfn[x]) {
                    VPI comp;
                    do {
                        comp.pb(stack.back());
                        stack.pop_back();
                    } while(comp.back()!=mp(x, y));
                    comps.pb(comp);
                }
                setmin(low[x], low[y]);
            } else {
                setmin(low[x], dfn[y]);
            }
        }
        vis[x]=1;
    };
    repn(x, n) if(vis[x]==0) dfs(x, -1);

    const int N=210;
    static LL pow[N], inv[N], binom[N][N];
    const auto power=[&](LL a, LL b) {
        LL c=1;
        for(; b>0; b>>=1, a=a*a%MOD)
            if(b&1) c=c*a%MOD;
        return c;
    };
    pow[0]=1;
    rep(i, 1, N-1) pow[i]=(pow[i-1]*k)%MOD;
    rep(i, 1, N-1) inv[i]=power(i, MOD-2);
    repn(i, N) binom[i][0]=binom[i][i]=1;
    rep(i, 1, N-1) rep(j, 1, i-1) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;

    LL ans=1;
    for(const auto& c: comps) {
        if(sz(c)==1) {
            (ans*=k)%=MOD;
            continue;
        }
        set<int> s; for(PII p: c) s.insert(p.fi), s.insert(p.se);
        //cout<<sz(c)<<" "<<sz(s)<<": "<<c<<" "<<VI(all(s))<<endl;
        if(sz(c)==sz(s)) {
            LL tmp=0;
            rep(i, 1, sz(c)) (tmp+=pow[gcd(i,sz(c))])%=MOD;
            (tmp*=inv[sz(c)])%=MOD;
            (ans*=tmp)%=MOD;
        } else {
            (ans*=binom[k+sz(c)-1][sz(c)])%=MOD;
        }
    }
    cout<<ans<<endl;

    return 0;
}
