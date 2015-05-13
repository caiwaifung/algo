#include <iostream>
using namespace std;

const int maxn=500000+100;
const int maxe=250000+100;

int g[maxn*2], g_lnk[maxe*2], g_nxt[maxe*2];
int n, m;

void add_edge(int e, int a, int b)
{
	//printf("edge %d->%d\n", a, b);
	g_lnk[e]=b; g_nxt[e]=g[a]; g[a]=e;
}

void init()
{
	scanf("%d%d", &m, &n);
	for (int i=1, e=0, a, b, sa, sb; i<=m; i++)
	{
		scanf("%d%d%d%d", &a, &sa, &b, &sb);
		add_edge(++e, a+(sa^1)*n, b+sb*n);
		add_edge(++e, b+(sb^1)*n, a+sa*n);
	}
}

int belong[maxn*2], head[maxn*2];
int low[maxn*2], dfn[maxn*2], total;
int st[maxn*2], top;
int num;

void dfs(int x)
{
	st[++top]=x;
	low[x]=dfn[x]=++total;
	belong[x]=-1;
	for (int i=g[x]; i>0; i=g_nxt[i])
	{
		if (belong[g_lnk[i]]==-1)
			low[x]<?=dfn[g_lnk[i]];
		if (belong[g_lnk[i]]==0)
			dfs(g_lnk[i]),
			low[x]<?=low[g_lnk[i]];
	}
	//printf("dfn[%d]=%d low[%d]=%d\n", x, dfn[x], x, low[x]);
	if (low[x]==dfn[x])
		for (head[++num]=x; st[top+1]!=x; )
			belong[st[top--]]=num;
}

int g2[maxn*2], g2_lnk[maxe*2], g2_nxt[maxe*2];
int deg[maxn*2];

void add_edge2(int e, int a, int b)
{
	g2_lnk[e]=b; g2_nxt[e]=g2[a]; g2[a]=e;
	deg[b]++;
}

bool ans[maxn*2];

void solve()
{
	memset(belong, 0, sizeof(belong));
	num=top=total=0;
	for (int i=1; i<=n*2; i++)
		if (belong[i]==0)
			dfs(i);
	//for (int i=1; i<=n*2; i++) printf("belong[%d]=%d\n", i, belong[i]);
	for (int i=1; i<=n; i++)
		if (belong[i]==belong[i+n])
		{
			printf("IMPOSSIBLE\n");
			return;
		}
	memset(deg, 0, sizeof(deg));
	for (int x=1, e=0; x<=n*2; x++)
		for (int i=g[x]; i>0; i=g_nxt[i])
			if (belong[x]!=belong[g_lnk[i]])
				add_edge2(++e, belong[g_lnk[i]], belong[x]);
	memset(ans, true, sizeof(ans));
	for (int x=1; x<=num; x++)
		if (deg[x]==0)
			st[++top]=x;
	while (top>0)
	{
		int x=st[top--];
		#define op(x) ((x)<=n?(x)+n:(x)-n)
		//printf("curx=%d\n", x);
		//printf("head[x]=%d\n", head[x]);
		//printf("op[head[x]]=%d\n", op(head[x]));
		//printf("belong[op[head[x]]]=%d\n", belong[op(head[x])]);
		if (ans[x]) ans[belong[op(head[x])]]=false;
		for (int i=g2[x]; i>0; i=g2_nxt[i])
			if (--deg[g2_lnk[i]]==0)
				st[++top]=g2_lnk[i];
	}
	for (int i=1; i<=n; i++)
		printf("%d\n", ans[belong[i]]?0:1);
}

int main()
{
	//freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
	init();
	solve();
	return 0;
}
