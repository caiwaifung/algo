#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
#define MP make_pair
#define PB push_back

int gcd(int a, int b) {
	return b==0 ? a : gcd(b,a%b);
}
int lcm(int a, int b) {
	return a*b/gcd(a,b);
}

int main() {
	for(int n=1; n<=100; ++n) {
		int x=-1, xa,xb,xc;
		for(int a=1; a<=n; ++a)
		for(int b=1; b<=n; ++b)
		for(int c=1; c<=n; ++c) {
			int y=lcm(a,b); y=lcm(y,c);
			if(y>=x) x=y,xa=a,xb=b,xc=c;
		}
		printf("x=%5d  %3d %3d %3d\n",x,xa,xb,xc);
	}
	return 0;
}
