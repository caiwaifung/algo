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

int d[111];
int n;

int main() {
	cin>>n; forint(i, 1, n) cin>>d[i];
	if(n==2) {
		printf("%s\n", (d[1]==1 && d[2]==1) ? "Unique" : "None");
		return 0;
	}
	int s=0; forint(i, 1, n) s+=d[i];
	if(s!=2*(n-1)) {
		printf("None\n"); return 0;
	}
	int c2=0;
	VI c; forint(i, 1, n) if(d[i]>=3) c.PB(d[i]); else if(d[i]==2) c2++;
	if(c.size()>0) {
		sort(c.begin(), c.end());
		if(c.size()>=4) {
			printf("Multiple\n"); return 0;
		}
		if(c.size()==1) {
			if(c2>1) {
				printf("Multiple\n"); return 0;
			}
		} else {
			if(c2>0) {
				printf("Multiple\n"); return 0;
			}
			if(c.size()==3 && c[0]!=c.back()) {
				printf("Multiple\n"); return 0;
			}
		}
	} else {
	}
	printf("Unique\n");
	return 0;
}
