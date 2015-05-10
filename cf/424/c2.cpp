#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

int t[1000010];
int n;

int xo(int x) {
	int xs[4]={x, 1, x+1, 0};
	return xs[x%4];
}
int xr(int l, int r) {
	if(l>r) return 0;
	return xo(r)^xo(l-1);
}

int main() {
	n=0;
	while(1){
	int ans=0; ++n;
	//scanf("%d", &n);
	/*
	forint(i, 1, n) {
		int x; scanf("%d", &x);
		ans^=x;
	}
	*/

	int tans=ans;
	t[0]=0;
	forint(i, 1, n) t[i]=t[i-1]^i;
	forint(i, 1, n) {
		int u=n/i;
		if(u%2!=0) {
			ans^=t[i-1];
		}
		ans^=t[n%i];
	}
	//printf("%d\n", ans);

	swap(ans,tans);
	forint(i, 2, n) {
		int x;
		if(n%i!=0) x=n+i-(n%i); else x=n;
		if((x/i)%2==1) ans^=t[n%i+(n%i==0?i-1:0)];
		else if(n%i!=0) ans^=t[i-1]^t[n%i];
	}

	if(ans!=tans) {printf("n=%d ans=%d tans=%d\n", n,ans,tans); for(;;); } else printf("k %d\n",n);
	}
	return 0;
}
