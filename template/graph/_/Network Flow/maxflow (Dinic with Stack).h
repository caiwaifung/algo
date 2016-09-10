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

	LL lim[N], tot[N];
	int st[N];
	LL find() {
		LL infi; memset(&infi, 0x7f, sizeof(infi));
		int p=1;
		st[p]=src; tot[p]=0; lim[p]=infi;
		while(1) {
			while(tot[p]==lim[p] || ce[st[p]]==NULL) {
				if(p==1) return tot[1];
				LL cur=tot[p];
				--p;
				tot[p]+=cur;
				ce[st[p]]->w-=cur;
				ce[st[p]]->oppo->w+=cur;
			}
			for(Edge *&e=ce[st[p]]; e!=NULL; e=e->next)
				if(e->w>0 && ce[e->y]!=NULL && d[e->y]>d[st[p]]) {
					LL cur=min(lim[p]-tot[p], e->w);
					if(e->y==dst) {
						tot[p]+=cur;
						e->w-=cur;
						e->oppo->w+=cur;
					} else {
						lim[p+1]=cur;
						tot[p+1]=0;
						st[p+1]=e->y;
						++p;
					}
					break;
				}
		}
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
