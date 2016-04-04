#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define _ (int)
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

template<size_t N, size_t E, class T, T INFI> class Dinic { //{{{
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
    int new_node() { return ++n; }
    void add_edge(int x, int y, T w1, T w2) {
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
}; //}}}

const int N=10010;

Dinic<N+10, N*6+10, int, 1<<30> net;
int npos, ndot, q;

int cal(int r, int rem) {
    return r/5+(rem<r%5?1:0);
}
int cal(int l, int r, int rem) {
    return cal(r, rem)-cal(l-1, rem);
}

bool solve() {
    scanf("%d%d%d", &ndot,&npos,&q);
    VPI limits;
    rep(i, 1, q) {
        int up, num; scanf("%d%d", &up,&num);
        limits.pb(mp(up, num));
    }
    limits.pb(mp(npos, ndot));
    sort(all(limits));

    net.init();
    int c_re[5];
    repn(i, 5) {
        c_re[i]=net.new_node();
        net.add_edge(net.s(), c_re[i], ndot/5, 0);
    }
    repn(i, limits.size()) {
        int l=(i==0?1:limits[i-1].fi+1), r=limits[i].fi;
        int num=limits[i].se-(i==0?0:limits[i-1].se);
        if(num<0) return false;
        int c_cur=net.new_node();
        net.add_edge(c_cur, net.t(), num, 0);
        repn(k, 5) {
            int w=cal(l, r, k); if(w==0) continue;
            net.add_edge(c_re[k], c_cur, w, 0);
            /*
            int x=net.new_node();
            net.add_edge(c_re[k], x, w, 0);
            net.add_edge(x, c_cur, 
            */
        }
    }

    int ans=net.compute();
    return ans==ndot;
}

int main() {
    printf("%s\n", solve()?"fair":"unfair");
    return 0;
}
