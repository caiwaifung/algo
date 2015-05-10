// 13:54
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
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;
typedef long long LL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const int MAXN=222;

bool black[MAXN][MAXN];
int n, m;

int digit(char c) {
	if(c>='0' && c<='9') return int(c-'0');
	if(c>='a' && c<='z') return int(c-'a'+10);
	if(c>='A' && c<='Z') return int(c-'A'+10);
	return -1;
}

bool vis[MAXN][MAXN];
int qx[MAXN*MAXN], qy[MAXN*MAXN];

const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

VPI bfs(int x, int y, bool ignore_color) {
	if(vis[x][y]) return VPI();
	int ss=0, tt=1; bool color=black[x][y];
	qx[tt]=x, qy[tt]=y;
	vis[x][y]=true;
	while(ss<tt) {
		++ss; x=qx[ss], y=qy[ss];
		for(int i=0; i<4; ++i) {
			int x0=x+dx[i], y0=y+dy[i];
			if(x0<1 || x0>n || y0<1 || y0>m) continue;
			if(vis[x0][y0]) continue;
			if(!ignore_color && color!=black[x0][y0])
				continue;
			vis[x0][y0]=true;
			++tt; qx[tt]=x0, qy[tt]=y0;
		}
	}
	VPI a;
	forint(i, 1, tt) a.PB(MP(qx[i], qy[i]));
	return a;
}

int main() {
	int cs=0;
	while(1) {
		scanf("%d%d", &n,&m);
		if(n==0) break;
		fillchar(black, false);
		forint(i, 1, n) {
			static char buf[55]; scanf("%s", buf);
			forint(j, 0, m-1) {
				int c=digit(buf[j]);
				forintdown(k, 4, 1) {
					if(c&1) black[i][j*4+k]=true;
					c>>=1;
				}
			}
		}
		m*=4;

		fillchar(vis, false);
		forint(i, 1, n) forint(j, 1, m)
			if(!vis[i][j] && (i==1 || i==n || j==1 || j==m))
				if(!black[i][j])
					bfs(i, j, false);
		string ans;
		forint(x, 1, n) forint(y, 1, m)
			if(!vis[x][y]) {
				VPI a=bfs(x, y, true);
				forn(i, a.size()) vis[a[i].fi][a[i].se]=false;
				int cnt=0;
				forn(i, a.size()) if(!vis[a[i].fi][a[i].se]) {
					if(!black[a[i].fi][a[i].se]) ++cnt;
					bfs(a[i].fi, a[i].se, false);
				}
				if(cnt==1) ans.PB('A');
				if(cnt==3) ans.PB('J');
				if(cnt==5) ans.PB('D');
				if(cnt==4) ans.PB('S');
				if(cnt==0) ans.PB('W');
				if(cnt==2) ans.PB('K');
			}
		sort(ans.begin(), ans.end());
		printf("Case %d: %s\n",++cs,ans.c_str());
	}
	return 0;
}
