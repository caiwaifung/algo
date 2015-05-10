#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXN=100010;

int a[MAXN];
int n, x, k;

void solve() {
	if(x==0) {
		LL ans=0;
		for(int i=1; i<=n; ++i) ans+=a[i];
		ans=(ans-1)/k+1;
		cout<<ans<<endl;
		return;
	}
	if(k==0) {
		LL ans=0;
		for(int i=1; i<=n; ++i) ans+=(a[i]-1)/x+1;
		cout<<ans<<endl;
		return;
	}
	LL t=0, r=0;
	for(int i=1; i<=n; ++i) {
		t+=a[i]/x; a[i]%=x;
		r+=a[i];
	}
	if((r-1)/k+1<=t) { // can solved in t days
		LL le=0, ri=t;
		while(le<ri) {
			LL d=(le+ri)/2;
			LL re=(t-d)*x+r;
			if((re-1)/k+1<=d)
				ri=d;
			else le=d+1;
		}
		cout<<le<<endl;
	} else {
		sort(a+1, a+n+1);
		for(int i=n; i>=1; --i) {
			r-=a[i];
			++t;
			if((r-1)/k+1<=t) {
				cout<<t<<endl;
				return;
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &n,&x,&k);
	for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
	solve();
	return 0;
}
