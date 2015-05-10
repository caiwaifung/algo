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

const int MAXN=100010;
const int MAXE=100010;

int g[MAXN], g_i[MAXE*2], g_lnk[MAXE*2], g_nxt[MAXE*2];
int n, m;

int dfn[MAXN], low[MAXN], tt;
int vis[MAXN];
bool is_cut[MAXE];

void dfs(int x, int fa) {
	dfn[x]=low[x]=++tt;
	vis[x]=-1;
	int fa_eid=0;
	for(int e=g[x]; e; e=g_nxt[e]) {
		int y=g_lnk[e];
		if(y==fa) {
			fa_eid=g_i[e];
			continue;
		}
		if(vis[y]==0) {
			dfs(y, x);
			low[x]=min(low[x], low[y]);
		}
		if(vis[y]==-1) {
			low[x]=min(low[x], dfn[y]);
		}
	}
	if(low[x]==dfn[x] && fa_eid>0)
		is_cut[fa_eid]=true;
}

int ans;

int go(int x, int fa) {
	vis[x]=1;
	int cnt=0; if(fa>0) ++cnt;
	for(int e=g[x]; e; e=g_nxt[e]) if(is_cut[g_i[e]]) {
		int y=g_lnk[e];
		if(y==fa) continue;
		cnt+=go(y, x);
	}
	ans+=cnt/2; cnt%=2;
	return cnt;
}

int main() {
	scanf("%d%d", &n,&m);
	int e=0; fillchar(g, 0);
	forint(i, 1, m) {
		int a, b; scanf("%d%d", &a,&b);
		g_i[++e]=i; g_lnk[e]=b, g_nxt[e]=g[a], g[a]=e;
		g_i[++e]=i; g_lnk[e]=a, g_nxt[e]=g[b], g[b]=e;
	}
	fillchar(is_cut, false);
	fillchar(vis, 0);
	tt=0; dfs(1, 0);

	//forint(i, 1, m) printf("%d ", is_cut[i]); printf("\n");

	ans=0;
	fillchar(vis, 0);
	forint(i, 1, n) if(vis[i]==0)
		go(i, 0);
	cout<<ans<<endl;

	return 0;
}
