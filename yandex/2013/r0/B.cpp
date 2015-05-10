#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int n; scanf("%d", &n);
	for(int k=1; k<=n; ++k) {
		int t=k*k-1;
		int cnt=0;
		for(int i=2; i*i<=t; ++i)
			while(t%i==0) {
				++cnt; t/=i;
			}
		if(t>1) ++cnt;
		if(cnt==2) printf("%d\n", k);
	}
	return 0;
}
