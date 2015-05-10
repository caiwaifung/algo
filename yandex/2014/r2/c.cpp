#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;

const int MAXN=2020;

int a[MAXN][MAXN];
int n, m;
int id[MAXN][MAXN], num;

void dfs(int x, int y, int i, int c) {
	if(x<1 || x>n || y<1 || y>m) return;
	if(id[x][y]>0) return;
	if(a[x][y]!=c) return;
	id[x][y]=i;
	dfs(x-1, y, i, c);
	dfs(x+1, y, i, c);
	dfs(x, y-1, i, c);
	dfs(x, y+1, i, c);
}

PII head[2][MAXN][MAXN];

PII get_head(int c, int x1, int y1, int x2, int y2) {
	PII t;
	t.fi=head[c][x2][y2].fi-head[c][x1-1][y2].fi-head[c][x2][y1-1].fi+head[c][x1-1][y1-1].fi;
	t.se=head[c][x2][y2].se-head[c][x1-1][y2].se-head[c][x2][y1-1].se+head[c][x1-1][y1-1].se;
	return t;
}

int borders_l[MAXN][MAXN];
int borders_u[MAXN][MAXN];
int next_l[2][MAXN][MAXN];
int next_u[2][MAXN][MAXN];

void init() {
	scanf("%d%d", &n,&m);
	forint(i, 1, n) {
		static char b[MAXN];
		scanf("%s", b+1);
		forint(j, 1, m) a[i][j]=int(b[j]-'0');
	}
	fillchar(id, 0); num=0;
	fillchar(head, 0);
	forint(i, 1, n) forint(j, 1, m) if(id[i][j]==0) {
		int c=a[i][j];
		++num;
		dfs(i, j, num, c);
		head[c][i][j].fi++;
		head[c][i][j].se+=num;
	}
	forint(i, 1, n) forint(j, 1, m) forn(c, 2) {
		head[c][i][j].fi=head[c][i][j].fi+head[c][i-1][j].fi+head[c][i][j-1].fi-head[c][i-1][j-1].fi;
		head[c][i][j].se=head[c][i][j].se+head[c][i-1][j].se+head[c][i][j-1].se-head[c][i-1][j-1].se;
	}

	fillchar(borders_l, 0);
	forint(i, 1, n) forint(j, 2, m)
		borders_l[i][j]=borders_l[i][j-1]+(a[i][j]!=a[i][j-1]?1:0);
	fillchar(borders_u, 0);
	forint(i, 2, n) forint(j, 1, m)
		borders_u[i][j]=borders_u[i-1][j]+(a[i][j]!=a[i-1][j]?1:0);
	fillchar(next_l, 0);
	fillchar(next_u, 0);
	forint(i, 1, n) forint(j, 1, m) {
		forn(c, 2) next_l[c][i][j]=next_l[c][i][j-1];
		forn(c, 2) next_u[c][i][j]=next_u[c][i-1][j];
		next_l[a[i][j]][i][j]=j;
		next_u[a[i][j]][i][j]=i;
	}
}

int get_borders(int x1, int y1, int x2, int y2) {
	// find color changes on border
	int ans=0;
	ans+=borders_l[x1][y2]-borders_l[x1][y1];
	ans+=borders_l[x2][y2]-borders_l[x2][y1];
	ans+=borders_u[x2][y1]-borders_u[x1][y1];
	ans+=borders_u[x2][y2]-borders_u[x1][y2];
	return ans;
}

int get_seg_rep(int c, int x1, int y1, int x2, int y2) {
	if(x1==x2) {
		int y=next_l[c][x2][y2];
		if(y>=y1) return id[x1][y];
		else return 0;
	} else {
		int x=next_u[c][x2][y2];
		if(x>=x1) return id[x][y1];
		else return 0;
	}
}

int get_border_rep(int c, int x1, int y1, int x2, int y2) {
	// find one with color c on border; return its id
	int ans=0;
	ans=get_seg_rep(c, x1, y1, x1, y2); if(ans>0) return ans;
	ans=get_seg_rep(c, x2, y1, x2, y2); if(ans>0) return ans;
	ans=get_seg_rep(c, x1, y1, x2, y1); if(ans>0) return ans;
	ans=get_seg_rep(c, x1, y2, x2, y2); if(ans>0) return ans;
	return 0;
}

int compute(int x1, int y1, int x2, int y2) {
	int cnt=get_borders(x1, y1, x2, y2);
	if(cnt>=4) return 0;
	PII h[2];
	forn(c, 2) h[c]=get_head(c, x1, y1, x2, y2);
	if(h[0].fi>=2 || h[1].fi>=2) return 0;

	if(cnt==0) {
		int c=a[x1][y1];
		if(h[c].fi>0 && h[c].se!=id[x1][y1]) return 0;
		if(h[c^1].fi==0)
			return 1;
		else return 2;
	} else {
		forn(c, 2) {
			int i=get_border_rep(c, x1, y1, x2, y2);
			if(h[c].fi>0 && h[c].se!=i) return 0;
		}
		return 2;
	}
}

void solve() {
	int cs; scanf("%d", &cs);
	while(cs--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
		int ans=compute(x1, y1, x2, y2);
		printf("%d\n", ans);
	}
}

int main() {
	init();
	solve();
	return 0;
}
