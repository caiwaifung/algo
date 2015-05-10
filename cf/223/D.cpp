#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef long long LL;
typedef pair<double,int> PDI;
#define MP(a,b) make_pair(a,b)

const int MAXN=100010;
const int MAXV=30000;
const int MAXNODES=MAXN*30;

int absv(int x) {return x<0?-x:x;}
struct Point {
	double x, y;
};
double mult(const Point &p0, const Point &p1, const Point &p2) {
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
Point get(const Point &p1, const Point &p2, double x) {
	Point b;
	if(p1.x==p2.x) {
		b.x=p1.x; b.y=max(p1.x,p2.x);
	} else {
		b.x=x;
		b.y=p1.y+(b.x-p1.x)*(p2.y-p1.y)/(p2.x-p1.x);
	}
	return b;
}
struct Segment {
	int i, j;
	Point pi, pj;
	//double my, iy, dx, dy;
};

Point a[MAXN];
int des[MAXN], fly[MAXN];
Segment seg[MAXN];
int n;

bool cmp1(const Segment &a, const Segment &b) {
	double u1=a.pi.x, u2=a.pj.x; if(u1>u2) swap(u1,u2);
	double v1=b.pi.x, v2=b.pj.x; if(v1>v2) swap(v1,v2);
	double x1=max(u1,v1), x2=min(u2,v2);
	double x=(x1+x2)/2;
	Point p1=get(a.pi, a.pj, x);
	Point p2=get(b.pi, b.pj, x);
	if(fabs(p1.y-p2.y)<1E-9) return p1.y<p2.y;
		else return (&a)<(&b);
		/*
	//if(max(a.pi.x,a.pj.x)<min(b.pi.x,b.pj.x)) return false;
	//if(max(b.pi.x,b.pj.x)<min(a.pi.x,a.pj.x)) return false;
	if(max(a.pi.y,a.pj.y)<=min(b.pi.y,b.pj.y)) {
		if(min(a.pi.y,a.pj.y)<min(b.pi.y,b.pj.y) || max(a.pi.y,a.pj.y)<max(b.pi.y,b.pj.y))
			return true;
		else return false;
	}
	if(max(b.pi.y,b.pj.y)<=min(a.pi.y,a.pj.y)) return false;
	double za=(a.pi.x<=a.pj.x?1:-1);
	double tmp2=mult(a.pi,a.pj, b.pi)+mult(a.pi,a.pj, b.pj);
	double zb=(b.pi.x<=b.pj.x?1:-1);
	double tmp3=mult(b.pi,b.pj, a.pi)+mult(b.pi,b.pj, a.pj);
	return (za*tmp2-zb*tmp3)>0;
	//if(a.my!=b.my) return a.my<b.my;
	//return a.dy*b.dx>b.dy*a.dx;
	*/
}

struct Node {
	int c;
	int l, r;
} tr[MAXNODES];
int nodes, root;

int color(int x, int s, int t, int st, int en, int c) {
	if(x==0) {
		x=++nodes;
		tr[x].l=tr[x].r=0;
		tr[x].c=-1;
	}
	if(st<=s && t<=en) {
		tr[x].c=c; return x;
	}
	int mid=(s+t)/2;
	if(tr[x].c>=0) {
		tr[x].l=color(tr[x].l, s, mid, s, t, tr[x].c);
		tr[x].r=color(tr[x].r, mid+1, t, s, t, tr[x].c);
		tr[x].c=-1;
	}
	if(st<=mid) tr[x].l=color(tr[x].l, s, mid, st, en, c);
	if(mid<en) tr[x].r=color(tr[x].r, mid+1, t, st, en, c);
	return x;
}
int get(int x, int s, int t, int ind) {
	if(x==0) return 0;
	if(tr[x].c>=0) return tr[x].c;
	int mid=(s+t)/2;
	if(ind<=mid) return get(tr[x].l, s, mid, ind);
	else return get(tr[x].r, mid+1, t, ind);
}

double f[MAXN];
vector<PDI> edges[MAXN];
set<PDI> que;
int src, dst;
void update(int i, double val) {
	if(val<f[i]) {
		que.erase(que.find(MP(f[i],i)));
		f[i]=val;
		que.insert(MP(f[i],i));
	}
}
double dis(Point a, Point b) {
#define sqr(x) ((x)*(x))
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
//PDI points[MAXN];

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; ++i) {
		scanf("%lf%lf", &a[i].x, &a[i].y);
		//points[i]=MP(a[i].y,i);
		a[i].x+=MAXV/2;
	}
	//sort(points+1,points+n+1);
	scanf("%d%d", &src,&dst);

	a[n+1]=a[1], a[0]=a[n];
	for(int i=1; i<=n; ++i) {
		seg[i].i=i, seg[i].j=i%n+1;
		seg[i].pi=a[i], seg[i].pj=a[i+1];
		//seg[i].my=max(a[i].y, a[i+1].y);
		//seg[i].iy=min(a[i].y, a[i+1].y);
		//seg[i].my=seg[i].iy=a[i].y+a[i+1].y;
		//seg[i].dx=absv(a[i].x-a[i+1].x);
		//seg[i].dy=absv(a[i].y-a[i+1].y);
	}
	sort(seg+1, seg+n+1, cmp1);
	memset(des, 0xff, sizeof(des));
	nodes=root=0; 
	//int cur=1;
	for(int i=1; i<=n; ++i) {
		int p1=seg[i].i;
		if(des[p1]<0) des[p1]=get(root, 1, MAXV, a[p1].x);
		int p2=seg[i].j;
		if(des[p2]<0) des[p2]=get(root, 1, MAXV, a[p2].x);
		//if(seg[i].i<1 || seg[i].i>n) return false;
		if(a[p1].x<=a[p2].x)
			root=color(root,1,MAXV, a[p1].x,a[p2].x,seg[i].i);
		else
			root=color(root,1,MAXV, a[p2].x,a[p1].x,0);
	}
	//for(int i=1; i<=n; ++i) if(seg[i].i<1 || seg[i].j<1) return 0;
	//for(int i=1; i<=n; ++i) if(seg[i].i>n || seg[i].j>n) return 0;
	//sort(seg+1, seg+n+1, cmp2);
	memset(fly, 0xff, sizeof(fly));
	nodes=root=0;
	//for(int i=1; i<=n; ++i) if(seg[i].i<1 || seg[i].j<1) return 0;
	//for(int i=1; i<=n; ++i) if(seg[i].i>n || seg[i].j>n) return 0;
	//for(int i=1; i<=n; ++i) if(des[i]>n) return 0;
	//for(int i=1; i<=n; ++i) {
	for(int i=n; i>=1; --i) {
		int p1=seg[i].i;
		if(fly[p1]<0) {
			fly[p1]=get(root, 1, MAXV, a[p1].x);
			//printf("get %d: %d=%d\n", p1,(int)a[p1].x, fly[p1]);
		}
		int p2=seg[i].j;
		if(fly[p2]<0) {
			fly[p2]=get(root, 1, MAXV, a[p2].x);
			//printf("get %d: %d=%d\n", p2,(int)a[p2].x, fly[p2]);
		}
		//if(p1<1 || p1>n || p2<1 || p2>n) return 0;
		swap(p1, p2);
		//printf("p1=%d p2=%d\n", p1,p2);
		if(a[p1].x<=a[p2].x) {
			//printf("color [%d,%d] %d\n",(int)a[p1].x,(int)a[p2].x,seg[i].i);
			root=color(root,1,MAXV, a[p1].x,a[p2].x,seg[i].i); }
		else
			root=color(root,1,MAXV, a[p2].x,a[p1].x,0);
	}
	for(int i=1; i<=n; ++i) edges[i].clear();
	for(int i=1; i<=n; ++i) {
		seg[i].i=i; seg[i].j=(i%n)+1;
	}
	for(int i=1; i<=n; ++i) {
		if(des[i]>0) {
			//if(des[i]<1 || des[i]>n) return 0;
			int p1=seg[des[i]].i;
			int p2=seg[des[i]].j;
			Point b=get(a[p1], a[p2], a[i].x);
			edges[i].push_back(MP(dis(a[i],b)+dis(b,a[p1]), p1));
			edges[i].push_back(MP(dis(a[i],b)+dis(b,a[p2]), p2));
		}
		//printf("des[%d]=%d\n", i,des[i]);
		//printf("fly[%d]=%d\n", i,fly[i]);
		if(fly[i]>0) {
			int p1=seg[fly[i]].i;
			int p2=seg[fly[i]].j;
			Point b=get(a[p1], a[p2], a[i].x);
			edges[p1].push_back(MP(dis(a[i],b)+dis(b,a[p1]), i));
			edges[p2].push_back(MP(dis(a[i],b)+dis(b,a[p2]), i));
		}
	}
	/*
	   for(int i=1; i<=n; ++i)
	   for(int j=0; j<edges[i].size(); ++j)
	   printf("e[%d,%d]=%.4lf\n",i,edges[i][j].second,edges[i][j].first);
	 */

	for(int i=1; i<=n; ++i) f[i]=1E50;
	f[src]=0;
	que.clear();
	for(int i=1; i<=n; ++i) que.insert(MP(f[i],i));
	while(que.size()>0) {
		int i=que.begin()->second;
		que.erase(que.begin());
		update(i==1?n:(i-1), f[i]+dis(a[i], a[i-1]));
		update(i==n?1:(i+1), f[i]+dis(a[i], a[i+1]));
		for(int j=0; j<edges[i].size(); ++j)
			update(edges[i][j].second, f[i]+edges[i][j].first);
	}
	printf("%.9lf\n", f[dst]);

	return 0;
}
