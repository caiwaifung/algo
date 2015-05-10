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
int a, b, c;
LL ans;

void dfs(int cur, int i, int j, int k) {
	if(cur>pn) {
		ans+=a/i + b/j + c/k;
		return;
	}
	dfs(cur+1, i,j,k);
	for(int ti=i*p[cur]; ti<=a; ti*=p[cur]) dfs(cur+1, ti,j,k);
	for(int tj=j*p[cur]; tj<=b; tj*=p[cur]) dfs(cur+1, i,tj,k);
	for(int tk=k*p[cur]; tk<=c; tk*=p[cur]) dfs(cur+1, i,j,tk);
}

int main() {
	scanf("%d%d%d", &a,&b,&c);
	pn=0;
	for(int i=2; i<=2000; ++i) {
		bool flag=true;
		for(int j=2; j*j<=i; ++j)
			if(i%j==0) flag=false;
		if(flag) p[++pn]=i;
	}
	ans=0;
	dfs(1, 1,1,1);
	cout<<ans<<endl;
	return 0;
}
