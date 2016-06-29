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
    void init(int n_, int s, int t) {
        memset(g, 0, sizeof(g)); e_cnt=0;
        n=n_, src=s, dst=t;
    }
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

const int N=55;
const int M=555;

int a[M], b[M], c[M], n, m, x;
Dinic<N, M, int, 1<<30> net;

bool check(double each) {
    net.init(n, 1, n);
    rep(i, 1, m) {
        int w=0;
        if(c[i]>x*each) w=x+1;
        else w=int(c[i]/each);
        net.add_edge(a[i], b[i], w, 0);
    }
    return net.compute()>=x;
}

int main() {
    scanf("%d%d%d", &n,&m,&x);
    rep(i, 1, m) scanf("%d%d%d", &a[i],&b[i],&c[i]);
    double le=0, ri=1000000;
    repn(tt, 199) {
        double mid=(le+ri)/2;
        if(check(mid)) le=mid;
            else ri=mid;
    }
    printf("%.9lf\n", le*x);
    return 0;
}
