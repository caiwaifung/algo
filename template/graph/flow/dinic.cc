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
    void addEdge(int x, int y, T w1, T w2) {
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
        e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
        e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
    }
    T compute() {
        T ans=0; while(build()) ans+=find(src, INFI); return ans;
    }
    T getFlow(int x, int y) {
        for(Edge *e=g[x]; e; e=e->next)
            if(e->y==y)
                return e->oppo->w;
        return 0;
    }
};
