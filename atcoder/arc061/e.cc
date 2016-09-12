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
#include <map>
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

int solve(const vector<VPI> es, int st, int en) {
    const int n=sz(es);
    vector<bool> vis(n, false);
    VI cur;
    cur.pb(st), vis[st]=true;
    for(int ans=0; !cur.empty(); ++ans) {
        for(int i=0; i<sz(cur); ++i) {
            const int x=cur[i];
            for(const auto& e: es[x]) if(e.se==0) {
                if(!vis[e.fi]) {
                    vis[e.fi]=true;
                    cur.pb(e.fi);
                }
            }
        }
        if(vis[en]) return ans;
        VI tmp;
        for(int i=0; i<sz(cur); ++i) {
            const int x=cur[i];
            for(const auto& e: es[x]) if(e.se==1) {
                if(!vis[e.fi]) {
                    vis[e.fi]=true;
                    tmp.pb(e.fi);
                }
            }
        }
        cur=tmp;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n, m; cin>>n>>m;
    vector<VPI> es(n+m);
    map<PII, VI> shares;
    repn(i, m) {
        int a, b, c; cin>>a>>b>>c;
        --a, --b;
        es[a].pb(mp(n+i, 1));
        es[b].pb(mp(n+i, 1));
        es[n+i].pb(mp(a, 0));
        es[n+i].pb(mp(b, 0));
        shares[mp(a, c)].pb(i);
        shares[mp(b, c)].pb(i);
    }
    for(const auto& kv: shares) {
        int i=-1;
        for(int j: kv.se) {
            if(i>=0) {
                es[n+i].pb(mp(n+j, 0));
                es[n+j].pb(mp(n+i, 0));
            }
            i=j;
        }
    }
    int ans=solve(es, 0, n-1);
    cout<<ans<<endl;

    return 0;
}
