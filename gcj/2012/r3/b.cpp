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

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
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

int n, m;
PII moves[10010];

void init() {
    scanf("%d%d", &n,&m);
    forint(i, 1, m) scanf("%d%d", &moves[i].fi,&moves[i].se);

    set<PII> tmp(moves+1, moves+m+1);
    assert(tmp.size()==(size_t)m);
}

bool inside(int x, int y) {
    if(x<1) return false;
    if(y<1) return false;
    if(x>2*n-1) return false;
    if(y>2*n-1) return false;
    if(x>y+n-1) return false;
    if(y>x+n-1) return false;
    return true;
}
bool inside(PII p) { return inside(p.fi, p.se); }

int on_cornor(int x, int y) {
    if(x==1 && y==1) return 0;
    if(x==n && y==1) return 1;
    if(x==2*n-1 && y==n) return 2;
    if(x==2*n-1 && y==2*n-1) return 3;
    if(x==n && y==2*n-1) return 4;
    if(x==1 && y==n) return 5;
    return -1;
}
int on_edge(int x, int y) {
    if(on_cornor(x, y)>=0) return -1;
    if(y==1) return 0;
    if(y+n-1==x) return 1;
    if(x==2*n-1) return 2;
    if(y==2*n-1) return 3;
    if(x+n-1==y) return 4;
    if(x==1) return 5;
    return -1;
}

int f[6060*6060];
int lab[6060*6060];
bool vis[6060*6060];
int gf(int x) {
    return f[x]==0?x:(f[x]=gf(f[x]));
}
void unite(int x, int y) {
    x=gf(x), y=gf(y);
    if(x!=y) {
        f[x]=y;
        lab[y]|=lab[x];
    }
}
int id(int x, int y) {
    return x*6060+y;
}
int bitcnt(int x) {
    return x==0?0:((x&1)+bitcnt(x>>1));
}

const int dx[6]={0, 1, 0, -1, 1, -1};
const int dy[6]={1, 0, -1, 0, 1, -1};

PII solve1() { // bridge & fork
    fillchar(f, 0);
    fillchar(lab, 0);
    fillchar(vis, false);
    forint(i, 1, m) {
        int x=moves[i].fi, y=moves[i].se;
        int cornor=on_cornor(x, y);
        if(cornor>=0)
            lab[id(x,y)]|=(1<<cornor);
        int edge=on_edge(x, y);
        if(edge>=0)
            lab[id(x,y)]|=(1<<(edge+6));
        vis[id(x, y)]=true;
        forn(k, 6) {
            int x0=x+dx[k], y0=y+dy[k];
            if(!inside(x0, y0)) continue;
            if(!vis[id(x0, y0)]) continue;
            unite(id(x, y), id(x0, y0));
        }

        int cur=lab[gf(id(x, y))];
        bool has_bridge=(bitcnt(cur&((1<<6)-1))>=2);
        bool has_fork=(bitcnt(cur>>6)>=3);
        if(has_bridge || has_fork) {
            PII ans=MP(0,0);
            if(has_bridge) ans.fi=i;
            if(has_fork) ans.se=i;
            return ans;
        }
    }
    return MP(0,0);
}

int alone_cnt;

void put(int x, int y) {
    int i=id(x, y);
    vis[i]=true;
    lab[i]=1; if(on_cornor(x, y)>=0 || on_edge(x, y)>=0) lab[i]=0;
    alone_cnt+=lab[i];
    forn(k, 6) {
        int x0=x+dx[k], y0=y+dy[k];
        if(!inside(x0, y0)) continue;
        if(!vis[id(x0, y0)]) continue;
        int j=id(x0, y0);
        i=gf(i), j=gf(j);
        if(i!=j) {
            alone_cnt-=lab[i];
            alone_cnt-=lab[j];
            f[i]=j, lab[j]&=lab[i];
            alone_cnt+=lab[j];
        }
    }
}

int solve2() { // ring
    fillchar(vis, false);
    forint(i, 1, m) vis[id(moves[i].fi, moves[i].se)]=true;
    vector<PII> full;
    forint(i, 1, n*2) forint(j, 1, n*2) if(inside(i, j)) {
        if(!vis[id(i,j)]) full.PB(MP(i, j));
    }

    fillchar(f, 0);
    fillchar(lab, 0);
    fillchar(vis, false);
    alone_cnt=0;
    for(PII p: full) put(p.fi, p.se);
    int first=0;
    if(alone_cnt>0) first=m;
    forintdown(i, m, 1) {
        put(moves[i].fi, moves[i].se);
        if(alone_cnt>0) first=i-1;
    }

    return first;
}

void solve(int cs) {
    PII a1=solve1();
    int a2=solve2();
    int ans=m+1;
    if(a1.fi>0) setmin(ans, a1.fi);
    if(a1.se>0) setmin(ans, a1.se);
    if(a2>0) setmin(ans, a2);

    printf("Case #%d: ", cs);
    if(ans<=m) {
        VS t;
        if(a1.fi==ans) t.PB("bridge");
        if(a1.se==ans) t.PB("fork");
        if(a2==ans) t.PB("ring");
        forn(i, t.size()) {
            if(i>0) printf("-");
            printf("%s", t[i].c_str());
        }
        printf(" in move %d\n", ans);
    }
    else printf("none\n");
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
