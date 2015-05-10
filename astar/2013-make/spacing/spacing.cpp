#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN=50010;

int a[MAXN], sa[MAXN];
int w, n, d;
int f[MAXN], sf[MAXN];

bool ok1(int i, int j) {
	return sa[i]-sa[j]+(i-j-1) <= w; 
}
bool ok2(int i, int j) {
	return sa[i]-sa[j]+(i-j-1)*d >= w; 
}

bool check(int _d) {
	d=_d;
	f[0]=1; sf[0]=1;
	int j1=0, j2=0;
	for(int i=1; i<=n; ++i) {
		while(j1+1<i && !ok1(i,j1)) ++j1;
		while(j2+1<i && ok2(i,j2+1)) ++j2;
		f[i]=0;
		if(ok1(i,j1) && ok2(i,j2)) {
			int tf=sf[j2];
			if(j1>0) tf-=sf[j1-1];
			if(tf>0) f[i]=1;
		}
		sf[i]=f[i]+sf[i-1];
	}
	for(int i=n; i>=0; --i)
		if(sa[n]-sa[i]+(n-i-1)<=w && f[i]>0)
			return true;
	return false;
}

void solve() {
	sa[0]=0; for(int i=1; i<=n; ++i) sa[i]=sa[i-1]+a[i];
	int le=1, ri=w;
	while(le<ri) {
		int mid=(le+ri)/2;
		if(check(mid))
			ri=mid;
		else le=mid+1;
	}
	printf("%d\n", le);
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &w,&n);
		for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
		solve();
	}
	return 0;
}

