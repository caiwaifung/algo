#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define all(a) a.begin(), a.end()
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
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }
template<class T> T sqr(T x) { return x*x; }

const double EPS=1e-10;

double sgn(double x) { return x<-EPS ? -1 : x>EPS; }

struct Point {
	double x, y;
	Point() { }
	Point(double x, double y) : x(x), y(y) { }
	Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
	Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
	Point operator *(double b) const { return Point(x*b, y*b); }
	Point operator /(double b) const { return Point(x/b, y/b); }
	void rotate90() { swap(x, y); x=-x; }
	double len() const { return sqrt(x*x+y*y); }
	void normalize() { *this=*this/len(); }
	friend double mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
	friend double dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
	friend double mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
	friend double dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
	friend double dist(Point p1, Point p2) { return (p1-p2).len(); }
};
typedef vector<Point> VP;

struct Line {
	double a, b, c;
	Line(double a, double b, double c) : a(a), b(b), c(c) { }
	Line(Point p1, Point p2) {
		a=p2.y-p1.y, b=p1.x-p2.x;
		c=-(p1.x*a+p1.y*b);
	}
};

double get_lambda(Point p, Point s, Point t) { //返回c: p=s+(t-s)*c
	return dot(s, t, p)/dot(s, t, t);
}

int cross_lc(Point p, double r, Line l, Point &p1, Point &p2) { //直线交圆
	double a=l.a, b=l.b, c=l.c; double aa=a*a, bb=b*b, s=aa+bb;
	double d=r*r*s-sqr(a*p.x+b*p.y+l.c);
	if(sgn(d)<0) return 0; if(sgn(d)==0) d=0; else d=sqrt(d);
	double ab=a*b, bd=b*d, ad=a*d;
	double xx=bb*p.x-ab*p.y-a*c;
	double yy=aa*p.y-ab*p.x-b*c;
	p2=Point((xx+bd)/s, (yy-ad)/s);
	p1=Point((xx-bd)/s, (yy+ad)/s);
	if(sgn(d)>0) return 2; else return 1;
}


// ------------------------ template ends here ------------------------ //

class BarbarianInvasion2 {
public:
	Point a[55], b[11];
	int n, m;
	double sum[1<<5];

	void go(Point s, Point t, double len) {
		vector<double> p;
		p.PB(0); p.PB(1);
		forint(i, 1, m) {
			Point p1, p2;
			if(cross_lc(b[i], len, Line(s,t), p1, p2)==0)
				continue;
			double x=get_lambda(p1, s, t);
			double y=get_lambda(p2, s, t);
			if(x>0 && x<1) p.PB(x);
			if(y>0 && y<1) p.PB(y);
		}
		sort(p.begin(), p.end());
		forn(i, p.size()-1) {
			double l=p[i], r=p[i+1];
			double mid=(l+r)/2;
			Point mp=s+(t-s)*mid;
			int cur=0;
			forint(j, 1, m)
				if(dist(mp, b[j])<=len)
					cur|=1<<(j-1);
			double len=dist(s, t)*(r-l);
			sum[cur]+=len;
		}
	}
	bool check(double len) {
		fillchar(sum, 0);
		forint(i, 1, n)
			go(a[i-1], a[i], len);
		double tot=0;
		forint(i, 1, n) tot+=dist(a[i-1], a[i]);

		forn(cur, 1<<m) {
			double need=0;
			forn(i, m) if(cur&(1<<i)) need+=tot/m;
			double has=0;
			forint(c, 1, (1<<m)-1)
				if((c&cur)>0)
					has+=sum[c];
			if(sgn(has-need)<0)
				return false;
		}
		return true;
	}
	double minimumTime(vector <int> boundaryX, vector <int> boundaryY, vector <int> cityX, vector <int> cityY) {
		n=boundaryX.size();
		forn(i, n) a[i+1]=Point(boundaryX[i], boundaryY[i]);
		a[0]=a[n];
		m=cityX.size();
		forn(i, m) b[i+1]=Point(cityX[i], cityY[i]);


		double le=0, ri=5555;
		forn(tt, 199) {
			double mid=(le+ri)/2;
			if(check(mid)) ri=mid;
			else le=mid;
		}
		return double(le);
	}

	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,2,2,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 1.414213562373088; verify_case(0, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0,3,3,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,3,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 2.8284271247461485; verify_case(1, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0,3,3,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,3,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 2.236067977499772; verify_case(2, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0,40,40,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,40,40}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,31,2,15}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,2,3,3,24}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 38.05748153551994; verify_case(3, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {0,124,-6,-120,-300}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,125,140,137,-100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10,10,10,10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {50,51,52,21}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); double Arg4 = 332.77770358002783; verify_case(4, Arg4, minimumTime(Arg0, Arg1, Arg2, Arg3)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BarbarianInvasion2 ___test;
	/*
	   ___test.run_test(0);
	/*/
	  ___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
