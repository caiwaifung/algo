// 17:44
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
using namespace std;

#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;
typedef long long LL;
typedef vector<int> VI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const int MAXN=50010;
const int MAXE=50010;

int g[MAXN], g_lnk[MAXE*2], g_nxt[MAXE*2];
int n, m;
VI ans;

int vis[MAXN], dfn[MAXN], low[MAXN], tt;
int size[MAXN], sup[MAXN]; bool marked_up[MAXN];

int dfs(int x, int fa) {
	dfn[x]=low[x]=++tt;
	vis[x]=-1;
	size[x]=1;
	vector<PII> rs;
	int cnt=(fa==0?0:1);
	marked_up[x]=false;
	sup[x]=0;
	for(int e=g[x]; e; e=g_nxt[e]) {
		int y=g_lnk[e]; if(y==fa) continue;
		if(vis[y]<0)
			low[x]=min(low[x], dfn[y]);
		if(vis[y]==0) {
			int ret=dfs(y, x);
			if(low[y]>=dfn[x]) ++cnt;
			else {
				sup[x]+=size[y];
				if(ret!=0) marked_up[x]=true;
			}
			low[x]=min(low[x], low[y]);
			size[x]+=size[y];
			rs.PB(MP(y, ret));
		}
	}
	vis[x]=1;
	if(cnt>1) {
		//printf("x=%d\n",x);
		forn(i, rs.size())
			if(rs[i].se==0 && low[rs[i].fi]>=dfn[x])
				ans.PB(size[rs[i].fi]);
				//printf("%d %d\n",rs[i].fi,size[rs[i].fi]); }
		return x;
	} else {
		int cur=0;
		forn(i, rs.size())
			if(rs[i].se!=0) {
				if(cur==0) cur=rs[i].se;
				else cur=-1;
			}
		return cur;
	}
}

void solve(int cs) {
	n=0; int e=0;
	fillchar(g, 0);
	forint(i, 1, m) {
		int a, b; scanf("%d%d", &a,&b);
		n=max(n, max(a, b));
		g_lnk[++e]=b, g_nxt[e]=g[a], g[a]=e;
		g_lnk[++e]=a, g_nxt[e]=g[b], g[b]=e;
	}
	ans.clear();
	fillchar(vis, 0); tt=0;
	int t=dfs(1, 0);
	int num; LL ret;
	if(t==0) {
		num=2;
		ret=LL(n)*LL(n-1)/2;
	} else {
		if(t>0 && !marked_up[t]) {
			int cnt=n-size[t]+sup[t];
			if(cnt>0) ans.PB(cnt);
		}
		num=ans.size();
		ret=1;
		forn(i, ans.size()) ret*=ans[i];
	}
	printf("Case %d: ", cs); cout<<num<<" "<<ret<<endl;
}

int main() {
	int cs=0;
	while(1) {
		scanf("%d", &m);
		if(m==0) break;
		solve(++cs);
	}
	return 0;
}
