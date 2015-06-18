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
#define rep2(i, n) rep(i, 0, (n)-1)
#define irep2(i, n) irep(i, (n)-1, 0)
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

const int MAXN=300010;
const int MAXLEN=MAXN*2;
const int MAXLogN=20;

VI es[MAXN];
char chs[MAXN];
int n;

int fa[MAXN], size[MAXN], dep[MAXN], up[MAXN][MAXLogN];
void dfs(int x, int f, int d) {
    fa[x]=f;
    dep[x]=d;

    fillchar(up[x], 0);
    up[x][0]=fa[x];
    for(int i=0; up[x][i]>0; ++i)
        up[x][i+1]=up[up[x][i]][i];

    size[x]=1;
    for(int y: es[x]) if(y!=fa[x]) {
        dfs(y, x, d+1);
        size[x]+=size[y];
    }
}

int head[MAXN], seq[MAXN], ind[MAXN], tot;
void dfs2(int x, int h) {
    int ymax=0;
    for(int y: es[x]) if(y!=fa[x])
        if(ymax==0 || size[y]>size[ymax])
            ymax=y;
    for(int y: es[x]) if(y!=fa[x] && y!=ymax)
        dfs2(y, y);
    if(ymax>0)
        dfs2(ymax, h);
    ++tot;
    seq[tot]=x;
    ind[x]=tot;
    head[x]=h;
}

int go_up(int x, int d) {
    irep2(i, MAXLogN) if(d&(1<<i)) x=up[x][i];
    return x;
}

int lca(int x, int y) {
    irep2(i, MAXLogN) {
        if(up[x][i]>0 && dep[up[x][i]]>=dep[y])
            x=up[x][i];
        if(up[y][i]>0 && dep[up[y][i]]>=dep[x])
            y=up[y][i];
    }
    irep2(i, MAXLogN)
        if(up[x][i]!=up[y][i]) {
            x=up[x][i];
            y=up[y][i];
        }
    if(x!=y) {
        x=fa[x];
        y=fa[y];
    }
    assert(x==y && x!=0);
    return x;
}

namespace SA { //{{{
int sa[MAXLEN], rank[MAXLEN], height[MAXLEN], limit[MAXLEN];
int wxa[MAXLEN], wxb[MAXLEN], wxc[MAXLEN];
char str[MAXLEN];
int len;
void cal_sa() {
    int *x=wxa, *y=wxb, *c=wxc, size=256;
    for(int i=0; i<=size; ++i) c[i]=0; //memset
    for(int i=1; i<=len; ++i) ++c[x[i]=(int)str[i]];
    for(int i=1; i<=size; ++i) c[i]+=c[i-1];
    for(int i=len; i>=1; --i) sa[c[x[i]]--]=i;

    for(int w=1; w<len; w*=2, size=len) {
        int p=0;
        for(int i=len-w+1; i<=len; ++i) y[++p]=i;
        for(int i=1; i<=len; ++i) if(sa[i]>w) y[++p]=sa[i]-w;

        for(int i=0; i<=size; ++i) c[i]=0; //memset
        for(int i=1; i<=len; ++i) ++c[x[i]];
        for(int i=1; i<=size; ++i) c[i]+=c[i-1];
        for(int i=len; i>=1; --i) sa[c[x[y[i]]]--]=y[i];
        std::swap(x, y); x[sa[1]]=1;
        for(int i=2; i<=len; ++i) {
            int j1=sa[i-1], j2=sa[i];
            int c1=y[j1], c2=y[j2];
            if(c1==c2) {
                c1=(j1+w<=len?y[j1+w]:0);
                c2=(j2+w<=len?y[j2+w]:0);
            }
            x[j2]=x[j1]+(c1<c2);
        }
    }
}
void cal_height() {
    for(int i=1; i<=len; ++i) rank[sa[i]]=i;
    for(int i=1, h=0; i<=len; ++i) {
        if(h>0) --h;
        int j=sa[rank[i]-1];
        while(i+h<=len && j+h<=len && str[i+h]==str[j+h])
            ++h;
        height[rank[i]]=h;
    }
}

int lcp_st[MAXLogN][MAXLEN];
int lcp_k[MAXLEN], lcp_w[MAXLEN];
void cal_lcp() {
    for(int i=2; i<=len; ++i) lcp_st[0][i]=height[i];
    for(int k=1, w=1; 2+w<=len; ++k, w*=2)
        for(int i=2; i+w<=len; ++i)
            lcp_st[k][i]=min(lcp_st[k-1][i], lcp_st[k-1][i+w]);
    for(int i=1, k=0, w=1; i<=len; ++i) {
        while(w*2<=i) w*=2, ++k;
        lcp_k[i]=k, lcp_w[i]=w;
    }
}
int lcp(int i, int j) {
    if(i==j) return limit[i];
    i=rank[i], j=rank[j]; if(i>j) swap(i, j);
    ++i;
    int k=lcp_k[j-i+1], w=lcp_w[j-i+1];
    return min(lcp_st[k][i], lcp_st[k][j-w+1]);
}

}; //}}}

