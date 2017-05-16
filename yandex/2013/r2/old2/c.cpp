#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

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
typedef pair<LL,LL> PLL;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;

struct Point {
	int x, y;
	double ang;
	bool operator <(const Point &p) const {
		return ang<p.ang;
	}
};

LL mult(Point p1, Point p2) {
	return LL(p1.x)*LL(p2.y) - LL(p2.x)*LL(p1.y);
}

void sort_ps(vector<Point> &a) {
	forn(i, a.size()) a[i].ang=atan2(a[i].y, a[i].x);
	sort(a.begin(), a.end());
}

pair<double,LL> cal(vector<Point> a) {
	sort_ps(a);
	int n=a.size();
	a.resize(n*2);
	forint(i, n, 2*n-1) a[i]=a[i-n];

	vector<double> sx, sy;
	sx.resize(n*2);
	sy.resize(n*2);
	forn(i, n*2) {
		sx[i]=a[i].x; if(i>0) sx[i]+=sx[i-1];
		sy[i]=a[i].y; if(i>0) sy[i]+=sy[i-1];
	}

	int j=0;
	double ans=0;
	forn(i, n) {
		if(j<i) j=i;
		while(j+1<n*2 && mult(a[i],a[j+1])>0)
			++j;
		double tx=sx[j]-sx[i];
		double ty=sy[j]-sy[i];
		ans+=a[i].x*ty-a[i].y*tx;
	}
	return MP(ans, LL(n)*(n-1));
}

int main() {
	int n;
	scanf("%d", &n);
	vector<Point> a(n);
	forn(i, n) scanf("%d%d", &a[i].x,&a[i].y);
	pair<double,LL> ans=MP(0., 0);
	forn(i, n) {
		vector<Point> b;
		forint(j, i+1, n-1) {
			Point t;
			t.x=a[j].x-a[i].x;
			t.y=a[j].y-a[i].y;
			b.PB(t);
		}
		pair<double,LL> tmp=cal(b);
		ans.fi+=tmp.fi;
		ans.se+=tmp.se;
	}
	double t=double((long double)ans.fi/ans.se);
	printf("%.16lf\n", t);
	return 0;
}
