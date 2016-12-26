#include <algorithm>
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

const int N=200000;

VI es[N];
bool liked[N];
int n;
LL ans;

PII f[N];

PII merge(PII a, PII b) {
    PII c;
    c.fi=max(a.fi, b.fi);
    c.se=a.se|b.se;
    return c;
}

void dfs(int x, int fa) {
    f[x]=mp(0, liked[x]);
    for(int y: es[x]) if(y!=fa) {
        dfs(y, x);
        f[x]=merge(f[x], f[y]);
    }
    ++f[x].fi;
}

void dfs2(int x, int fa, PII top) {
    VI ys;
    for(int y: es[x]) if(y!=fa) ys.pb(y);
    vector<PII> l(sz(ys)+1), r(sz(ys)+1);
    repn(i, sz(ys)) l[i+1]=merge(l[i], f[ys[i]]);
    irepn(i, sz(ys)) r[i]=merge(r[i+1], f[ys[i]]);
    repn(i, sz(ys)) {
        PII tmp=merge(top, merge(l[i], r[i+1]));
        if(liked[x]) tmp.se=1;
        ++tmp.fi;
        dfs2(ys[i], x, tmp);
    }

    VPI vs;
    for(int y: es[x]) {
        vs.pb(y==fa ? top : f[y]);
    }
    sort(all(vs), greater<PII>());
    if(!vs.empty()) {
        int ubound=min(vs[0].fi-1, sz(vs)>1 ? vs[1].fi+1 : 1);
        int lbound=0;
        if(!liked[x]) {
            int i=sz(vs)-1;
            while(i>=0 && !vs[i].se) --i;
            if(i>=0) lbound=vs[i].fi;
                else lbound=ubound+1;
        }
        if(lbound<=ubound) {
            ans+=ubound-lbound+1;
        }
    }
}

int main() {
    scanf("%d", &n);
    repn(i, n-1) {
        int a, b; scanf("%d%d", &a,&b);
        --a, --b;
        es[a].pb(b), es[b].pb(a);
    }
    static char buf[N+1];
    scanf("%s", buf);
    repn(i, n) {
        liked[i]=(buf[i]=='1');
    }

    dfs(0, -1);
    ans=0;
    dfs2(0, -1, mp(0, 0));
    if(count(liked, liked+n, true)>0) ++ans;
    cout<<ans<<endl;

    return 0;
}
