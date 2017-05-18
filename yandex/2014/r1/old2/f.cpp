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
const int MAXK=1000010;
const int MOD=int(1e9)+7;

int x[MAXK], y[MAXK];
int a[MAXN];
int n, k;

int main() {
	scanf("%d%d", &k,&n);
	forint(i, 1, n) scanf("%d", &a[i]);
	if(k<n) {
		int ans=0;
		forint(i, 1, n) {
			int cnt=0;
			forint(j, 1, n) if(a[j]<a[i]) ++cnt;
			if(cnt<=k) ans=max(ans, a[i]);
		}
		ans%=MOD;
		printf("%d\n", ans);
	} else {
		k=k-n+3;
		x[1]=1, y[1]=0;
		x[2]=0, y[2]=1;
		int p=-1;
		forint(i, 3, k) {
			x[i]=(x[i-1]+x[i-2])%MOD;
			y[i]=(y[i-1]+y[i-2])%MOD;
			if(p<0) {
				if(x[i-1]+x[i-2]>=MOD || y[i-1]+y[i-2]>=MOD)
					p=i-1;
			}
		}
		if(p<0) p=k;
		PII m=MP(-1,-1); LL bst=0;
		forint(i, 1, n) for(int j=i-1; j<=i+2; j+=2) {
			if(j<1 || j>n) continue;
			LL tmp=LL(x[p])*a[i]+LL(y[p])*a[j];
			if(tmp>bst) bst=tmp, m=MP(a[i],a[j]);
		}
		LL ans=LL(m.fi)*x[k]+LL(m.se)*y[k];
		ans=ans%MOD;
		printf("%d\n", int(ans));
	}
	return 0;
}
