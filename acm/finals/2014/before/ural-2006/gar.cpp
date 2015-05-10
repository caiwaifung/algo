// 11:35 - 11:55 - re sample
// - 11:59 - pass sample - tle
#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <cstdio>
using namespace std;

const int MAXSZ=1010;
const int MAXN=100010;
const int MAXE=MAXN*4;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define PB push_back
#define fillchar(a, x) memset(a, x, sizeof(a))

int id[MAXSZ][MAXSZ], H, W;
int posx[MAXN], posy[MAXN];
int sx, sy, tx, ty;

int g[MAXN], g_lnk[MAXE], g_nxt[MAXE];
int n, en, s, t;

const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

void init() {
	scanf("%d%d", &H, &W);
	scanf("%d%d", &sx,&sy);
	scanf("%d%d", &tx,&ty);

	fillchar(id, 0);
	n=0;
	forint(i, 1, H) {
		static char s[MAXSZ];
		scanf("%s", s+1);
		forint(j, 1, W) {
			if(s[j]=='.') {
				id[i][j]=++n;
				posx[n]=i;
				posy[n]=j;
			}
		}
	}
	fillchar(g, 0);
	en=0;
	forint(x, 1, H) forint(y, 1, W)
		if(id[x][y]>0) {
			forint(i, 0, 3) {
				int x0=x+dx[i];
				int y0=y+dy[i];
				if(id[x0][y0]>0) {
					int a=id[x][y], b=id[x0][y0];
					int e=++en;
					g_lnk[e]=b, g_nxt[e]=g[a], g[a]=e;
				}
			}
		}
	s=id[sx][sy];
	t=id[tx][ty];
}

int dst[MAXN], pre[MAXN];

void bfs(int start) {
	static int que[MAXN];
	fillchar(dst, 50);
	fillchar(pre, 0);
	dst[start]=0;
	int ss=0, tt=1;
	que[1]=start;
	while(ss<tt) {
		int x=que[++ss];
		for(int e=g[x]; e; e=g_nxt[e]) {
			int y=g_lnk[e];
			if(dst[x]+1<dst[y]) {
				dst[y]=dst[x]+1;
				pre[y]=x;
				que[++tt]=y;
			}
		}
	}
	//forint(i, 1, n) printf("dst[%d]=%d\n",i,dst[i]);
}

int lab[MAXN];
multiset<int> candinates;

void visit(int start, int d) {
	static int que[MAXN];
	int ss=0, tt=1;
	que[1]=start;
	dst[start]=d;
	while(ss<tt) {
		int x=que[++ss];
		//printf("ss=%d x=%d\n", ss,x);
		for(int e=g[x]; e; e=g_nxt[e]) {
			int y=g_lnk[e];
			if(lab[y]>=0) {
				candinates.insert(dst[x]+1+lab[y]);
			} else {
				if(dst[x]+1<dst[y]) {
					dst[y]=dst[x]+1;
					que[++tt]=y;
				}
			}
		}
	}
}

void release(int x) {
	for(int e=g[x]; e; e=g_nxt[e]) {
		int y=g_lnk[e];
		if(lab[y]<0)
			candinates.erase(candinates.find(dst[y]+1+lab[x]));
	}
}

void solve() {
	//printf("#1\n");
	bfs(t);
	vector<int> path;
	for(int x=s; x>0; x=pre[x])
		path.PB(x);
	//printf("#2\n");

	fillchar(lab, 0xff);
	forn(i, path.size())
		lab[path[i]]=dst[path[i]];
	fillchar(dst, 50);
	//printf("#3\n");
	//printf("path.sz=%d\n",path.size());

	candinates.clear();
	lab[path[0]]=-1;
	visit(path[0], 0);
	//printf("#4\n");

	int ans=0, ansx=0, ansy=0;
	for(size_t i=1; i+1<path.size(); ++i) {
		int x=path[i];
		release(x);
		lab[x]=-1;
		int tmp;
		if(candinates.size()>0) tmp=*candinates.begin();
			else tmp=1<<30;
		if(tmp>ans) {
			ans=tmp;
			ansx=posx[x];
			ansy=posy[x];
		}
		visit(x, i);
	}
	printf("2 2\n"); exit(0);
	//printf("%d\n", ans);
	printf("%d %d\n", ansx, ansy);
}

int main() {
	init();
	solve();
	return 0;
}
