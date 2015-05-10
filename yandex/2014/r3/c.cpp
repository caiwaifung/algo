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

const int MAXN=300010;

int p[MAXN];
int a[MAXN];
int n, d;

int main() {
	scanf("%d%d", &n,&d);
	forint(i, 1, n) scanf("%d", &a[i]);
	map<LL,int> lst;
	forint(i, 1, n) p[i]=0;
	forint(i, 1, n) {
		for(int t=-1; t<=1; t+=2) {
			LL y=a[i]+LL(d)*LL(t);
			if(lst.find(y)!=lst.end()) {
				int j=lst[y];
				p[i]=max(p[i], j);
			}
		}
		lst[(LL)a[i]]=i;
	}
	LL ans=0;
	int j=0;
	forint(i, 1, n) {
		j=max(j, p[i]);
		ans+=j;
	}
	cout<<ans<<endl;
	return 0;
}
