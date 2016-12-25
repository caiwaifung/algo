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

const int N=50000;

VPI es[N];
int n;

struct Op {
    char type;
    int a, b, c;
};
vector<Op> ops;

int vis[N], low[N], dfn[N], label;
bool own[N];

void pre_dfs(int x, int fe) {
    low[x]=dfn[x]=label++;
    vis[x]=1; own[x]=false;
    for(const auto& e: es[x]) if(e.se!=fe) {
        if(vis[e.fi]==0) {
            pre_dfs(e.fi, e.se);
            if(setmin(low[x], low[e.fi])) {
                own[x]=false;
            }
        } else {
            if(setmin(low[x], dfn[e.fi])) {
                own[x]=true;
            }
        }
    }
}

void dfs(int x) {
    vis[x]=1;
    int special_y=-1;
    for(const auto& e: es[x]) if(vis[e.fi]==0) {
        if(low[e.fi]<dfn[x]) {
            special_y=e.fi;
            continue;
        }
        dfs(e.fi);
        if(low[e.fi]==dfn[x]) {
            ops.pb({'r', e.fi, 1, 3});
            ops.pb({'j', e.fi, x, 0});
            ops.pb({'c', x, 1, 3});
            ops.pb({'r', x, 3, 4});
            if(!own[e.fi]) {
                ops.pb({'c', x, 1, 2});
                ops.pb({'r', x, 2, 4});
            }
        } else {
            ops.pb({'r', e.fi, 1, 3});
            ops.pb({'j', e.fi, x, 0});
            ops.pb({'c', x, 1, 3});
            ops.pb({'r', x, 3, 4});
        }
    }
    if(special_y>=0) {
        dfs(special_y);
        ops.pb({'r', special_y, 1, 3});
        ops.pb({'j', special_y, x, 0});
        ops.pb({'c', x, 1, 3});
        if(own[special_y]) {
            ops.pb({'r', x, 3, 2});
        } else {
            ops.pb({'r', x, 3, 4});
        }
    }
}

int main() {
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);
    int m, id=0;
    scanf("%d%d", &n,&m);
    while(m--) {
        int k; scanf("%d", &k);
        int x; scanf("%d", &x); --x;
        --k;
        while(k--) {
            int y; scanf("%d", &y); --y;
            es[x].pb(mp(y, id)), es[y].pb(mp(x, id));
            id++;
            x=y;
        }
    }

    fillchar(vis, 0);
    label=0;
    pre_dfs(0, -1);

    fillchar(vis, 0);
    dfs(0);

    printf("%d\n", sz(ops));
    for(const auto& op: ops) {
        if(op.type=='j') {
            printf("j %d %d\n", op.a+1, op.b+1);
        } else {
            printf("%c %d %d %d\n", op.type, op.a+1, op.b, op.c);
        }
    }
    return 0;
}
