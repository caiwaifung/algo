#include <cstdlib>
#include <queue>
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

struct Rect {
	int x1, y1, x2, y2;
	Rect() {}
	Rect(int x1, int y1, int x2, int y2)
		: x1(x1), y1(y1), x2(x2), y2(y2) {}
	void read() {
		scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
	}
};

const int MAXN=1010;

int g[MAXN][MAXN];
Rect r[MAXN];
int d[MAXN];
bool vis[MAXN];

int get_g_x(PII a, PII b) {
	if(a.se<b.fi) return b.fi-a.se-1;
	if(b.se<a.fi) return a.fi-b.se-1;
	return 0;
}

int get_g(Rect a, Rect b) {
	int x=get_g_x(MP(a.x1,a.x2), MP(b.x1,b.x2));
	int y=get_g_x(MP(a.y1,a.y2), MP(b.y1,b.y2));
	return max(x,y);
}

void solve() {
	int w, h, n;
	scanf("%d%d%d", &w,&h,&n);
	forint(i, 1, n) r[i].read();
	r[++n]=Rect(-1, 0, -1, h-1);
	r[++n]=Rect(w, 0, w, h-1);
	forint(i, 1, n) forint(j, 1, n) {
		g[i][j]=get_g(r[i], r[j]);
		//printf("g[%d,%d]=%d\n",i,j,g[i][j]);
	}

	fillchar(d, 100); fillchar(vis, false);
	priority_queue<PII> que;
	d[n-1]=0;
	que.push(MP(0, n-1));
	while(!que.empty()) {
		int x=que.top().se;
		//printf("x=%d d[x]=%d\n",x,d[x]);
		que.pop();
		if(vis[x]) continue;
		vis[x]=true;
		forint(y, 1, n)
			if(d[x]+g[x][y]<d[y]) {
				d[y]=d[x]+g[x][y];
				que.push(MP(-d[y], y));
			}
	}
	printf("%d\n", d[n]);
}

int main()  {
	int ncs; scanf("%d", &ncs);
	forint(cs, 1, ncs) {
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
