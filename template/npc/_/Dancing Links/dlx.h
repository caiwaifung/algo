typedef bool (*FinishProc)(int *ans);

template<size_t R, size_t C, size_t N> class DancingLinks {
	int le[N+C], ri[N+C], up[N+C], dn[N+C], px[N+C], py[N+C];
	pair<int,int> nodes[N];
	int col[C], tmp[C], s[C], answer[C];
	int r, c, trc, num, root;
	FinishProc fproc;

	void addlr(int z, int p) {
		ri[p]=ri[z], le[p]=z;
		le[ri[p]]=ri[le[p]]=p;
	}
	void addud(int z, int p) {
		dn[p]=dn[z], up[p]=z;
		up[dn[p]]=dn[up[p]]=p;
	}
	void cover(int y) {
		int z=col[y];
		le[ri[z]]=le[z], ri[le[z]]=ri[z];
		for(int p=dn[z]; p!=z; p=dn[p])
			for(int q=ri[p]; q!=p; q=ri[q]) {
				up[dn[q]]=up[q], dn[up[q]]=dn[q];
				--s[py[q]];
			}
	}
	void uncover(int y) {
		int z=col[y];
		le[ri[z]]=ri[le[z]]=z;
		for(int p=up[z]; p!=z; p=up[p])
			for(int q=le[p]; q!=p; q=le[q]) {
				up[dn[q]]=dn[up[q]]=q;
				++s[py[q]];
			}
	}
	bool search(int depth) {
		int val=N, z;
		for(int p=ri[root]; p!=root; p=ri[p])
			if(!ignored[py[p]] && s[py[p]]<val)
				val=s[py[p]], z=p;
		if(val==N) return fproc(answer);
		if(val==0) return false;
		cover(py[z]);
		for(int p=dn[z]; p!=z; p=dn[p]) {
			for(int q=ri[p]; q!=p; q=ri[q]) {
				cover(py[q]);
				answer[py[q]]=px[q];
			}
			answer[py[p]]=px[p];
			if(search(depth+1)) return true;
			answer[py[p]]=0;
			for(int q=le[p]; q!=p; q=le[q]) {
				uncover(py[q]);
				answer[py[q]]=0;
			}
		}
		uncover(py[z]);
		return false;
	}
public:
	bool chosen[R];
	bool ignored[C];
	void initialize(int rows, int cols, FinishProc fp) {
		r=rows, c=cols, num=0;
		fproc=fp;
		memset(chosen, false, sizeof(chosen));
		memset(ignored, false, sizeof(ignored));
	}
	void add(int x, int y) {
		nodes[++num]=make_pair(x,y);
	}
	void solve() {
		sort(nodes+1, nodes+num+1);
		int nodes_n=num;
		root=++num;
		le[root]=ri[root]=root;
		for(int y=1; y<=c; ++y) {
			col[y]=tmp[y]=++num; s[y]=0;
			up[num]=dn[num]=num; py[num]=y;
			addlr(num-1, num);
		}
		memset(answer, 0, sizeof(answer));
		for(int x=1, st=1, en=0; x<=r; ++x, st=en+1) {
			while(en+1<=nodes_n && nodes[en+1].first==x) ++en;
			for(int k=st, y; k<=en; ++k) {
				px[k]=x, py[k]=y=nodes[k].second;
				++s[y];
				if(chosen[x])
					if(answer[y]>0) return;
					else answer[y]=x;
				addud(tmp[y], k); tmp[y]=k;
			}
			le[st]=ri[st]=st;
			for(int k=st+1; k<=en; ++k) addlr(k-1, k);
		}
		for(int y=1; y<=c; ++y) if(answer[y]>0) cover(y);
		search(1);
	}
};
