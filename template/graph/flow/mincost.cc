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
    int newNode() { return ++n; }
    void addEdge(int x, int y, T w, T c) {
        //printf("add %d %d %d %d\n",x,y,w,c);
        Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
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
