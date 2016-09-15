// O(ElogE + N^2)
template<size_t N, size_t E> class DirectedMST {
	struct Edge {
		int a, b; LL c;
		friend bool operator <(const Edge &x, const Edge &y) {
			if(x.b!=y.b) return x.b<y.b;
			return x.c<y.c;
		}
	} e[E];
	int ne;
	int le[N], ri[N];
	int belong[N], next[N];
	LL addi[N];
	int pre[N], vis[N]; bool lab[N];
	int n;
	
public:
	LL min_cost;
	void initialize(int _n) {
		n=_n, ne=0;
	}
	void add_edge(int a, int b, LL c) {
		++ne;
		e[ne].a=a, e[ne].b=b, e[ne].c=c;
	}
	bool cproc1(int i) {
		LL cur;
		memset(&cur, 50, sizeof(cur));
		pre[i]=0;
		for(int x=i; x>0; x=next[x]) {
			while(le[x]<=ri[x] && belong[e[le[x]].a]==belong[e[le[x]].b])
				++le[x];
			if(le[x]<=ri[x] && e[le[x]].c+addi[x]<cur) {
				cur=e[le[x]].c+addi[x];
				pre[i]=belong[e[le[x]].a];
			}
		}
		if(pre[i]==0) return false;
		min_cost+=cur;
		for(int x=i; x>0; x=next[x])
			addi[x]-=cur;
		return true;
	}
	bool cproc2(int i) {
		int x=i;
		while(!lab[x] && vis[x]==0)
			vis[x]=i, x=pre[x];
		if(!lab[x] && vis[x]==i) {
			lab[x]=true;
			for(int y=pre[x]; y!=x; y=pre[y]) {
				lab[y]=true;
				for(int z=y, nz=next[y]; z>0; z=nz, nz=next[nz]) {
					next[z]=next[x], next[x]=z;
					belong[z]=x;
				}
			}
			return true;
		}
		return false;
	}
	bool compute(int root) {
		sort(e+1, e+ne+1);
		ri[0]=0;
		for(int i=1; i<=n; ++i) {
			belong[i]=i; next[i]=0; addi[i]=0;
			le[i]=1+(ri[i]=ri[i-1]);
			while(ri[i]<ne && e[ri[i]+1].b==i)
				++ri[i];
		}
		min_cost=0;
		while(1) {
			for(int i=1; i<=n; ++i)
				if(belong[i]==i && i!=root)
					if(!cproc1(i))
						return false;
			memset(vis, 0, sizeof(vis));
			memset(lab, false, sizeof(lab));
			bool flag=false;
			lab[root]=true;
			for(int i=1; i<=n; ++i)
				if(belong[i]==i)
					if(cproc2(i))
						flag=true;
			if(!flag) break;
		}
		return true;
	}
};
