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

const int MAXN=110;
const int MAXH=220;
const int MAXT=2200;

int h[MAXN], g[MAXN];
int n, p_me, p_tower;

int f[MAXN][MAXH][MAXT][2];

void solve() {
	cin>>p_me>>p_tower>>n;
	forint(i, 1, n) cin>>h[i]>>g[i];
	int maxt=2010;
	fillchar(f, 0xff);
	f[1][h[1]][0][0]=0;
	h[n+1]=1;
	forint(i, 1, n) forintdown(r, h[i], 1) forint(t, 0, maxt) forn(turn, 2) {
		if(f[i][r][t][turn]<0) continue;
		int val=f[i][r][t][turn];
		if(t>0) {
			int *cur, b=0;
			if(r<=p_me) cur=&f[i+1][h[i+1]][t-1][turn], b=g[i];
			else cur=&f[i][r-p_me][t-1][turn];
			*cur=max(*cur, val+b);
		}
		if(turn==0) {
			int *cur=&f[i][r][t+1][1];
			*cur=max(*cur, val);
		} else {
			int *cur;
			if(r<=p_tower) cur=&f[i+1][h[i+1]][t][0];
			else cur=&f[i][r-p_tower][t][0];
			*cur=max(*cur, val);
		}
	}
	int ans=0;
	forint(t, 0, maxt) forn(turn, 2) ans=max(ans, f[n+1][h[n+1]][t][turn]);
	printf("%d\n", ans);
}

int main() {
	int ncs; scanf("%d", &ncs);
	forint(cs, 1, ncs) {
		cerr<<cs<<endl;
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
