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

	Edge *pe[N];
	int st[N];
	LL find() {
		LL ans=0;
		int p=1; st[p]=src;
		while(p>0) {
			if(st[p]==dst) {
				LL cur; memset(&cur, 100, sizeof(cur));
				for(int i=1; i<p; ++i)
					cur=min(cur, pe[i]->w);
				ans+=cur;
				for(int i=p-1; i>=1; --i) {
					if((pe[i]->w-=cur)==0) p=i;
					pe[i]->oppo->w += cur;
				}
			}
			while(1) {
				Edge *e=ce[st[p]];
				if(e==NULL) {--p; break;}
				if(e->w>0 && ce[e->y]!=NULL && d[e->y]>d[st[p]]) {
					pe[p]=e;
					st[++p]=e->y; break;
				}
				ce[st[p]]=e->next;
			}
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
		LL ans=0;
		while(build()) ans+=find();
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
