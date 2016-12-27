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

int run(const vector<VI>& es, const VI& mask) {
    const int n=sz(es);
    VI f=mask;
    queue<int> que;
    repn(i, n) if(mask[i]>0) {
        que.push(i);
    }
    while(!que.empty()) {
        int x=que.front();
        que.pop();
        for(int y: es[x]) {
            if((f[y]&f[x])!=f[x]) {
                f[y]|=f[x];
                que.push(y);
            }
        }
    }
    int root=-1;
    repn(i, n) if(f[i]==15) root=i;
    if(root<0) return -1;

    //printf("root=%d\n",root);

    VI subtree(n), low(n), dfn(n), vis(n);
    vector<VI> children(n);
    int cur=0;
    function<void(int, int)> dfs=[&](int x, int fa) {
        //printf("%d %d\n",x,fa);
        subtree[x]=mask[x];
        low[x]=dfn[x]=cur++;
        vis[x]=-1;
        for(int y: es[x]) if(y!=fa) {
            if(vis[y]==0) {
                children[x].pb(y);
                dfs(y, x);
                subtree[x]|=subtree[y];
                setmin(low[x], low[y]);
            } else if(vis[y]<0) {
                setmin(low[x], dfn[y]);
            }
        }
        vis[x]=1;
    };
    dfs(root, -1);

    bool found=false;
    function<void(int, int)> dfs2=[&](int x, int upmask) {
        VI ys=children[x];
        VI l(sz(ys)+1), r(sz(ys)+1);
        repn(i, sz(ys)) l[i+1]=l[i]|subtree[ys[i]];
        irepn(i, sz(ys)) r[i]=r[i+1]|subtree[ys[i]];
        repn(i, sz(ys)) {
            dfs2(ys[i], upmask|mask[x]|l[i]|r[i+1]);
        }

        for(int y: ys) {
            if(subtree[y]==15) { found=true; }
            if(low[y]<dfn[x]) upmask|=subtree[y];
        }
        if(upmask==15) found=true;
    };
    dfs2(root, 0);

    if(found) {
        return -1;
    } else {
        return cur;
    }
}

void solve() {
    int n, m; cin>>n>>m;
    VS lines(n);
    repn(i, n) cin>>lines[i];

    vector<VPI> ids(n, VPI(m, {-1,-1}));
    int num=0;
    repn(i, n) repn(j, m) {
        if(lines[i][j*2]=='0') {
            ids[i][j].fi=num++;
        }
        if(lines[i][j*2+1]=='0') {
            ids[i][j].se=num++;
        }
    }
    vector<VI> es(num);
    const function<void(int,int,int,int,int,int)> add_edge=
    [&](int i1, int j1, int p1, int i2, int j2, int p2) {
        if(i1<0 || i1>=n || j1<0 || j1>=m) return;
        if(i2<0 || i2>=n || j2<0 || j2>=m) return;
        if(p1<0) {
            add_edge(i1, j1, 0, i2, j2, p2);
            add_edge(i1, j1, 1, i2, j2, p2);
            return;
        }
        if(p2<0) {
            add_edge(i1, j1, p1, i2, j2, 0);
            add_edge(i1, j1, p1, i2, j2, 1);
            return;
        }
        int a=(p1==0 ? ids[i1][j1].fi : ids[i1][j1].se);
        int b=(p2==0 ? ids[i2][j2].fi : ids[i2][j2].se);
        if(a<0 || b<0) return;
        es[a].pb(b), es[b].pb(a);
    };
    repn(i, n) repn(j, m) {
        add_edge(i, j, 0, i, j, 1);
        if((i+j)%2==0) {
            add_edge(i, j, -1, i-1, j, 1);
            add_edge(i, j, -1, i+1, j, 0);
            add_edge(i, j, 0, i, j-1, -1);
            add_edge(i, j, 1, i, j+1, -1);
        } else {
            add_edge(i, j, -1, i, j-1, 1);
            add_edge(i, j, -1, i, j+1, 0);
            add_edge(i, j, 0, i-1, j, -1);
            add_edge(i, j, 1, i+1, j, -1);
        }
    }
    VI mask(num);
    repn(i, n) repn(j, m) repn(p, 2) {
        int cur=0, t=(i+j)%2;
        if(i==0 && (t==0 || p==0)) cur|=1;
        if(i==n-1 && (t==0 || p==1)) cur|=2;
        if(j==0 && (t==1 || p==0)) cur|=4;
        if(j==m-1 && (t==1 || p==1)) cur|=8;
        int x=(p==0 ? ids[i][j].fi : ids[i][j].se);
        if(x>=0) mask[x]=cur;
    }

    int ans=run(es, mask);
    if(ans<0) {
        cout<<"NO MINIMAL CORRIDOR"<<endl;
    } else {
        cout<<ans<<endl;
    }
}

int main() {
    int cs; cin>>cs;
    while(cs--) {
        solve();
    }
    return 0;
}
