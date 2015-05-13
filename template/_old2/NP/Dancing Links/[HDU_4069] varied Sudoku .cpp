int num[11][11];
bool valid[11][11][4];
int belong[11][11];
const int dx[4]={-1, 0, 1, 0};
const int dy[4]={0, 1, 0, -1};
const int db[4]={16, 32, 64, 128};

void search(int x, int y, int id) {
	belong[x][y]=id;
	for(int i=0; i<4; ++i) {
		if(!valid[x][y][i]) continue;
		int x0=x+dx[i], y0=y+dy[i];
		if(x0>=1 && x0<=9 && y0>=1 && y0<=9 && belong[x0][y0]==0)
			search(x0, y0, id);
	}
}

DancingLinks<11*11*10, 3*11*10, 11*11*10*4> dlx;
int idx[11][10], idy[11][10], idb[11][10], idpos[11][11];
int ie[11][11][10], iex[11*11*10], iey[11*11*10], ieval[11*11*10];
int cols, rows;

int found;
bool finish(int *ans) {
	if(found>0) {++found; return true;}
	found=1;
	for(int i=1; i<=cols; ++i) {
		int cur=ans[i]; if(cur==0) printf("heio!");
		num[iex[cur]][iey[cur]]=ieval[cur];
	}
	return false;
}

int main() {
	int cs; scanf("%d", &cs);
	for(int fcs=1; fcs<=cs; ++fcs) {
		printf("Case %d:\n", fcs);
		for(int i=1; i<=9; ++i)
			for(int j=1; j<=9; ++j) {
				int x; scanf("%d", &x);
				num[i][j]=(x&15);
				for(int k=0; k<4; ++k)
					valid[i][j][k]=((x&db[k])==0);
			}
		int tot=0;
		memset(belong, 0, sizeof(belong));
		for(int i=1; i<=9; ++i) for(int j=1; j<=9; ++j)
			if(belong[i][j]==0)
				search(i, j, ++tot);
		cols=0;
		for(int i=1; i<=9; ++i) for(int val=1; val<=9; ++val) idx[i][val]=++cols;
		for(int i=1; i<=9; ++i) for(int val=1; val<=9; ++val) idy[i][val]=++cols;
		for(int i=1; i<=9; ++i) for(int val=1; val<=9; ++val) idb[i][val]=++cols;
		for(int i=1; i<=9; ++i) for(int j=1; j<=9; ++j) idpos[i][j]=++cols;
		rows=0;
		for(int i=1; i<=9; ++i) for(int j=1; j<=9; ++j)
			for(int val=1; val<=9; ++val) {
				ie[i][j][val]=++rows;
				iex[rows]=i, iey[rows]=j, ieval[rows]=val;
			}
		dlx.initialize(rows, cols, finish);
		for(int i=1; i<=9; ++i) for(int j=1; j<=9; ++j)
			for(int val=1; val<=9; ++val) {
				dlx.add(ie[i][j][val], idx[i][val]);
				dlx.add(ie[i][j][val], idy[j][val]);
				dlx.add(ie[i][j][val], idb[belong[i][j]][val]);
				dlx.add(ie[i][j][val], idpos[i][j]);
			}
		for(int i=1; i<=9; ++i) for(int j=1; j<=9; ++j)
			if(num[i][j]>0)
				dlx.chosen[ie[i][j][num[i][j]]]=true;
		found=0;
		dlx.solve();
		if(found==0) printf("No solution\n");
		else if(found>1) printf("Multiple Solutions\n");
		else for(int i=1; i<=9; ++i,printf("\n"))
			for(int j=1; j<=9; ++j) printf("%d", num[i][j]);
	}
	return 0;
}
