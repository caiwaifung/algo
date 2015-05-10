//  19:12 - 19:20
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
typedef long long LL;

const int MAXN=111;
const double PI=acos(-1);
const double EPS=1e-8;

int sgn(double x) {
	return x<-EPS ? -1 : x>EPS;
}

struct Point {
	double x, y;
	Point() : x(0), y(0) {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator -(const Point &p) const {
		return Point(x-p.x, y-p.y);
	}
	friend double dot(Point p1, Point p2) {
		return p1.x*p2.x+p1.y*p2.y;
	}
	friend double dot(Point p0, Point p1, Point p2) {
		return dot(p1-p0, p2-p0);
	}
	friend double mult(Point p1, Point p2) {
		return p1.x*p2.y-p1.y*p2.x;
	}
	friend double mult(Point p0, Point p1, Point p2) {
		return mult(p1-p0, p2-p0);
	}
	double len() {
		return sqrt(x*x+y*y);
	}
} a[MAXN];

double area2(Point pa, Point pb, double r) {
	if (pa.len()<pb.len()) swap(pa, pb);
	if (sgn(pb.len())==0) return 0.;
	double a=pb.len(), b=pa.len(), c=(pa-pb).len();
	double cosB=dot(pb,pb-pa)/a/c, sinB=fabs(mult(pb,pb-pa)/a/c);
	double cosC=dot(pa,pb)/a/b, sinC=fabs(mult(pa,pb)/a/b);
	double B=atan2(sinB, cosB), C=atan2(sinC, cosC);
	double S, h, theta;
	if (a>r) { S=C/2.*r*r; h=a*b*sinC/c;
		if (h<r && B<PI/2.) S-=acos(h/r)*r*r-h*sqrt(r*r-h*h);
	}
	else if (b>r) { theta=PI-B-asin(sinB/r*a);
		S=.5*a*r*sin(theta)+(C-theta)/2.*r*r;
	} else
		S=.5*sinC*a*b;
	return S;
}

int n, r;

int main() {
	while(scanf("%d%d", &n,&r)!=EOF) {
		forint(i, 1, n) scanf("%lf%lf", &a[i].x,&a[i].y);
		double ans=0.;
		a[0]=a[n];
		forint(i, 1, n) {
			double tmp=area2(a[i-1], a[i], r);
			if(mult(a[i-1], a[i])>0) tmp=-tmp;
			ans+=tmp;
		}
		ans=fabs(ans);
		printf("%.9lf\n", ans);
	}
	return 0;
}
