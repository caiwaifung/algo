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

void solve() {
	int n, x; scanf("%d%d", &n,&x);
	static int a[10010];
	forint(i, 1, n) scanf("%d", &a[i]);
	int cnt=0, j=1;
	sort(a+1, a+n+1);
	forintdown(i, n, 1) {
		if(j>i) break;
		++cnt;
		if(a[j]+a[i]<=x) ++j;
	}
	printf("%d\n", cnt);
}

int main() {
	int ncs; scanf("%d", &ncs);
	forint(cs, 1, ncs) {
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
