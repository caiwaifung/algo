#include <map>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

const int N=100010;

template<size_t N, size_t E, class T, T INFI> class Dinic2 {
public:
    struct Edge {
        int y;  T w;
        Edge *next, *oppo;
    } edges[E*6];
    Edge *g[N], *ce[N], *super_e;
    int e_cnt, n, src, dst, super_src, super_dst;
    T super_out, tot_lw;

    int d[N], q[N];
    bool build(int s, int t) {
        memset(d, 0, sizeof(d)); d[q[1]=s]=1;
        for(int ss=0, tt=1; ss<tt; ) {
            int x=q[++ss];
            for(Edge *e=ce[x]=g[x]; e; e=e->next)
                if(e->w>0 && d[e->y]==0) d[q[++tt]=e->y]=d[x]+1;
        }
        return d[t]>0;
    }
    T find(int x, int t, T rest) {
        //printf("find x=%d t=%d r=%d\n",x,t,rest);
        if(x==t) return rest;
        T ans=0;
        for(Edge *&e=ce[x]; e; e=e->next)
            if(e->w>0 && d[e->y]>d[x]) {
                T cur=find(e->y, t, min(e->w,rest));
                e->w-=cur; e->oppo->w+=cur;
                ans+=cur; rest-=cur;
                if(rest==0) break;
            }
        return ans;
    }
    const Edge* add(int x, int y, T w1, T w2) {
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
        e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
        e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
        return e2;
    }
    T getOut(int x) {
        T ans=0;
        for(Edge *e=g[x]; e; e=e->next)
            if(e!=super_e->oppo) {
                //if(e->oppo->w) printf("getOut: x=%d y=%d w=%d\n",x,e->y,e->oppo->w);
                ans+=e->oppo->w;
            }
        return ans;
    }
public:
    Dinic2() { init(); }
    int s() { return src; }
    int t() { return dst; }
    void init() {
        memset(g, 0, sizeof(g)); e_cnt=0;
        n=4, src=1, dst=2, super_src=3, super_dst=4;
        super_out=0; tot_lw=0;
        add(dst, src, INFI, 0);
        super_e=&edges[e_cnt-2];
    }
    int new_node() { return ++n; }
    const Edge* add_edge(int x, int y, T lower_w, T upper_w) {
        //printf("%d->%d %d %d\n",x,y,int(lower_w),int(upper_w));
        if(lower_w>0) {
            add(super_src, y, lower_w, 0);
            add(x, super_dst, lower_w, 0);
            super_out+=lower_w;
            if(x==src) tot_lw+=lower_w;
        }
        return add(x, y, upper_w-lower_w, 0);
    }
    T compute_max() {
        while(build(super_src, super_dst)) find(super_src, super_dst, INFI);
        //printf("super_out=%d out=%d\n",super_out,getOut(super_src));fflush(stdout);
        if(getOut(super_src)!=super_out)
            return -1;
        while(build(src, dst)) find(src, dst, INFI);
        //printf("tot_lw=%d out=%d\n",tot_lw,getOut(src));
        T ans=getOut(src);
        return ans;
    }
    bool has_flow(const Edge* e) { return e->w>0; }
};

Dinic2<N, N*10, int, 1<<30> net;

int main() {
    map<int, int> lim_x, lim_y;
    int n, m; scanf("%d%d", &n,&m);
    int r, b; scanf("%d%d", &r,&b);
    bool rb_rev=false; if(r>b) rb_rev=true, swap(r, b);
    static PII points[N]; bool anscolor[N];
    rep(i, 1, n) {
        int x, y; scanf("%d%d", &x,&y);
        points[i]=mp(x, y);
    }
    rep(i, 1, m) {
        int t, l, d; scanf("%d%d%d", &t,&l,&d);
        if(t==1) {
            if(lim_x.count(l)) setmin(lim_x[l], d);
            else lim_x[l]=d;
        } else {
            if(lim_y.count(l)) setmin(lim_y[l], d);
            else lim_y[l]=d;
        }
    }
    map<int, VI> cnt_x, cnt_y, free_x, free_y;
    int ans=0;
    rep(i, 1, n) {
        bool has_x=lim_x.count(points[i].fi)>0;
        bool has_y=lim_y.count(points[i].se)>0;
        if(!has_x && !has_y) { ans+=1; anscolor[i]=true; continue; }
        if(has_x && !has_y) { free_x[points[i].fi].pb(i); continue; }
        if(!has_x && has_y) { free_y[points[i].se].pb(i); continue; }
        cnt_x[points[i].fi].pb(i), cnt_y[points[i].se].pb(i);
    }

    map<int, int> ix, iy;
    net.init();
    static const decltype(net)::Edge* es[N];
    fillchar(es, 0);
    for(const auto& kv: lim_x) ix[kv.fi]=net.new_node();
    for(const auto& kv: lim_y) iy[kv.fi]=net.new_node();
    repn(tt, 2) {
        auto& lim=(tt==0?lim_x:lim_y);
        auto& cnt=(tt==0?cnt_x:cnt_y);
        auto& free=(tt==0?free_x:free_y);
        for(const auto& kv: lim) {
            const int c=sz(cnt[kv.fi]), f=sz(free[kv.fi]);
            const int tot=c+f, lbound=max(0,(tot-kv.se+1)/2), rbound=tot-lbound;
            //printf("tt=%d,v=%d c=%d f=%d [%d,%d]\n",tt,kv.fi,c,f,lbound,rbound);
            if(lbound>rbound) { printf("-1\n"); return 0; }
            if(tt==0) {
                const int x=ix[kv.fi];
                net.add_edge(net.s(), x, lbound, rbound);
                for(int i: free[kv.fi]) {
                    es[i]=net.add_edge(x, net.t(), 0, 1);
                }
                for(int i: cnt[kv.fi]) {
                    const int y=iy[points[i].se];
                    es[i]=net.add_edge(x, y, 0,1);
                }
            } else {
                const int y=iy[kv.fi];
                net.add_edge(y, net.t(), lbound, rbound);
                for(int i: free[kv.fi]) {
                    es[i]=net.add_edge(net.s(), y, 0,1);
                }
            }
        }
    }
    int tmp=net.compute_max();
    if(tmp<0) { printf("-1\n"); return 0; }
    ans+=tmp;
    rep(i, 1, n) if(es[i]!=nullptr) anscolor[i]=net.has_flow(es[i]);
    //printf("ans=%d\n",ans);
    printf("%lld\n", ans*LL(r)+(n-ans)*LL(b));
    rep(i, 1, n) printf("%c", (anscolor[i]^rb_rev)?'r':'b');

    return 0;
}
