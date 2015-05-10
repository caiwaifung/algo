// 13:31 - 13:43 ac
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
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef pair<int, int> PII;
typedef long long LL;
typedef vector<int> VI;
typedef pair<LL,LL> PLL;
typedef long double LD;

const int MAXN=111;

struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x,&y);
	}
	bool operator <(const Point &p) const {
		return x<p.x || (x==p.x && y<p.y);
	}
	friend int mult(Point p0, Point p1, Point p2) {
		return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
	}
} a[MAXN*2];
int n;

void cal_convex() {
	//printf("cal_convex. n=%d\n",n);
	sort(a+1, a+n+1);
	//printf("cal_convex.\n"); fflush(stdout);
	static Point b[MAXN*2];
	int len=0;
	forint(i, 1, n) {
		while(len>=2 && mult(b[len-1],b[len],a[i])<=0) --len;
		b[++len]=a[i];
	//printf("i=%d len=%d\n",i,len);
	}
	//printf("len=%d\n",len);
	int t=len+1;
	forintdown(i, n, 1) {
		while(len>=t && mult(b[len-1],b[len],a[i])<=0) --len;
		b[++len]=a[i];
	}
	--len;
	n=len;
	forint(i, 1, n) a[i]=b[i];
}

double dis(Point p1, Point p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

double dis(Point p, Point p1, Point p2) {
	return abs(mult(p, p1, p2))/dis(p1, p2);
}

int main() {
	int cs=0;
	while(1) {
		scanf("%d", &n);
		if(n==0) break;
		forint(i, 1, n) a[i].read();
		cal_convex();
		//printf("done.\n");
		forint(i, 1, n) a[i+n]=a[i];
		double ans=1e50;
		forint(i, 1, n) {
			double tmp=0;
			forint(j, 1, n)
				tmp=max(tmp, dis(a[j],a[i],a[i+1]));
			ans=min(ans, tmp);
		}
		printf("Case %d: %.2lf\n",++cs,ans);
	}
	return 0;
}
