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
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

template<size_t N, size_t E, class T, T INFI> class Dinic2 {
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
    void add(int x, int y, T w1, T w2) {
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
        e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
        e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
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
    int newNode() { return ++n; }
    void addEdge(int x, int y, T lower_w, T upper_w) {
        //printf("%d-%d %d %d\n",x,y,lower_w,upper_w);
        add(x, y, upper_w-lower_w, 0);
        if(lower_w>0) {
            add(super_src, y, lower_w, 0);
            add(x, super_dst, lower_w, 0);
        }
        super_out+=lower_w;
        if(x==src) tot_lw+=lower_w;
    }
    T computeMax() {
        while(build(super_src, super_dst)) find(super_src, super_dst, INFI);
        //printf("super_out=%d out=%d\n",super_out,getOut(super_src));fflush(stdout);
        if(getOut(super_src)!=super_out)
            return -1;
        while(build(src, dst)) find(src, dst, INFI);
        //printf("tot_lw=%d out=%d\n",tot_lw,getOut(src));
        T ans=getOut(src);
        return ans;
    }
};

// ------------------------ template ends here ------------------------ //

Dinic2<1010, 1010*1010, int, 1<<28> network;
bool is_e[1010]; int a[1010], must[1010];
int le[1010], ri[1010];
int ids[1010];
int n;

int main() {
    int cases;
    scanf("%d", &cases);
    forint(cs, 1, cases) {
        scanf("%d", &n);
        forint(i, 1, n) {
            char s[9]; scanf("%s%d", s,&a[i]);
            is_e[i]=(s[0]=='E');
        }

        forint(i, 1, n) {
            must[i]=0;
            if(is_e[i]) {
                le[i]=i+1, ri[i]=n;
                if(a[i]!=0) {
                    forint(j, i+1, n) if(is_e[j]==is_e[i] && a[j]==a[i]) {
                        ri[i]=j-1; must[i]=1;
                        break;
                    }
                }
            } else {
                le[i]=1, ri[i]=i-1;
                if(a[i]!=0) {
                    forintdown(j, i-1, 1) if(is_e[j]==is_e[i] && a[j]==a[i]) {
                        le[i]=j+1; must[i]=1;
                        break;
                    }
                }
            }
        }
        network.init();
        forint(i, 1, n) ids[i]=network.newNode();
        int en=0;
        forint(i, 1, n) {
            if(is_e[i]) {
                network.addEdge(network.s(), ids[i], must[i], 1);
                ++en;
            } else
                network.addEdge(ids[i], network.t(), must[i], 1);
        }
        forint(i, 1, n) forint(j, i+1, n)
            if(is_e[i] && !is_e[j]) {
                if(!(le[i]<=j && j<=ri[i])) continue;
                if(!(le[j]<=i && i<=ri[j])) continue;
                if(a[i]==a[j] || a[i]==0 || a[j]==0)
                    network.addEdge(ids[i], ids[j], 0, 1);
            }
        int ans=network.computeMax();
        printf("Case #%d: ", cs);
        if(ans<0) printf("CRIME TIME\n");
            else printf("%d\n", en-ans);
//break;
    }
    return 0;
}
