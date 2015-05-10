#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;

const int MAXN=33;

LL C[MAXN][MAXN];
LL ca[MAXN][MAXN], cb[MAXN][MAXN];
int n;

LL gcd(LL a, LL b) {
	return b==0 ? a : gcd(b,a%b);
}

void adjust(LL &a, LL &b) {
	LL k=gcd(a, b);
	a/=k, b/=k;
	if(b<0) a=-a, b=-b;
}

void add(LL &a, LL &b, LL xa, LL xb) {
	adjust(a, b); adjust(xa, xb);
	LL k=gcd(b, xb);
	LL u=b/k, ub=xb/k;
	a*=ub; b*=ub;
	xa*=u; xb*=u;
	a+=xa;
	adjust(a, b);
}

int main() {
	int cs; for(cin>>cs; cs--; ) {
		for(int i=0; i<MAXN; ++i) C[i][0]=C[i][i]=1LL;
		for(int i=1; i<MAXN; ++i) for(int j=1; j<i; ++j) C[i][j]=C[i-1][j-1]+C[i-1][j];
		cin>>n;
		ca[0][0]=0, cb[0][0]=1;
		ca[0][1]=1, cb[0][1]=1;
		for(int k=1; k<=n; ++k) {
			for(int i=0; i<=k+1; ++i) {
				ca[k][i]=0;
				cb[k][i]=1;
			}
			for(int i=0; i<=k+1; ++i)
				add(ca[k][i], cb[k][i], C[k+1][i], 1);
			for(int i=0; i<=k-1; ++i)
				for(int j=0; j<=i+1; ++j)
					add(ca[k][j], cb[k][j], -ca[i][j]*C[k+1][i], cb[i][j]);
			add(ca[k][0], cb[k][0], -1, 1);
			for(int i=0; i<=k+1; ++i) {
				cb[k][i]*=(LL)(k+1);
				adjust(ca[k][i], cb[k][i]);
			}
		}
		for(int i=n+1; i>=0; --i)
			cout<<ca[n][i]<<"/"<<cb[n][i]<<(i>0?' ':'\n');
	}
	return 0;
}
