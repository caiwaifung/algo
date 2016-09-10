template<size_t N, size_t E> class MaxFlow {
	struct Edge {
		int y;  LL w;
		Edge *next, *oppo;
	} edges[E*2];
	int e_cnt;
    	Edge *g[N], *ce[N];
	int n, src, dst;
	
	int d[N], q[N];
	bool build() {
		memset(d, 0, sizeof(d));
		d[q[1]=src]=1;
		for(int ss=0, tt=1; ss<tt; ) {
			int x=q[++ss];
			for(Edge *e=ce[x]=g[x]; e!=NULL; e=e->next)
				if(e->w>0 && d[e->y]==0)
					d[q[++tt]=e->y]=d[x]+1;
		}
		return d[dst]>0;
	}
	LL find(int x, LL rest) {
		if(x==dst) return rest;
		LL ans=0;
		for(Edge *&e=ce[x]; e!=NULL; e=e->next)
			if(e->w>0 && d[e->y]>d[x]) {
				LL cur=find(e->y, min(e->w,rest));
				e->w-=cur; e->oppo->w+=cur;
				ans+=cur; rest-=cur;
				if(rest==0) break;
			}
		return ans;
	}

public:
	void initialize(int _n, int _s, int _t) {
		n=_n, src=_s, dst=_t;
		memset(g, 0, sizeof(g));
		e_cnt=0;
	}
	void add_edge(int x, int y, LL w1, LL w2) {
		Edge *e1=&edges[e_cnt++];
		Edge *e2=&edges[e_cnt++];
		e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
		e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
	}
	LL compute() {
		LL ans=0, INFI;
		memset(&INFI, 100, sizeof(INFI));
		while(build()) ans+=find(src, INFI);
		return ans;
	}
	void print_flow() {
		for(int i=0; i<e_cnt; i+=2) {
			Edge *e=&edges[i];
			int x=e->y, y=e->oppo->y;
			LL c=(e->w - e->oppo->w)/2;
			if(c<0) swap(x,y), c=-c;
			printf("%d %d %d\n", x, y, (int)c);
		}
	}
    /*
    vector<int> get_cut() {
    	vector<int> answer;
    	dinic_build();
    	for (int x = 1; x <= node_count; ++ x)
    		if (level[x] > 0)
    			for (int e = first[x]; e > 0; e = e_next[e])
    				if (level[e_link[e]] < 0)
    					answer.push_back(e_ind[e]);
    	return answer;
    }*/
};
