#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

const int MAXN=1010;
typedef pair<int,int> PII;

int gcd(int a, int b) {
	return b==0 ? a : gcd(b,a%b);
}

int x[MAXN], y[MAXN];
int n;

void solve() {
	int ret=0;
	for(int i=1; i<=n; ++i) {
		map<PII,int> ans;
		int tmp=0;
		int x0=x[i], y0=y[i];
		for(int j=1; j<=n; ++j) {
			if(x[i]==x[j] && y[i]==y[j]) {
				++tmp; continue;
			}
			int a=y[j]*x0-y0*x[j];
			int b=x0*x[j]*(x[j]-x0);
			int t=gcd(a, b);
			a/=t, b/=t;
			if(b<0) a=-a, b=-b;
			if(a>=0) continue;
			ans[make_pair(a,b)]++;
		}
		int best=0;
		for(map<PII,int>::iterator it=ans.begin(); it!=ans.end(); ++it)
			best=max(best, it->second);
		ret=max(ret, best+tmp);
	}
	/*
	int ans=0;
	for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) {
		if(x[i]==x[j] || y[i]==y[j]) continue;
		int b=(y[i]*x[j]*x[j]-y[j]*x[i]*x[i]);
		b/=(x[i]*x[j]*x[j]-x[j]*x[i]*x[i]);
		int a=(y[i]-b*x[i])/x[i]/x[i];
		if(a*x[i]*x[i]+b*x[i]!=y[i]) continue;
		if(a*x[j]*x[j]+b*x[j]!=y[j]) continue;
		int tmp=0;
		for(int k=1; k<=n; ++k)
			if(a*x[k]*x[k]+b*x[k]==y[k]) ++tmp;
		ans=max(ans,tmp); 
	}
	if(ans!=ret) printf("error (%d) ",ans); else printf("ans=%d ",ans);
	*/
	printf("%d\n", ret);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i=1; i<=n; ++i) scanf("%d%d", &x[i],&y[i]);
		solve();
	}
	return 0;
}

