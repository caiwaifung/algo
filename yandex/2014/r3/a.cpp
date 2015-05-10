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

int d[MAXN];
int n;

int main() {
	fillchar(d, 0);
	scanf("%d", &n);
	forint(i, 1, n-1) {
		int a, b; scanf("%d%d", &a,&b);
		++d[a], ++d[b];
	}
	LL ans=0;
	forint(i, 1, n) {
		LL t=d[i];
		if(t>=2) ans+=t*(t-1)/2;
	}
	cout<<ans<<endl;
	return 0;
}
