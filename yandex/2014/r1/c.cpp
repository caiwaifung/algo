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

const int MAXN=10010;

int a[MAXN], m[MAXN];
int n;

int main() {
	scanf("%d", &n); forint(i, 1, n) scanf("%d", &a[i]);
	sort(a+1, a+n+1);
	int ans=-1;
	m[1]=-1;
	forint(i, 2, n) {
		m[i]=m[i-1];
		if(a[i]>a[i-1]) m[i]=a[i-1];
	}
	forint(i, 4, n) {
		if(m[i]<0) continue;
		int a1=a[i-1];
		int a2=a[i-2];
		int a3=(a[i-3]<a[i]?a[i-3]:m[i]);
		int s=a1+a2+a3;
		if(a[i]<s)
			ans=a[i]+s;
	}
	printf("%d\n", ans);
	return 0;
}
