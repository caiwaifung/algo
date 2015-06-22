// 14:48 - 15:23
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

template<size_t N, size_t E, class T, T INFI> class Dinic {
    struct Edge {
        int y;  T w;
        Edge *next, *oppo;
    } edges[E*2];
    Edge *g[N], *ce[N];
    int e_cnt, n, src, dst;

    int d[N], q[N];
    bool build() {
        memset(d, 0, sizeof(d)); d[q[1]=src]=1;
        for(int ss=0, tt=1; ss<tt; ) {
            int x=q[++ss];
            for(Edge *e=ce[x]=g[x]; e; e=e->next)
                if(e->w>0 && d[e->y]==0) d[q[++tt]=e->y]=d[x]+1;
        }
        return d[dst]>0;
    }
    T find(int x, T rest) {
        if(x==dst) return rest;
        T ans=0;
        for(Edge *&e=ce[x]; e; e=e->next)
            if(e->w>0 && d[e->y]>d[x]) {
                T cur=find(e->y, min(e->w,rest));
                e->w-=cur; e->oppo->w+=cur;
                ans+=cur; rest-=cur;
                if(rest==0) break;
            }
        return ans;
    }
public:
    Dinic() { init(); }
    int s() { return src; }
    int t() { return dst; }
    void init() {
        memset(g, 0, sizeof(g)); e_cnt=0;
        n=2, src=1, dst=2;
    }
    int new_node() { assert(n+5<(int)N); return ++n; }
    void add_edge(int x, int y, T w1, T w2) {
        assert(e_cnt+5<(int)E);
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
        e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
        e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
    }
    T compute() {
        T ans=0; while(build()) ans+=find(src, INFI); return ans;
    }
    T get(int x, int y) {
        for(Edge *e=g[x]; e; e=e->next)
            if(e->y==y)
                return e->oppo->w;
        return 0;
    }
    vector<bool> get_left() {
        build();
        vector<bool> ans(n+1);
        for(int i=1; i<=n; ++i) ans[i]=(d[i]>0);
        return ans;
    }
};

int a[310][310], b[310][310];
int pos[310], ans[310];
int n, m;
LL tot_val;

Dinic<100*200+100, 500*10000, LL, 1LL<<60> net;

void solve() {
    PII ip[310];
    rep(i, 1, n) ip[i]=mp(pos[i], i);
    sort(ip+1, ip+n+1);
    rep(i, 1, n) pos[i]=ip[i].fi; pos[0]=0;
    //sort(pos+1, pos+n+1); pos[0]=0;

    int ia[310][310], ib[310][310];
    net.init();
    rep(i, 1, n) {
        ia[i][0]=net.s(), ia[i][n]=net.t();
        rep(j, 1, n-1) ia[i][j]=net.new_node();
        rep(j, 1, n) if(j!=i) 
            net.add_edge(ia[i][j-1], ia[i][j], 1LL<<55, 0);
    }
    rep(i, 1, m) {
        ib[i][0]=net.s(), ib[i][n]=net.t();
        rep(j, 1, n-1) ib[i][j]=net.new_node();
        rep(j, 1, n)
            net.add_edge(ib[i][j-1], ib[i][j], 0, 1LL<<55);
    }
    rep(i, 1, n) rep(j, 1, m) {
        rep(k, 1, n-1) {
            LL v=(LL)(pos[k+1]-pos[k])*(LL)a[ip[i].se][j];
            //cout<<"i="<<i<<" j="<<j<<" k="<<k<<" v="<<v<<endl;
            net.add_edge(ia[i][k], ib[j][k], v, v);
        }
    }
    rep(i, 1, m) rep(j, i+1, m) {
        rep(k, 1, n-1) {
            LL v=(LL)(pos[k+1]-pos[k])*(LL)b[i][j];
            net.add_edge(ib[i][k], ib[j][k], v, v);
        }
    }

    LL val=net.compute();
    tot_val+=val;
    //cout<<"val="<<val<<endl;

    vector<bool> left=net.get_left();
    rep(i, 1, m) {
        int cnt=0;
        rep(j, 1, n) if(left[ib[i][j-1]] && !left[ib[i][j]]) {
            //cout<<"select "<<j<<endl;
            ++cnt;
            ans[i]=pos[j];
        }
        assert(cnt==1);
    }
}

int main() {
    static int px[310], py[310];
    scanf("%d%d", &n,&m);
    rep(i, 1, n) scanf("%d%d", &px[i],&py[i]);
    rep(i, 1, n) rep(j, 1, m) scanf("%d", &a[i][j]);
    rep(i, 1, m-1) rep(j, i+1, m) scanf("%d", &b[i][j]);

    tot_val=0;
    static int qx[310], qy[310];
    memmove(pos, px, sizeof(pos));
    solve();
    memmove(qx, ans, sizeof(ans));
    memmove(pos, py, sizeof(pos));
    solve();
    memmove(qy, ans, sizeof(ans));

    LL val=0;
    rep(i, 1, n) rep(j, 1, m) {
        LL d=abs(px[i]-qx[j])+abs(py[i]-qy[j]);
        val+=d*(LL)a[i][j];
    }
    rep(i, 1, m) rep(j, i+1, m) {
        LL d=abs(qx[i]-qx[j])+abs(qy[i]-qy[j]);
        val+=d*(LL)b[i][j];
    }
    cout<<val<<endl;
    cout<<tot_val<<endl;

    return 0;
}
