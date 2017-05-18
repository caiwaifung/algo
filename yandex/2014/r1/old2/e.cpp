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

int a[22], n;
int ans;
bool ok[55];

bool check() {
	forint(i, 1, n) {
		if(!ok[a[i]]) return false;
	}
	return true;
}

void dfs(int num, int cur) {
	if(check()) {
		//printf("ans=%d\n", ans); forint(i, 1, num) printf("%d ", b[i]); printf("\n");
		ans=num; return;
	}
	if(num+1>=ans) return;
	bool o[55]; memmove(o, ok, sizeof(o));
	while(cur<=50) {
		forint(k, 0, 50-cur) if(o[k]) ok[k+cur]=true;
		dfs(num+1, cur);
		++cur;
		memmove(ok, o, sizeof(o));
	}
}
/*
void d(int num, int cur) {
	if(num>=6) return;
	++ans;
	while(cur<=50) {
		b[num+1]=cur;
		d(num+1, cur+1);
		++cur;
	}
}
*/

int main() {
	//ans=0; d(0, 1); cout<<ans<<endl;

	cin>>n; forint(i, 1, n) cin>>a[i];
	ans=6;

	fillchar(ok, false); ok[0]=true;
	dfs(0, 1);
	cout<<ans<<endl;
	return 0;
}
