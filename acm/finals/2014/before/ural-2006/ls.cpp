#include <cstdlib>
#include <vector>
#include <iostream>
#include <cstring>
#include <set>
#include <cstdio>
using namespace std;

int n;

int main() {
	scanf("%d", &n);
	int p[4]={0}, x;
	for(int i=1; i<=n; ++i) scanf("%d", &x), ++p[x];
	int c[111][111];
	for(int i=0; i<=100; ++i) c[i][0]=c[i][i]=1;
	for(int i=1; i<=100; ++i)
		for(int j=1; j<=i-1; ++j)
			c[i][j]=min(10, c[i-1][j-1]+c[i-1][j]);
	int ans=1;
	for(int i=1; i<=3; ++i) {
		ans*=c[n][p[i]];
		n-=p[i];
	}
	printf("%s\n", ans>=6 ? "Yes" : "No");
	return 0;
}
