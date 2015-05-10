#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long LL;

int main() {
	int t; cin>>t;
	while(t--) {
		LL n, m; cin>>n>>m;
		LL ans=1;
		for(LL x=2; x*x<=max(n,m); ++x) {
			LL p=1, q=1;
			while(n%x==0) p*=x, n/=x;
			while(m%x==0) q*=x, m/=x;
			if(p!=q) ans*=max(p, q);
		}
		if(n>1 && n!=m) ans*=n;
		if(m>1 && m!=n) ans*=m;
		cout<<ans<<endl;
	}
	return 0;
}
