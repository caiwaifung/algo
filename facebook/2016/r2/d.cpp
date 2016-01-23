#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//{{{
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
template<class T> T absv(T _x) { return _x>0?_x:-_x; }
//}}}

//{{{
template<size_t N, size_t E, class T> class MinCostFlow {
    struct Edge {
        int y; T c, w;
        Edge *next, *oppo;
    } edges[E*2];
    Edge *g[N];
    int e_cnt, n, src, dst;

    bool inside[N];
    Edge *pre[N];
    int q[N];
    T d[N];
public:
    MinCostFlow() { init(); }
    int s() { return src; }
    int t() { return dst; }
    void init() {
        memset(g, 0, sizeof(g)); e_cnt=0;
        n=2, src=1, dst=2;
    }
    int new_node() { assert(n<N); return ++n; }
    void add_edge(int x, int y, T w, T c) {
        //printf("add %d %d %d %d\n",x,y,w,c);
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
        assert(e_cnt<E);
        e1->y=y, e1->c=+c, e1->w=w, e1->oppo=e2, e1->next=g[x], g[x]=e1;
        e2->y=x, e2->c=-c, e2->w=0, e2->oppo=e1, e2->next=g[y], g[y]=e2;
    }
    pair<T,T> compute() {
        T flow=0, cost=0;
        while(1) {
            memset(pre, 0, sizeof(pre));
            memset(d, 100, sizeof(d));
            memset(inside, false, sizeof(inside));
            int ss=0, tt=1;
            q[1]=src, d[src]=0, inside[src]=true;
            while(ss!=tt) {
                if(++ss==N) ss=1;
                int x=q[ss]; inside[x]=false;
                for(Edge *e=g[x]; e; e=e->next)
                    if(e->w>0 && d[x]+e->c<d[e->y]) {
                        int y=e->y;
                        d[y]=d[x]+e->c;
                        pre[y]=e;
                        if(!inside[y]) {
                            inside[y]=true;
                            if(++tt==N) tt=1;
                            q[tt]=y;
                        }
                    }
            }
            if(pre[dst]==NULL)
                break;
            T cur=pre[dst]->w;
            for(int y=dst, x; y!=src; y=x) {
                cur=min(cur, pre[y]->w);
                x=pre[y]->oppo->y;
            }
            flow+=cur;
            cost+=cur*d[dst];
            for(int y=dst, x; y!=src; y=x) {
                pre[y]->w-=cur;
                pre[y]->oppo->w+=cur;
                x=pre[y]->oppo->y;
            }
        }
        return make_pair(flow, cost);
    }
};
//}}}

const int MAXN=1010;
const int MAXK=33;

int C[MAXN][MAXK];
VI es[MAXN];
int n, k, P;

void read_input() {
    /*
    n=1000; k=30; P=rand()%100+100;
    rep(i, 1, n) rep(j, 1, k) C[i][j]=rand()%55+55; 
    rep(i, 1, n) es[i].clear();
    rep(i, 2, n) { int j=rand()%(i-1)+1; es[i].pb(j), es[j].pb(i); }//printf("%d - %d\n",i,j);}
    return;
    */

    scanf("%d%d%d", &n,&k,&P);
    rep(i, 1, n) rep(j, 1, k) scanf("%d", &C[i][j]);
    rep(i, 1, n) es[i].clear();
    rep(i, 1, n-1) {
        int x, y; scanf("%d%d", &x,&y);
        es[x].pb(y), es[y].pb(x);
    }
}

LL f[MAXN][MAXK][MAXK];

LL naive(int x, int fa, int c, int) {
    LL ans=C[x][c]+P;
    for(int y: es[x]) if(y!=fa) {
        LL t=1LL<<55;
        rep(i, 1, k) setmin(t, f[y][i][c]);
        ans+=t;
    }
    return ans;
}

LL clever(int x, int fa, int c, int cf) {
    static MinCostFlow<MAXN+MAXK, MAXN*MAXK, LL> net;
    net.init();

    static int ci[MAXK];
    rep(i, 1, k) if(i!=cf) {
        ci[i]=net.new_node(); 
        net.add_edge(ci[i], net.t(), 1, 0);
    } else ci[i]=-1;
    int num=0;
    for(int y: es[x]) if(y!=fa) {
        ++num;
        int p=net.new_node();
        net.add_edge(net.s(), p, 1, 0);
        rep(i, 1, k) if(ci[i]>0)
            net.add_edge(p, ci[i], 1, f[y][i][c]);
    }

    PLL r=net.compute();
    if(r.fi!=num) return 1LL<<55;

    LL ans=r.se;
    ans+=C[x][c];
    return ans;
}

void dfs(int x, int fa) {
    for(int y: es[x]) if(y!=fa) dfs(y, x);
    rep(c, 1, k) rep(cf, 0, k) {
        //printf("%d %d %d\n",x,c,cf);
        f[x][c][cf]=min(naive(x, fa, c, cf), clever(x, fa, c, cf));
    }
}

LL solve() {
    dfs(1, 0);
    LL ans=1LL<<55;
    rep(i, 1, k) setmin(ans, f[1][i][0]);
    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/costly_labels.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        LL ans=solve();
        printf("Case #%d: %lld\n", cs, ans);
    }
    return 0;
}

