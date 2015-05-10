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

const int MAXN=10;

int a[MAXN];
int n, ans;

void dfs(int cur, int sum) {
	if(cur>n) {
		ans=max(ans, sum);
		return;
	}
	sum+=a[cur];
	int x[9], len=0;
	while(sum>0) x[++len]=sum%10, sum/=10;
	int p[9];
	forint(i, 1, len) p[i]=i;
	do {
		sum=0;
		forint(i, 1, len) sum=sum*10+x[p[i]];
		dfs(cur+1, sum);
	} while(next_permutation(p+1, p+len+1));
}

int main() {
	scanf("%d", &n); forint(i, 1, n) scanf("%d", &a[i]);
	ans=0;
	dfs(1, 0);
	cout<<ans<<endl;
	return 0;
}
