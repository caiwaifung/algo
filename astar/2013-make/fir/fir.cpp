#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

double p[444][444];
int main() {
	int N=400;
	memset(p, 0, sizeof(p));
	for(int i=0; i<=N; ++i) p[0][i]=1;
	for(int i=1; i<=N; ++i) {
		p[i][0]=0;
		for(int j=1; j<=N; ++j) {
			p[i][j]=0;
			for(int k=1; k<=i; ++k)
				p[i][j]+=(p[i-k][j-1]*p[k-1][j-1])/(double)i;
		}
	}
	int t; scanf("%d", &t); while(t--) {
		int n; scanf("%d", &n);
		double ans=0;
		for(int i=1; i<=n; ++i)
			ans+=i*(p[n][i]-p[n][i-1]);
		printf("%.5lf\n", ans);
	}
	return 0;
}
