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

int a[111];
int n;

int main() {
	scanf("%d", &n);
	forint(i, 1, n) scanf("%d", &a[i]);
	sort(a+1, a+n+1);
	reverse(a+1, a+n+1);
	VI x;
	int mv=a[n], mc=0;
	while(n>0 && a[n]==mv) ++mc, --n;
	forint(i, 1, n) {
		sort(x.rbegin(), x.rend());
		x.erase(unique(x.begin(), x.end()), x.end());
		VI y=x; y.PB(a[i]);
		size_t k=0;
		while(k<x.size()) {
			int cur=x[k]; if(cur<a[i]) break;
			++k;
			y.PB(cur%a[i]);
		}
		x=y;
	}
	forn(i, x.size()) x[i]=x[i]%mv;
	if(mc>1) x.PB(0); else x.PB(mv);

	sort(x.rbegin(), x.rend());
	x.erase(unique(x.begin(), x.end()), x.end());
	//forn(i, x.size()) printf("%d ",x[i]);printf("\n");
	printf("%d\n", x.size());
	return 0;
}
