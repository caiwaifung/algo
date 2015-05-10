#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second


int main() {
	int csn; cin>>csn;
	forint(cs, 1, csn) {
		double C, F, X; cin>>C>>F>>X;
		double ans=X/2., cur=0;
		for(int i=1; ; ++i) {
			cur+=C/(2.+F*(i-1));
			if(cur>ans) break;
			ans=min(ans, cur+X/(2.+i*F));
		}
		cout<<"Case #"<<cs<<": ";
		printf("%.9lf\n", ans);
	}
	return 0;
}
