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

const int MAXN=1010;

PII a[MAXN];
int n;

void solve() {
	scanf("%d", &n);
	forint(i, 1, n) scanf("%d", &a[i].fi), a[i].se=i;
	static int p[MAXN];
	forint(i, 1, n) p[i]=i;
	int ans=1<<30;
	do {
		bool dec=false, flag=true;
		forint(i, 2, n) {
			if(a[p[i-1]].fi>a[p[i]].fi)
				dec=true;
			else if(dec) flag=false;
		}
		if(flag) {
			int tmp=0;
			forint(i, 1, n) forint(j, i+1, n)
				if(a[p[i]].se>a[p[j]].se)
					++tmp;
			ans=min(ans,tmp);
		}
	} while(next_permutation(p+1, p+n+1));
	printf("%d\n", ans);
}

int main()  {
	int ncs; scanf("%d", &ncs);
	forint(cs, 1, ncs) {
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
