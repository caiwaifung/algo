const int MAXN=55;
const int MAXR=MAXN*MAXN;
const int MAXC=MAXN*6;
const int MAXNUM=MAXR*4;

DancingLinks<MAXR, MAXC, MAXNUM> dlx;
int idx[MAXN], idy[MAXN], idu[MAXN*2], idv[MAXN*2];
int ie[MAXN][MAXN], iex[MAXR], iey[MAXR];
int rows, cols;

int map[MAXN], n;
bool found;

bool finish(int *ans) {
	for(int i=1; i<=cols; ++i) {
		int cur=ans[i]; if(cur==0) continue;
		map[iex[cur]]=iey[cur];
	}
	for(int i=1; i<=n; ++i) printf("%d%c", map[i], i<n?' ':'\n');
	found=true;
	return true;
}

int main() {
	while(1) {
		if(scanf("%d", &n)==EOF) break;
		for(int i=1; i<=n; ++i) scanf("%d", map+i);
		cols=0;
		for(int i=1; i<=n; ++i) idx[i]=++cols;
		for(int i=1; i<=n; ++i) idy[i]=++cols;
		for(int i=1; i<=n*2-1; ++i) idu[i]=++cols;
		for(int i=1; i<=n*2-1; ++i) idv[i]=++cols;
		rows=0;
		for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) {
			ie[i][j]=++rows;
			iex[rows]=i; iey[rows]=j;
		}
		dlx.initialize(rows, cols, finish);
		for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) {
			dlx.add(ie[i][j], idx[i]);
			dlx.add(ie[i][j], idy[j]);
			dlx.add(ie[i][j], idu[i+j-1]);
			dlx.add(ie[i][j], idv[i-j+n]);
		}
		for(int i=1; i<=n*2-1; ++i) dlx.ignore(idu[i]), dlx.ignore(idv[i]);
		for(int i=1; i<=n; ++i)
			if(map[i]>0)
				dlx.choose(ie[i][map[i]]);
		found=false;
		dlx.solve();
		if(!found) printf("no answer i think!\n");
	}
	return 0;
}
