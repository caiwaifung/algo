#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

int main() {
	VPI a; int n, s;
	scanf("%d%d", &n,&s); s=1000000-s;
	forn(i, n) {
		int x, y, t; scanf("%d%d%d",&x,&y,&t);
		a.PB(MP(x*x+y*y, t));
	}
	sort(a.begin(), a.end());
	size_t cur=0; int ct=0; int ans=0;
	while(ct<s && cur<a.size()) {
		ct+=a[cur].se;
		ans=a[cur].fi;
		++cur;
	}
	if(ct<s) printf("-1\n"); else printf("%.9lf\n", sqrt(double(ans)));

	
	return 0;
}
