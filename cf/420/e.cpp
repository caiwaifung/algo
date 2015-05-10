#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define sqr(x) ((x)*(x))

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const double EPS=1e-8;
const double PI=acos(-1.);

int sgn(double x, double e=EPS) {
	return x<-e ? -1 : x>e;
}

struct Point {
	double x, y;
	void read() { scanf("%lf%lf",&x,&y); }
	Point(double x, double y) : x(x), y(y) {}
	Point() : x(0), y(0) {}
	Point operator +(const Point &p) const {
		return Point(x+p.x, y+p.y);
	}
	Point operator -(const Point &p) const {
		return Point(x-p.x, y-p.y);
	}
	Point operator *(double b) const {
		return Point(x*b, y*b);
	}
	Point operator /(double b) const {
		return Point(x/b, y/b);
	}
	friend double mult(Point p1, Point p2) {
		return p1.x*p2.y - p1.y*p2.x;
	}
	friend double dot(Point p1, Point p2) {
		return p1.x*p2.x + p1.y*p2.y;
	}
	friend double mult(Point p0, Point p1, Point p2) {
		return mult(p1-p0, p2-p0);
	}
	friend double dot(Point p0, Point p1, Point p2) {
		return dot(p1-p0, p2-p0);
	}
	double atan() const {
		return atan2(y, x);
	}
	double len() const {
		return sqrt(x*x+y*y);
	}
};

int cross_cc(Point p1, double r1, Point p2, double r2, 
		Point &cp1, Point &cp2) {
	double mx=p2.x-p1.x, sx=p2.x+p1.x, mx2=mx*mx;
	double my=p2.y-p1.y, sy=p2.y+p1.y, my2=my*my;
	double sq=mx2+my2, d=-(sq-sqr(r1-r2))*(sq-sqr(r1+r2));
	if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
	double x=mx*((r1+r2)*(r1-r2) + mx*sx) + sx*my2;
	double y=my*((r1+r2)*(r1-r2) + my*sy) + sy*mx2;
	double dx=mx*d, dy=my*d; sq*=2.;
	cp1=Point((x-dy)/sq, (y+dx)/sq);
	cp2=Point((x+dy)/sq, (y-dx)/sq);
	if(sgn(d)>0) return 2; else return 1;
}

const int MAXN=20010;

Point a[MAXN]; double r[MAXN];
int n, d;

vector<pair<double,int> > lst;

void add(Point p1, Point p2) {
	double a1=p2.atan();
	double a2=p1.atan();
	if(a1>a2) a2+=PI*2;
	lst.PB(MP(a1, 1));
	lst.PB(MP(a2, -1));
	lst.PB(MP(a1+PI*2, 1));
	lst.PB(MP(a2+PI*2, -1));
}

int main() {
	scanf("%d%d",&n,&d);
	forint(i, 1, n) a[i].read(), scanf("%lf", &r[i]);
	int bas_ans=0;
	lst.clear();
	forint(i, 1, n) {
		if(sgn(a[i].len()-r[i])<=0) {
			forint(ct, 1, 11) {
				if(sgn(r[i]-a[i].len()-ct*d)>=0) {
					++bas_ans;
					continue;
				}
				if(sgn(a[i].len())==0)
					continue;
				Point p1, p2;
				cross_cc(Point(), ct*d, a[i], r[i], p1, p2);
				if(sgn(mult(a[i], p1))<0) swap(p1, p2);
				add(p1, p2);
			}
		} else {
			int t=int(a[i].len()/d);
			forint(ct, max(1, t-11), t+11) {
				Point p1, p2;
				if(0==cross_cc(Point(), d*ct, a[i], r[i], p1, p2))
					continue;
				if(sgn(mult(a[i], p1))<0) swap(p1, p2);
				add(p1, p2);
			}
		}
	}
	sort(lst.begin(), lst.end());
	int ans=0, cur=0;
	for(size_t i=0; i<lst.size(); ) {
		double c=lst[i].fi;
		int a=0, b=0;
		while(i<lst.size() && sgn(lst[i].fi-c)==0) {
			if(lst[i].se>0) ++a; else ++b;
			++i;
		}
		cur+=a;
		if(cur>ans) ans=cur;
		cur-=b;
	}
	printf("%d\n", ans+bas_ans);
	return 0;
}
