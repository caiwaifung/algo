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

const int MAXN=1001000;

LL a[MAXN], s[MAXN];
int n;

void solve() {
	{
	scanf("%d", &n);
	int p, q, r, s;
	scanf("%d%d%d%d",&p,&q,&r,&s);
	forint(i, 0, n-1) a[i+1]=((LL(i)*LL(p)+q)%LL(r)+LL(s));
	}
	s[0]=0;
	forint(i, 1, n) s[i]=s[i-1]+a[i];
	LL ans=1LL<<60;
	int j=1;
	forint(i, 1, n) {
		LL tmp=s[n]-s[i];
		LL p1, p2;
		while(1) {
			p1=s[j], p2=s[i]-s[j];
			if(p1<=p2) ++j;
			else break;
		}
		ans=min(ans, max(tmp,max(p1,p2)));
		p1=s[j-1], p2=s[i]-s[j-1];
		ans=min(ans, max(tmp,max(p1,p2)));
	}
	double t=double(s[n]-ans)/double(s[n]);
	printf("%.16lf\n", t);
}

int main() {
	int ncs; scanf("%d", &ncs);
	forint(cs, 1, ncs) {
		cerr<<cs<<endl;
		printf("Case #%d: ", cs);
		solve();
	}
	return 0;
}
