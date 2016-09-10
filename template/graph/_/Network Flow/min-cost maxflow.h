template<size_t N, size_t E> class MinCostMaxFlow {
	struct Edge {
		int y;
		LL w, cost;
		Edge *oppo, *next;
	} edges[E*2];
	Edge* g[N];
	LL w[N], dist[N]; Edge *pe[N];
	int q[N]; bool inside[N];
	int n, src, dst, e_cnt;
public:
	LL max_flow, min_cost;
	void initialize(int _n, int s, int t) {
		n=_n, src=s, dst=t;
		memset(g, 0, sizeof(g));
		e_cnt=0;
	}
	void add_edge(int x, int y, LL w, LL c) {
		Edge *e1=&edges[e_cnt++];
		Edge *e2=&edges[e_cnt++];
		e1->y=y, e1->w=w, e1->cost=c, e1->oppo=e2, e1->next=g[x], g[x]=e1;
		e2->y=x, e2->w=0, e2->cost=-c, e2->oppo=e1, e2->next=g[y], g[y]=e2;
	}
	void compute() {
		LL INFI; memset(&INFI, 100, sizeof(INFI));
		max_flow=min_cost=0;
		while(1) {
			int ss=0, tt=1;
			memset(dist, 100, sizeof(dist));
			memset(inside, false, sizeof(inside));
			q[tt]=src;
			dist[src]=0; w[src]=INFI; inside[src]=true;
			while(ss!=tt) {
				if(++ss==N) ss=1;
				int x=q[ss];
				for(Edge *e=g[x]; e!=NULL; e=e->next)
					if(e->w>0 && dist[x]+e->cost<dist[e->y]) {
						dist[e->y]=dist[x]+e->cost;
						w[e->y]=min(w[x], e->w);
						pe[e->y]=e;
						if(!inside[e->y]) {
							if(++tt==N) tt=1;
							inside[q[tt]=e->y]=true;
						}
					}
				inside[x]=false;
			}
			if(dist[dst]==INFI) break;
			LL cur=w[dst];
			max_flow+=cur;
			min_cost+=cur*dist[dst];
			for(int x=dst; x!=src; x=pe[x]->oppo->y)
				pe[x]->w-=cur, pe[x]->oppo->w+=cur;
		}
	}
};
