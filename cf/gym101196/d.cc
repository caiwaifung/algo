#include <algorithm>
#include <map>
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

vector<VPI> es;
int n;

void solve() {
    vector<int> vis(n, 0);
    VI cur;
    cur.pb(0), vis[0]=-1;
    int ans=0;
    while(!cur.empty()) {
        VI d(n, 1<<30);
        VI tmp;
        for(int x: cur) {
            for(const auto& e: es[x]) {
                if(vis[e.fi]==0) {
                    vis[e.fi]=1;
                    d[e.fi]=e.se;
                    tmp.pb(e.fi);
                } else if(vis[e.fi]==1) {
                    setmin(d[e.fi], e.se);
                }
            }
        }
        for(int x: tmp) {
            ans+=d[x];
            vis[x]=-1;
        }
        cur=tmp;
    }

    repn(i, n) if(!vis[i]) {
        cout<<"Impossible"<<endl;
        return;
    }
    cout<<ans<<endl;
}

int main() {
    int m; cin>>n>>m;
    ++n;
    map<string, int> id;
    id["English"]=0;
    replr(i, 1, n) {
        string s; cin>>s;
        id[s]=i;
    }
    es.resize(n);
    while(m--) {
        string a, b; int c;
        cin>>a>>b>>c;
        int x=id[a], y=id[b];
        es[x].pb(mp(y, c)), es[y].pb(mp(x, c));
    }
    solve();

    return 0;
}
