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