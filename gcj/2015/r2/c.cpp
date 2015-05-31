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
    int newNode() { return ++n; }
    void add(int x, int y, T w1, T w2) {
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
        e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
        e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
    }
    T compute() {
        printf("%d %d\n",e_cnt, (int)E);
        printf("%d %d\n",n, (int)N);
        T ans=0; while(build()) ans+=find(src, INFI); return ans;
    }
    T getFlow(int x, int y) {
        for(Edge *e=g[x]; e; e=e->next)
            if(e->y==y)
                return e->oppo->w;
        return 0;
    }
};

Dinic<10010, 99999, int, 1<<30> net;
VI a[222];
int n, wn;
map<string, int> words;

int word_id(string w) {
    if(words.find(w)==words.end())
        words[w]=++wn;
    int ans=words[w];
    //printf("id[%s]->%d\n",w.c_str(),ans);
    return ans;
}

void init() {
    wn=0; words.clear();
    static char buf[99999];
    scanf("%d", &n); fgets(buf, 99990, stdin);
    forint(i, 1, n) {
        a[i].clear();
        fgets(buf, 99990, stdin);
        string cur(buf);
        while(cur.size()>0 && (cur.back()=='\n' || cur.back()=='\r')) cur.pop_back();
        cur+=' ';
        string tmp="";
        //cout<<cur<<"|"<<endl;
        for(auto ch: cur) {
            if(ch==' ') {
                if(tmp!="") {
                    a[i].PB(word_id(tmp));
                    tmp="";
                }
            }
            else tmp+=ch;
        }
    }

    /*
    forint(i, 1, n) {
        printf("i=%d:",i);
        for(auto k:a[i]) printf(" %d", k); printf("\n");
    }
    */
}

int wx[99999], wy[99999], sen[999];

void solve(int cs) {
    int F=1<<26;
    net.init();
    forint(i, 1, wn) {
        wx[i]=net.newNode();
        wy[i]=net.newNode();
    }
    forint(i, 1, n)
        sen[i]=net.newNode();
    net.add(net.s(), sen[1], F, 0);
    net.add(sen[2], net.t(), F, 0);
    forint(i, 1, n) {
        for(int k: a[i]) {
            net.add(sen[i], wx[k], F,0);
            net.add(wy[k], sen[i], F,0);
        }
    }
    forint(i, 1, wn)
        net.add(wx[i], wy[i], 1,0);
    int ans=net.compute();
    printf("Case #%d: ", cs);
    printf("%d\n", ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
