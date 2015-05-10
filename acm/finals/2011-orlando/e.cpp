#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;

const int MAXN=500010;
const int MAXW=2010;

int dx, dy, n, q, w;
int px[MAXN], py[MAXN], pu[MAXN], pv[MAXN];
int s[MAXW][MAXW];

void solve() {
	forint(i, 1, n) scanf("%d%d", px+i,py+i);
	w=dx+dy-1;
	forint(i, 1, n) {
		pu[i]=px[i]+py[i]-1;
		pv[i]=px[i]-py[i]+dy;
	}
	while(q--) {
		int limit; scanf("%d", &limit);
		fillchar(s, 0);
		forint(i, 1, n) {
			int u1=max(pu[i]-limit, 1), u2=min(pu[i]+limit, w);
			int v1=max(pv[i]-limit, 1), v2=min(pv[i]+limit, w);
			s[u1][v1]++;
			s[u1][v2+1]--;
			s[u2+1][v1]--;
			s[u2+1][v2+1]++;
		}

		int ans=-1; PII ansp;
		forint(u, 1, w) forint(v, 1, w) {
			s[u][v]=s[u][v]+s[u-1][v]+s[u][v-1]-s[u-1][v-1];
			int p=u+1, q=v-dy;
			int x=(p+q)/2, y=(p-q)/2;
			if((p+q)%2==0 && x>=1 && x<=dx && y>=1 && y<=dy) {
				if(s[u][v]>ans) ans=s[u][v], ansp=MP(1<<30,1<<30);
				if(s[u][v]==ans) {
					PII tmp=MP(y,x);
					ansp=min(ansp, tmp);
				}
			}
		}
		printf("%d (%d,%d)\n", ans, ansp.se,ansp.fi);
	}
}

int main() {
	int cs=0;
	while(1) {
		scanf("%d%d%d%d",&dx,&dy,&n,&q); if(dx==0) break;
		printf("Case %d:\n", ++cs);
		solve();
	}
	return 0;
}
