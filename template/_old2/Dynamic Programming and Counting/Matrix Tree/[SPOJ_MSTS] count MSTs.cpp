#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int modnum=31011;

pair<int, pair<int, int> > e[1010];
int g[110][110];
bool vis[110];
int list[110];
int ff[110];
int a[110][110];
int n, m;

int get(int x) {
	return ff[x]==0?x:(ff[x]=get(ff[x]));
}

void dfs(int x) {
	if (vis[x]) return;
	list[++list[0]]=x;
	vis[x]=true;
	for (int y=1; y<=n; y++)
		if (g[x][y]>0) dfs(y);
}

int count() {
	if (list[0]==1) return 1;
	int num=list[0];
	memset(a, 0, sizeof(a));
	for (int i=1; i<=num; i++)
		for (int j=1; j<=num; j++) {
			a[i][i]+=g[list[i]][list[j]];
			a[i][j]-=g[list[i]][list[j]];
		}
	num--;
	int ans=1;
	for (int i=1; i<=num; i++) {
		for (int j=i+1; j<=num; j++)
			while (a[j][i]!=0) {
				int tmp=a[i][i]/a[j][i];
				for (int k=i; k<=num; k++) {
					a[i][k]=(a[i][k]-tmp*a[j][k])%modnum;
					swap(a[i][k], a[j][k]);
				}
				ans=-ans;
			}
		ans=(ans*a[i][i])%modnum;
	}
	return (ans%modnum+modnum)%modnum;
}

void solve() {
	memset(ff, 0, sizeof(ff));
	int ans=1;
	for (int i=1; i<=m; ) {
		memset(g, 0, sizeof(g));
		do {
			int a=get(e[i].second.first), b=get(e[i].second.second);
			if (a!=b) g[a][b]++, g[b][a]++;
			i++;
		} while (i<=m && e[i].first==e[i-1].first);
		memset(vis, false, sizeof(vis));
		for (int j=1; j<=n; j++)
			if (!vis[j]) {
				list[0]=0;
				dfs(j);
				ans=(ans*count())%modnum;
				for (int k=2; k<=list[0]; k++)
					ff[get(list[k])]=list[1];
			}
	}
	printf("%d\n", ans);
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i=1; i<=m; i++)
		scanf("%d%d%d", &e[i].second.first, &e[i].second.second, &e[i].first);
	sort(e+1, e+m+1);
	solve();
	return 0;
}

/*
   4 4
   1 2 1
   1 3 2
   1 4 3
   3 4 3
 */
