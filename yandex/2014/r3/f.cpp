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

int f[7700][7700];

int main() {
	int N; cin>>N;
	fillchar(f, 1);
	forint(l, 1, N) {
		forint(n, 0, l-1) f[n][l]=0;
		forint(n, l, N) {
			//printf("%d %d\n",l,n);
			VI a;
			for(int i=0, j=n-l; i<=j; ++i,--j)
				a.PB(f[i][l]^f[j][l]);
			//printf("@1\n");
			sort(a.begin(), a.end());
			a.erase(unique(a.begin(), a.end()), a.end());
			size_t i=0;
			int cur=0;
			while(1) {
				if(i>=a.size() || cur!=a[i]) break;
				++i, ++cur;
			}
			f[n][l]=cur;
		}
	}
	int i=N;
	forint(j, 1, i) printf("%c", f[i][j]>0?'F':'S');
	printf("\n");
	return 0;
}
