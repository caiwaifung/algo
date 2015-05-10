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
	int x, y, z;

	void read() {
		scanf("%d%d%d",&x,&y,&z);
		x*=4, y*=4, z*=4;
	}
	friend int mult(Point p0, Point p1, Point p2) {
		return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
	}
	friend int dot(Point p0, Point p1, Point p2) {
		return (p1.x-p0.x)*(p2.x-p0.x) + (p1.y-p0.y)*(p2.y-p0.y);
	}

};

bool inside(Point p, Point a[]) {
	int area=mult(a[0], a[1], a[2]);
	if(area<0) reverse(a, a+3);
	if(mult(p, a[0], a[1])<=0) return false;
	if(mult(p, a[1], a[2])<=0) return false;
	if(mult(p, a[2], a[0])<=0) return false;
	return true;
}

bool onside(Point p, Point p1, Point p2) {
	if(mult(p, p1, p2)!=0) return false;
	return dot(p, p1, p2)<=0;
}

int main() {
	Point p[4];
	forn(i, 4) p[i].read();
	Point c;
	c.x=c.y=c.z=0;
	forn(i, 4) {
		c.x+=p[i].x;
		c.y+=p[i].y;
		c.z+=p[i].z;
	}
	c.x/=4, c.y/=4, c.z/=4;
	if(inside(c, p)) printf("Standing\n");
	else if(onside(c, p[0], p[1]) || onside(c,p[1],p[2]) || onside(c,p[2],p[0])) 
		printf("Unstable\n");
	else printf("Falling\n");
	return 0;
}
