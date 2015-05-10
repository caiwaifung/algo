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

int a[1010], x[1010], y[1010];
int n;
int w, h;

int main() {
	scanf("%d", &n);
	forint(i, 1, n) scanf("%d", &a[i]);
	x[0]=y[0]=0;
	int min_y=0;
	forint(i, 1, n) {
		x[i]=x[i-1]+a[i];
		y[i]=y[i-1]+a[i]*(i%2==1?1:-1);
		min_y=min(min_y, y[i]);
	}
	forint(i, 1, n)
		y[i]-=min_y[i];
	w=h=0;
	return 0;
}
