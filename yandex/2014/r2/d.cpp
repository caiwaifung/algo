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

int a[100010];

const int N=100000;
int tr[100010];
void add(int x) {
	for(; x<=N; x+=(x&-x)) ++tr[x];
}
int get(int x) {
	int ans=0;
	for(; x>=1; x-=(x&-x)) ans+=tr[x];
	return ans;
}

int main() {
	int k; scanf("%d", &k);
	int n=1;
	while(n*(n-1)/2<k) ++n;

	fillchar(tr, 0);
	forint(i, 1, n) {
		int r=n-i;
		int t=r*(r-1)/2;
		int p=max(0, k-t); k-=p;
		int cur=p+1;
		a[i]=get(cur)+cur;
		add(cur);
	}
	printf("%d\n",n);
	forint(i, 1, n) printf("%d ", a[i]); printf("\n");

	return 0;
}
