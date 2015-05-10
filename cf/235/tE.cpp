#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back

int p[9999], pn;
const LL limit=2000LL * 2000LL * 2000LL;
LL ans;

void dfs(int cur, LL s) {
	if(cur>pn || s*p[cur]>limit) {
		++ans;
		if(ans%1000000==0) printf("ans=%lld\n",ans);
		return;
	}
	while(s<=limit) {
		dfs(cur+1, s);
		s*=p[cur];
	}
}

int main() {
	pn=0;
	for(int i=2; i<=2000; ++i) {
		bool flag=true;
		for(int j=2; j*j<=i; ++j)
			if(i%j==0) flag=false;
		if(flag) p[++pn]=i;
	}
	printf("pn=%d\n", pn);
	ans=0;
	dfs(1, 1);
	cout << ans << endl;
	return 0;
}
