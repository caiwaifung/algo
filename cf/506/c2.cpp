#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //
const int MAXN=100000;
const int MAXM=5050;

LL div_ceil(LL a, LL b) {
	if(b<=0) { printf("ERROR @ div_ceil\n"); exit(1); }
	if(a<0) return 0;
	return (a+b-1)/b;
}

int n, m, k; LL p;
LL h[MAXN], a[MAXN], t[MAXN], w[MAXN];
LL least[MAXM];

bool ok(LL X) {
	forn(i, n) {
		t[i]=div_ceil(h[i]+a[i]*m-X, p);
		w[i]=t[i]*p-(h[i]+a[i]*m-X);
	}
	LL sum_t=0;
	forn(i, n) sum_t+=t[i];
	if(sum_t>m*k) return false;
	fillchar(least, 0);
	forn(i, n) forint(j, 1, t[i]) {
		// find min k: we can beat j times during first k days
		LL k=div_ceil(j*p-h[i]-w[i], a[i])+1;
		if(k<0) continue;
		if(k>m) return false;
		least[k]+=1;
	}
	LL s=0;
	forintdown(i, m, 1) {
		s+=least[i];
		if(s>(m-i+1)*k) return false;
	}
	return true;
}

int main() {
	int _p;
	scanf("%d%d%d%d", &n,&m,&k,&_p); p=_p;
	forn(i, n) {
		int _h, _a; scanf("%d%d", &_h,&_a);
		h[i]=_h, a[i]=_a;
	}
	LL le=0, ri=LL(1e9 * 1e4);
	while(le<ri) {
		LL mid=(le+ri)/2;
		if(ok(mid))
			ri=mid;
		else
			le=mid+1;
	}
	cout<<le<<endl;
	return 0;
}
