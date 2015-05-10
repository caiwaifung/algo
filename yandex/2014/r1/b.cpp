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

const int MAXN=100010;

int a[MAXN], n;
LL f[MAXN];

LL g2(LL p1, LL p2) {
	return abs(p1-p2);
}
LL g3(LL p1, LL p2, LL p3) {
	LL tmp=1LL<<60;
	tmp=min(tmp, abs(p1-p2)+abs(p1-p3));
	tmp=min(tmp, abs(p2-p1)+abs(p2-p3));
	tmp=min(tmp, abs(p3-p1)+abs(p3-p2));
	return tmp;
}

int main() {
	scanf("%d", &n); forint(i, 1, n) scanf("%d", &a[i]);
	sort(a+1, a+n+1);
	f[0]=0;
	f[1]=1LL<<60;
	forint(i, 2, n) {
		f[i]=f[i-2]+g2(a[i-1], a[i]);
		if(i>=3) f[i]=min(f[i], f[i-3]+g3(a[i-2],a[i-1],a[i]));
	}
	cout<<f[n]<<endl;
	return 0;
}