void preprocess() {
    dfs(1, 0, 1);
    dfs2(1, 1);

    SA::len=n*2+1;
    rep(i, 1, n) SA::str[i]=chs[seq[i]];
    SA::str[n+1]='*';
    rep(i, 1, n) SA::str[n+1+i]=chs[seq[n-i+1]];
    rep(i, 1, SA::len) SA::limit[i]=SA::len-i+1;

    SA::cal_sa();
    SA::cal_height();
    SA::cal_lcp();
}

VPI extract_direct_path(int x, int y) {
    VPI p;
    while(1) {
        int z=head[x];
        if(dep[z]<dep[y])
            z=y;
        p.pb(mp(x, z));
        if(z==y) break;
        x=fa[z];
    }
    return p;
}

VPI extract_path(int x, int y) {
    int z=lca(x, y);
    VPI px, py;
    px=extract_direct_path(x, z);
    if(y!=z)
        py=extract_direct_path(y, go_up(y, dep[y]-dep[z]-1));
    reverse(all(py));
    for(PII &p: py) swap(p.fi, p.se);
    px.insert(px.end(), all(py));
    for(PII p: px) assert(head[p.fi]==head[p.se]);
    return px;
}

int path_len(PII p) { int d=dep[p.fi]-dep[p.se]; if(d<0) d=-d; return d+1; }
bool take_subpath(PII &p, PII &q, int len) {
    if(len==path_len(p)) { q=p; return false; }
    if(dep[p.fi]>dep[p.se]) {
        int z=seq[ind[p.fi]+len-1];
        q=mp(p.fi, z);
        p=mp(fa[z], p.se);
    }
    else {
        int z=seq[ind[p.fi]-len+1];
        q=mp(p.fi, z);
        p=mp(seq[ind[p.fi]-len], p.se);
    }
    return true;
}

void sync_paths(VPI &p1, VPI &p2) {
    VPI new_p1, new_p2;
    size_t i=0, j=0;
    while(i<p1.size() && j<p2.size()) {
        int lu=path_len(p1[i]);
        int lv=path_len(p2[j]);
        int len=min(lu, lv);
        PII z1, z2;
        if(!take_subpath(p1[i], z1, len)) ++i;
        if(!take_subpath(p2[j], z2, len)) ++j;
        new_p1.pb(z1);
        new_p2.pb(z2);
    }
    p1=new_p1;
    p2=new_p2;
    //printf("done."); exit(1);
}

int query(int x1, int y1, int x2, int y2) {
    VPI p1=extract_path(x1, y1);
    VPI p2=extract_path(x2, y2);
    sync_paths(p1, p2);
    assert(p1.size()==p2.size());
    int ans=0;
    //rep(i, 1, n) printf("ind[%d]=%d ",i,ind[i]); printf("\n");
    rep2(i, p1.size()) {
        assert(path_len(p1[i])==path_len(p2[i]));
        int len=path_len(p1[i]);
        int x=p1[i].fi, xz=p1[i].se;
        int y=p2[i].fi, yz=p2[i].se;
        int ix=(dep[x]>=dep[xz] ? ind[x] : 2*n+1-ind[x]+1);
        int iy=(dep[y]>=dep[yz] ? ind[y] : 2*n+1-ind[y]+1);
        int lcp=SA::lcp(ix, iy);
        //printf("x=%d y=%d ix=%d iy=%d\n",x,y,ix,iy);
        if(lcp<len) {
            ans+=lcp; break;
        }
        ans+=len;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    scanf("%s", chs+1);
    rep(i, 1, n) es[i].clear();
    rep(i, 1, n-1) {
        int a, b; scanf("%d%d", &a,&b);
        es[a].pb(b);
        es[b].pb(a);
    }

    preprocess();

    int q; scanf("%d", &q);
    while(q--) {
        int a, b, c, d; scanf("%d%d%d%d", &a,&b,&c,&d);
        int ans=query(a, b, c, d);
        printf("%d\n", ans);
    }
    return 0;
}
