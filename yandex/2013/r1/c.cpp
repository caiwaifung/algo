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

int main() {
	int cs; cin>>cs;
	while(cs--) {
		LL n; cin>>n;
		int k, t=0; cin>>k;
		LL x=2;
		while(x*x<=n) {
			int c=0;
			while(n%x==0) n/=x, ++c;
			if(c>k) {
				if((c-k)%2==0) c=k; else c=k-1;
			}
			t+=c;
			++x;
		}
		k-=t;
		if(n>1) --k;
		cout<<(k<=0 ? "YES" : "NO")<<endl;
	}
	return 0;
}
