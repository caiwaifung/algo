// O(N*E)
template<size_t N, size_t E> class DirectedMST {
	LL ec[E]; int ea[E], eb[E], e;
	LL inw[N]; int pre[N], id[N], vis[N];
	int n;
public:
	LL min_cost;
	void initialize(int _n) {
		n=_n, e=0;
	}
	void add_edge(int a, int b, LL c) {
		ec[++e]=c, ea[e]=a, eb[e]=b;
	}
	bool compute(int root) {
		min_cost=0;
		while(1) {
			memset(inw, 50, sizeof(inw));
			memset(pre, 0, sizeof(pre));
			for(int i=1; i<=e; ++i)
				if(ea[i]!=eb[i] && ec[i]<inw[eb[i]])
					inw[eb[i]]=ec[i], pre[eb[i]]=ea[i];
			for(int i=1; i<=n; ++i)
				if(i!=root && pre[i]==0)
					return false;
			int tot=0;
			memset(id, 0, sizeof(id));
			memset(vis, 0, sizeof(vis));
			inw[root]=0;
			for(int i=1; i<=n; ++i) {
				min_cost+=inw[i];
				int x=i;
				while(x!=root && vis[x]==0 && id[x]==0)
					vis[x]=i, x=pre[x];
				if(x!=root && vis[x]==i && id[x]==0) {
					id[x]=++tot;
					for(int y=pre[x]; y!=x; y=pre[y])
						id[y]=tot;
				}
			}
			if(tot==0) break;
			for(int i=1; i<=n; ++i)
				if(id[i]==0)
					id[i]=++tot;
			for(int i=1; i<=e; ++i) {
				ec[i]-=inw[eb[i]];
				ea[i]=id[ea[i]];
				eb[i]=id[eb[i]];
			}
			n=tot;
			root=id[root];
		}
		return true;
	}
};
