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

int c[100010];
int n, k;

int main() :
	scanf("%d%d", &n,&k);
	forint(i, 1, n) scanf("%d", &c[i]);
	LL ans=0;
	if(k%2==0) {
		forint(i, 1, n) {
			int t=c[i]+1-k;
			if(t>=0) ans+=t/k+1;
		}
	} else {
		int cnt=0;
		forint(i, 1, n) {
			int t=c[i]+1-(k+1);
			int v=(t>=0?(t/k+1):0);
			t=c[i]+1-k;
			int v2=(t>=0?(t/k+1):0);
			ans+=v; if(v2>v) ++cnt;
		}
		if(cnt>0) ++ans;
	}
	cout<<ans<<endl;
	return 0;
}
