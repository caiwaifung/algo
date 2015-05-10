// 16:50
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
using namespace std;

#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forn(i, n) forint(i, 0, (n)-1)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;
typedef long long LL;
typedef vector<int> VI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const double PI=acos(-1);

double area(double a, double b, double c) {
	double p=(a+b+c)/2;
	double ans=p*(p-a)*(p-b)*(p-c);
	if(ans<1e-8) ans=0; else ans=sqrt(ans);
	return ans;
}

double angle(double r, double x) {
	double t=x*x/(2*r*r);
	t=1-t;
	if(t<-1) t=-1;
	if(t>1) t=1;
	return acos(t);
}

double go1(VI a) {
	double le=0, ri=1e10;
	forn(i, a.size()) le=max(le, a[i]/2.);
	double ans=0;
	forn(tt, 99) {
		double mid=(le+ri)/2;
		double tot=0.;
		forn(i, a.size()) tot+=angle(mid, a[i]);
		if(tot<PI*2) ri=mid;
		else {
			le=mid;
			ans=0;
			forn(i, a.size()) ans+=area(a[i], le, le);
		}
	}
	return ans;
}
double go2(VI a) {
	//return 0;
	double le=0, ri=1e10;
	forn(i, a.size()) le=max(le, a[i]/2.);
	sort(a.begin(), a.end());
	double maxl=a.back(); a.pop_back();
	double ans=0;
	forn(tt, 99) {
		double mid=(le+ri)/2;
		double tot=0.;
		forn(i, a.size()) tot+=angle(mid, a[i]);
		tot-=angle(mid, maxl);
		printf("mid=%.9lf tot=%.9lf\n",mid,tot);
		if(tot<0) le=mid;
		else {
			ri=mid;
			forn(i, a.size()) ans+=area(a[i], le, le);
			ans-=area(maxl, le, le);
		}
	}
	printf("le=%.9lf\n",le);
	return ans;
}	

void solve(int cs, int n) {
	VI a(n);
	forn(i, n) scanf("%d", &a[i]);
	double ans=go1(a);
	if(ans==0) ans=go2(a);
	printf("Case %d: %.9lf\n", cs,ans);
}

int main() {
	int cs=0;
	while(1) {
		int n;
		scanf("%d", &n);
		if(n==0) break;
		solve(++cs, n);
	}
	return 0;
}
