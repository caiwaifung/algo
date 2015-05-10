#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<LL> VLL;
typedef pair<int,int> PII;
#define fi first
#define se second
#define PB push_back
#define MP make_pair
template<class T> bool setmin(T &a, T b) {
	if(b<a) {a=b; return true;} else return false;
}
template<class T> bool setmax(T &a, T b) {
	if(b>a) {a=b; return true;} else return false;
}
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, (x), sizeof(a))

const LL MOD=1000000000+7;
const int MAXN=2010;

int a[MAXN]; int n;
int p[MAXN], len;

LL f[MAXN], fac[MAXN], inv_fac[MAXN];
bool used[MAXN];

LL pow(LL a, LL b, LL m) {
	LL x=1;
	for(; b>0; b>>=1, a=(a*a)%m)
		if(b&1) x=(x*a)%m;
	return x;
}

int main() {
	scanf("%d", &n); forint(i, 1, n) scanf("%d", a+i);

	fac[0]=1;
	forint(i, 1, n) fac[i]=(fac[i-1]*i)%MOD;
	forint(i, 0, n) inv_fac[i]=pow(fac[i], MOD-2, MOD);

	fillchar(used, false);
	len=0; forint(i, 1, n) if(a[i]<0) p[++len]=i; else used[a[i]]=true;

	f[0]=1;
	forint(i, 1, len) {
		f[i]=fac[len];
		forint(j, 1, i) if(!used[p[j]]) {
			f[i]=(f[i]-f[j-1]*fac[len-j])%MOD;
			printf("i=%d j=%d t=%lld\n",i,j,f[j-1]*fac[len-j]);
		}
		//cout<<"f["<<i<<"]="<<f[i]<<endl;
		f[i]=(f[i]*inv_fac[len-i])%MOD;
		f[i]=(f[i]+MOD)%MOD;
		//cout<<"f["<<i<<"]="<<f[i]<<endl;
	}
	LL ans=f[len];
	forint(i, 1, n) if(a[i]==i) ans=0;
	ans=(ans%MOD+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}

