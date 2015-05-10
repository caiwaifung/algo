#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }

struct Point {
	int x, y;
	double p; int i;
	Point() {}
	Point(int x, int y, double p=0.) :
		x(x), y(y), p(p) {}
	bool operator <(const Point &b) const {
		return (x<b.x) || (x==b.x && y<b.y);
	}
	Point operator -(const Point &b) const {
		return Point(x-b.x, y-b.y);
	}
	Point operator +(const Point &b) const {
		return Point(x+b.x, y+b.y);
	}
};
typedef vector<Point> VP;
int mult(Point p1, Point p2) {
	return p1.x*p2.y-p1.y*p2.x;
}
int mult(Point p0, Point p1, Point p2) {
	return mult(p1-p0, p2-p0);
}
int dot(Point p1, Point p2) {
	return p1.x*p2.x+p1.y*p2.y;
}
int dot(Point p0, Point p1, Point p2) {
	return dot(p1-p0, p2-p0);
}
double area(Point p0, Point p1, Point p2) {
	double p=mult(p0, p1, p2);
	return fabs(p)/2.;
}
int dis(Point p0, Point p1) {
	return (p1.x-p0.x)*(p1.x-p0.x)+(p1.y-p0.y)*(p1.y-p0.y);
}

class Constellation {
public:
	double cal(Point p, VP a) {
		double ans=0.;
		forn(i, a.size()) forint(j, i+1, a.size()-1) {
			double cp=1.;
			double ca=area(p, a[i],a[j]);
			cp*=a[i].p;
			cp*=a[j].p;
			forn(k, a.size()) if(k!=i && k!=j) {
				if(mult(a[i],a[j],a[k])==0) {
					if(dot(a[k],a[i],a[j])<0)
						cp*=1.-a[k].p;
					continue;
				}
				if((mult(a[i],a[j],a[k])<0)!=(mult(a[i],a[j],p)<0))
					cp*=1.-a[k].p;
			}
			ans+=ca*cp;
		}
		return ans;
	}
	double expectation(vector <int> x, vector <int> y, vector <int> prob) {
		VP p;
		forn(i, x.size()) {
			bool found=false;
			double cp=(double)prob[i]/1000.;
			forn(j, p.size())
				if(x[i]==p[j].x && y[i]==p[j].y) {
					p[j].p=1.-(1.-p[j].p)*(1.-cp);
					found=true;
				}
			if(!found)
				p.PB(Point(x[i],y[i],cp));
		}
		sort(p.begin(), p.end());
		double ans=0., tmp=1.;
		forn(i, p.size()) {
			VP b;
			forint(j, i+1, p.size()-1) b.PB(p[j]);
			ans+=tmp*p[i].p*cal(p[i], b);
			tmp*=1.-p[i].p;
		}
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500,500,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.0625; verify_case(0, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,400,800}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.6000000000000001; verify_case(1, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {-1,-1,-1,0,0,0,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,0,1,-1,0,1,-1,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500,500,500,500,500,500,500,500,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.9375; verify_case(2, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,1,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,2,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,500,200,500,1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.3; verify_case(3, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1,5,5,8,2,6,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,6,4,2,5,7,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100,400,200,1000,400,900,600}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 12.888936; verify_case(4, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,1000,1000,342,747,897,325,678,34,53,6,253}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 40000.0; verify_case(5, Arg3, expectation(Arg0, Arg1, Arg2)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	Constellation ___test;
	//*
	___test.run_test(-1);
	/*/
	___test.run_test(0);
	//*/
	return 0;
}
// END CUT HERE
