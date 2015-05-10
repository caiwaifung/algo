#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long int64;
typedef unsigned long long qword;
template <class T> T abs_val(T x) { return x > 0 ? x : -x; }
template <class T> T sqr(T x) { return x*x; }
template <class T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a%b); }
template <class T> void set_max(T &a, T b) { if (a < b) a = b; }
template <class T> void set_min(T &a, T b) { if (a > b) a = b; }
#define fillchar(a, x) memset(a, x, sizeof(a))
#define movechar(a, b) memmove(b, a, sizeof(a))
#define forn(i, n) for (int i = 0; i < (int)(n); ++ i)
#define forint(i, s, t) for (int i = (int)(s); i <= (int)(t); ++ i)
#define forintdown(i, s, t) for (int i = (int)(s); i >= (int)(t); -- i)
#define forall(it, a) for (typeof(a.begin()) it = a.begin(); it != a.end(); ++ it)

const int MAX_N=55;

struct Point {
	int x, y;
	Point(int _x=0, int _y=0) : x(_x), y(_y) { }
	void read() { scanf("%d%d", &x, &y); }
	Point operator +(const Point &t) { return Point(x+t.x, y+t.y); }
	Point operator -(const Point &t) { return Point(x-t.x, y-t.y); }
};

Point p[MAX_N], v[MAX_N];
int n;

int main() {
	scanf("%d", &n); forint(i, 1, n) p[i].read(), v[i].read();
	int ans=0;
	forint(i, 1, n) forint(j, i+1, n) {
		//printf("i=%d j=%d\n",i,j);
		Point a1=p[j]-p[i], b1=v[j]-v[i];
		int curtt=0;
		vector<pair<double, double> > times;
		forint(k, 1, n) {
			Point a2=p[k]-p[i], b2=v[k]-v[i];
			int a = (b1.x*b2.y - b1.y*b2.x);
			int b = (a1.x*b2.y+b1.x*a2.y) - (a1.y*b2.x+b1.y*a2.x);
			int c = (a1.x*a2.y - a1.y*a2.x);
			//printf(" a=%d b=%d c=%d\n",a,b,c);
			if(a==0 && b==0 && c==0) {
				++curtt; continue;
			}
			double x1, x2;
			if (a!=0) {
				int64 delta = (int64)b*(int64)b-4*(int64)a*(int64)c;
				if(delta<0) continue;
				x1=(-b+sqrt((double)delta))/2./(double)a;
				x2=(-b-sqrt((double)delta))/2./(double)a;
			} else {
				if(b==0) continue;
				x1=x2= -(double)c/(double)b;
			}
			times.push_back(make_pair(x1, x2));
			//printf("  %.4lf %.4lf\n", x1,x2);
		}
		//printf("curt=%d\n",curtt);
		set_max(ans, curtt);
		forn(k, times.size()) forn(kk, 2) {
			double t = (kk==0?times[k].first:times[k].second);
			if(abs_val(a1.x+t*b1.x)<1E-8 && abs_val(a1.y+t*b1.y)<1E-8) continue;
			if(t<-1E-8 || t>1+1E-8) continue;
			int cur=0;
			forn(k2, times.size())
				if(abs_val(times[k2].first-t)<1E-8 || abs_val(times[k2].second-t)<1E-8)
					++cur;
			set_max(ans, cur+curtt);
		//	printf("  cur=%d\n",cur);
		}
		//printf("\n");
	}
	printf("%d\n", ans);
	return 0;
}
