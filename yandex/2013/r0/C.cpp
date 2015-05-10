#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;

int main() {
	int n; scanf("%d", &n);
	LL ans1=(LL)n*(LL)(n+1)/2;
	LL x=0;
	for(LL b=1<<30, t=n; b>1; b>>=1)
		if(t>=b) {
			t-=b;
			if(t%2==0) x|=b;
		}
	if((n+1)/2%2==1) x|=1;
	cout<<x<<endl;
	LL ans2=n-x+1; if(x==0) ans2=0;
	cout<<ans1<<" "<<ans2<<endl;
	return 0;
}
