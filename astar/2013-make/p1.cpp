#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
inline LL absval(LL x) { return x>0?x:-x; }
inline LL gcd(LL a, LL b) { return b==0?a:gcd(b, a%b); }
inline LL mul_mod(LL a, LL b, LL p) {
	LL x=0;
	for(; b; b>>=1, a=(a+a)%p)
		if(b&1) x=(x+a)%p;
	return x;
}
inline LL power(LL a, LL b, LL n) {
	LL x=1;
	for(; b; b>>=1, a=mul_mod(a,a,n))
		if(b&1)	x=mul_mod(x,a,n);
	return x;
}

// Miller-Rabin prime test
bool primetest(LL n) {
	int b[]={2, 3, 5, 7, 11,
		13, 17, 19, 23, 29,
		31, 37};
	bool flag=true;
	for(int i=0; flag && i<12 && b[i]<n; ++i) {
		LL t=n-1; int s=0;
		while(t%2==0) t/=2, ++s;
		LL res=power(b[i], t, n);
		if(res==1 || res==n-1) continue;
		for(flag=false; s>0; --s)
			if((res=mul_mod(res, res, n)) == n-1)
				flag=true;
	}
	return flag;
}

// return factor of n, if fail return n
LL pollard_rho(LL n, LL c) { 
	LL x, y, d, s, t;
	for(x=y=rand()%(n-1)+1, d=1, s=1, t=2; d==1; ) {
		x=(mul_mod(x,x,n)+c)%n;
		d=gcd(absval(x-y), n);
		if(++s==t) y=x, t<<=1;
	}
	return d;
}

// fast factorize
vector<LL> factorize(LL n) {
	vector<LL> p;
	while(n>1)
		if(primetest(n))
			p.push_back(n), n=1;
		else {
			LL d=n; while(d==n) d=pollard_rho(n, rand()%(n-1)+1);
			p.push_back(d), n/=d;
		}
	return p;
}

int main() {
	srand(123456789);
	int cs; cin>>cs;
	while(cs--) {
		LL n; //cin>>n;
		n=cs;
		vector<LL> p=factorize(n);
		sort(p.begin(), p.end());
		LL ans=1;
		for(size_t i=0, j=0; i<p.size(); i=j) {
			while(j<p.size() && p[j]==p[i]) ++j;
			ans*=(LL)(j-i+1);
		}
		for(int i=1; i<=(int)n; ++i) if(n%i==0) --ans;
		if(ans==0) printf("correct. n=%d\n",cs); else {
			printf("err! n=%d delta=%d\n", cs,(int)ans);
			for(size_t i=0; i<p.size(); ++i) printf("%d ",p[i]); printf("\n");
			for(;;);
		}
		//cout<<ans<<endl;
	}
	return 0;
}
