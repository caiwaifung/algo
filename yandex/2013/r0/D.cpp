#include <iostream>
#include <cstdio>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b) {
	return b==0 ? a : gcd(b,a%b);
}

int main() {
	int a, b; scanf("%d%d", &a,&b);
	if(b==1) printf("infinity\n"); else {
		double rb=1.;
		for(int i=1; i<=a+1; ++i) rb*=(double)(b-1);
		double ans=0., fb=1;
		for(int n=1; n<=1000000; ++n) {
			fb*=b;
			double fa=rb;
			for(int i=1; i<=a; ++i) fa*=n;
			//printf("%.1lf %.1lf\n",fa,fb);
			ans+=fa/fb;
		}
		LL x=(LL)(ans+0.1);
		LL y=(LL)(rb+0.1);
		LL t=gcd(x, y);
		x/=t;
		y/=t;
		cout<<x<<"/"<<y<<endl;
	}
	return 0;
}
