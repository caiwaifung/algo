#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN=3010;
const int MAXH=(1<<20)-1;
typedef pair<int,int> PII;

inline int gcd(int a, int b) {
	return b==0 ? a : gcd(b,a%b);
}

int x[MAXN], y[MAXN];
int n;

int h[MAXH], hh[MAXH], ha[MAXH], hb[MAXH], hc[MAXH], hnxt[MAXH], hn;
int best;

inline void add(int a, int b) {
	int p=((a^b)&MAXH);
	for(int i=h[p]; i>0; i=hnxt[i])
		if(ha[i]==a && hb[i]==b) {
			best=max(best, ++hc[i]);
			return;
		}
	++hn;
	best=max(best, 1);
	hh[hn]=p, ha[hn]=a, hb[hn]=b, hc[hn]=1;
	hnxt[hn]=h[p], h[p]=hn;
}

void solve() {
	int ret=0;
	memset(h, 0, sizeof(h)); hn=0;
	for(int i=1; i<=n; ++i) {
		for(int j=1; j<=hn; ++j) h[hh[j]]=0; hn=0;
		best=0;
		int tmp=0;
		int x0=x[i], y0=y[i];
		for(int j=1; j<=n; ++j) {
			if(x[j]==x0 && y[j]==y0) {
				++tmp; continue;
			}
			int a=y[j]*x0-y0*x[j];
			int b=x0*x[j]*(x[j]-x0);
			int t=gcd(a, b);
			a/=t, b/=t;
			if(b<0) a=-a, b=-b;
			if(a>=0) continue;
			add(-a, b);
		}
		ret=max(ret, best+tmp);
	}
	printf("%d\n", ret);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i=1; i<=n; ++i) scanf("%d%d", &x[i],&y[i]);
		solve();
	}
	return 0;
}

