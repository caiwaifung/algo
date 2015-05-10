#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>
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
typedef pair<int,int> PII;
typedef vector<PII> VPI;
typedef pair<double,double> PDD;

LL gcd(LL a, LL b) {
	return b==0?a:gcd(b,a%b);
}

int main() {
	freopen("A-large.in", "r", stdin);
	freopen("A.out", "w", stdout);
	int n; scanf("%d", &n);
	for(int cs=1; cs<=n; ++cs) {
		LL a, b; scanf("%I64d/%I64d", &a,&b);
		LL c=gcd(a, b); a/=c, b/=c;
		int d=0;
		while((1LL<<d)<b) ++d;
		if((1LL<<d)!=b) printf("Case #%d: impossible\n",cs); else {
			while(a>=2) a/=2, --d;
			printf("Case #%d: %d\n",cs,d);
		}
	}
	return 0;
}
