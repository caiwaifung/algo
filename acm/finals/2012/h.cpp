// 14:33 - 15:11 - finish
// 16:01 - pass sample
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN=211;
const double INFI=1E50;
const double EPS=1e-8;

#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)

int sgn(double x) {
	return x<-EPS ? -1 : x>EPS;
}

struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point operator -(const Point &p) const {
		Point t=*this;
		t.x-=p.x, t.y-=p.y;
		return t;
	}
	Point operator +(const Point &p) const {
		Point t=*this;
		t.x+=p.x, t.y+=p.y;
		return t;
	}
	Point operator *(double b) const {
		return Point(x*b, y*b);
	}
	Point operator /(double b) const {
		return Point(x/b, y/b);
	}
	void read() {
		scanf("%lf%lf", &x,&y);
	}
	void normalize() {
		double len=sqrt(x*x+y*y);
		x/=len, y/=len;
	}
};

Point a[MAXN];
Point robot;
int n;

Point tp[MAXN];

double dist(Point p1, Point p2) {
#define sqr(x) ((x)*(x))
	return sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
}

double mult(Point p0, Point p1, Point p2) {
	return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
}

Point project(Point p, Point p1, Point p2) {
	double d=dist(p1, p2);
	double s=mult(p1, p2, p);
	Point dir=Point(p2.y-p1.y, p1.x-p2.x);
	dir.normalize();
	Point z=p + dir*s/d;
	//printf("project: p=(%.4lf,%.4lf) p1=(%.4lf,%.4lf) p2=(%.4lf,%.4lf)\n", p.x,p.y,p1.x,p1.y,p2.x,p2.y);
	//printf("d=%.4lf s=%.4lf z=(%.4lf,%.4lf)\n",d,s,z.x,z.y);
	return z;
}

Point mirror(Point p, Point p1, Point p2) {
	Point p3=project(p, p1, p2);
	//printf("   p3=(%.4lf,%.4lf)\n",p3.x,p3.y);
	return p3+p3-p;
}

bool cross(Point a1, Point a2, Point b1, Point b2) {
	if(sgn(mult(a1,a2,b1)) * sgn(mult(a1,a2,b2)) >0) return false;
	if(sgn(mult(b1,b2,a1)) * sgn(mult(b1,b2,a2)) >0) return false;
	return true;
}

double cal(Point s, int i, int j, Point t) {
	tp[i]=s;
//printf("\ni=%d j=%d s=(%.4lf,%.4lf) t=(%.4lf,%.4lf):\n",i,j,s.x,s.y,t.x,t.y);
	forint(k, i, j-1) {
		Point p1=a[k+1], p2=a[k];
		if(sgn(mult(p1, p2, tp[k]))>0)
			return INFI;
		tp[k+1]=mirror(tp[k], p1, p2);
		//printf("tp[k]=(%.4lf,%.4lf)\n",tp[k].x,tp[k].y);
		//printf("p1=(%.4lf,%.4lf) p2=(%.4lf,%.4lf)\n",p1.x,p1.y,p2.x,p2.y);
		//printf("tp[k']=(%.4lf,%.4lf)\n",tp[nxt(k)].x,tp[nxt(k)].y);
	}
//printf("\n");
//forint(k,i,j) printf("tp[%d]=(%.4lf,%.4lf)\n",k,tp[k].x,tp[k].y);

	forintdown(k, j, i+1) {
		Point p1=a[k], p2=a[k-1];
		Point t1=tp[k], t2=t;
		if(!cross(p1, p2, t1, t2))
			return INFI;
		t=mirror(t, p1, p2);
	}
//printf("i=%d j=%d s=(%.4lf,%.4lf) t=(%.4lf,%.4lf):\n",i,j,s.x,s.y,t.x,t.y);
//printf("\n");
	return dist(s, t);
}

//double fl[MAXN][MAXN], fr[MAXN][MAXN];
double g[MAXN][MAXN];

void solve(int cs) {

	double ans=INFI;
	forintdown(i, n*2, 1)
		forint(j, i+1, n*2)
			forint(k, i+1, j-1)
				g[i][j]=min(g[i][j], g[i][k]+g[k][j]);
	forint(i, 1, n) {
		double tmp=cal(robot, i, i+n, robot);
		ans=min(ans, tmp);
		//printf("\n--------------------\n");
		//printf("i=%d tmp=%.9lf\n",i,tmp);

		forint(j, i, i+n) forint(k, j, i+n) {
			double tmp=g[j][k];
			if(j<=i+1) tmp+=dist(robot, a[j]);
			else if(j>=i+2) tmp+=cal(robot, i, j-1, a[j]);
			if(k>=i+n-1) tmp+=dist(robot, a[k]);
			else if(k<=i+n-2) tmp+=cal(a[k], k+1, i+n, robot);
			ans=min(ans, tmp);
			//printf("i=%d j=%d k=%d tmp=%.9lf\n",i,j,k,tmp);
		}
	}
	printf("Case %d: %.2lf\n", cs, ans);
}

int main() {
	for(int cs=1; ; ++cs) {
		if(scanf("%d", &n)<1) break;
		robot.read();
		forint(i, 1, n) a[i].read(), a[i+n]=a[i];
	//cal(robot,1,3,a[4]); return 0;

		/*
		forint(i, 1, n) {
			fl[i][i]=dist(robot, a[i]);
			fl[i][nxt(i)]=dist(robot, a[nxt(i)]);
			for(int j=nxt(nxt(i)); j!=i; j=nxt(j))
				fl[i][j]=cal(robot, i, lst(j), a[j]);
		}
		forint(i, 1, n) {
			fr[i][i]=dist(robot, a[i]);
			fr[i][lst(i)]=dist(robot, a[lst(i)]);
			for(int j=lst(lst(i)); j!=i; j=lst(j))
				fr[i][j]=cal(a[j], nxt(j), i, robot);
		}
		*/
		forint(i, 1, n*2) {
			g[i][i]=0;
			g[i][i+1]=dist(a[i], a[i+1]);
			g[i][i+2]=dist(a[i], a[i+2]);
			forint(j, i+3, n*2)
				g[i][j]=cal(a[i], i+1, j-1, a[j]);
		}
		solve(cs);
	}
	return 0;
}
