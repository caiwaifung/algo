#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
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
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

// ------------------------ template ends here ------------------------ //

struct Point {
    double x, y, ang, p;
    int i;
    Point(double x, double y, int p, int i) : x(x), y(y), p(p/100.), i(i) {
        ang=atan2(y, x); 
    }
    bool operator <(const Point &p) const { return ang<p.ang; }
};

class TrianglePainting {
public:
    double expectedArea(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2, vector <int> prob) {
        vector<Point> a;
        forn(i, x1.size()) {
            if(x1[i]*y2[i]-x2[i]*y1[i]<0) {
                swap(x1[i], x2[i]);
                swap(y1[i], y2[i]);
            }
            a.PB(Point(x1[i], y1[i], prob[i], i));
            a.PB(Point(x2[i]-x1[i], y2[i]-y1[i], prob[i], i));
            a.PB(Point(-x2[i], -y2[i], prob[i], i));
        }
        sort(all(a));
        vector<VI> pos(x1.size());
        forn(i, a.size()) pos[a[i].i].PB(i);

        vector<double> sx(a.size()+1, 0), sy(a.size()+1, 0);
        forn(i, a.size()) {
            sx[i+1]=sx[i]+a[i].x*a[i].p;
            sy[i+1]=sy[i]+a[i].y*a[i].p;
        }
        double ans=0;
        forn(i, x1.size()) {
            double tmp=0, dx=0, dy=0;
            for(int k: pos[i]) {
                double x=sx[k]+dx;
                double y=sy[k]+dy;
                tmp+=(x*a[k].y-y*a[k].x);
                dx+=a[k].x-a[k].x*a[k].p;
                dy+=a[k].y-a[k].y*a[k].p;
            }
            ans+=tmp*double(prob[i]/100.);
            //printf("%.2lf %.2lf\n",p.x,p.y);
        }
        return double(ans/2);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,-2,-4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,2,-2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-1,-1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {100,100,100}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 52.5; verify_case(0, Arg5, expectedArea(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arr0[] = {1,-2,-4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,2,-2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-1,-1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {50,50,50}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 15.0; verify_case(1, Arg5, expectedArea(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 0.01; verify_case(2, Arg5, expectedArea(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,1,-1,1,-1,1,-1,1,-1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,1,1,1,1,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,-1,1,-1,1,-1,1,-1,1,-1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {10,20,30,40,50,60,70,80,90,100}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 31.899999999999995; verify_case(3, Arg5, expectedArea(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arr0[] = {-6,-2,-10,9,8,-1,10,5,7,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-5,2,-5,6,6,-10,8,7,-4,-5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5,-1,-1,-8,6,7,10,-6,6,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,-5,-7,4,10,0,10,-3,-3,-4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {71,100,43,59,51,41,11,53,3,27}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 940.1964999999999; verify_case(4, Arg5, expectedArea(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arr0[] = {34,-71,19,78,69,-73,27,64,-100,70,-87,50,8,-97,46,-46,-30,-40,-30,-23,77,81,48,93,-40,70,
37,-66,53,-87,-85,38,-90,63,-16,24,-2,-60,-88,67,-56,-8,-80,-19,-84,35,95,-24,-26,-15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {58,-24,-80,33,-98,61,99,79,-34,29,-1,-70,70,90,43,25,-50,-54,73,18,36,8,41,3,26,-6,-80,
-22,65,33,-100,-1,80,-19,-6,-8,-4,-86,-43,-34,0,-93,-61,92,74,-77,32,-78,-56,-21}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-78,-100,-1,27,67,-31,-82,-24,44,-26,12,36,-36,-71,-84,3,59,28,-26,-79,-47,56,-75,-44,
-85,-72,56,53,-27,53,-19,-65,14,62,96,-44,12,-20,-57,83,59,71,85,-62,21,24,-38,20,52,-64}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {90,-41,79,18,7,-85,-88,-16,12,38,-7,12,-27,-43,-30,-93,48,-19,58,54,70,73,81,89,-35,-75,
63,-73,66,-90,-25,44,-53,59,-14,83,18,-35,-81,49,-11,-63,-87,-92,-83,-43,60,-42,5,-96}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {9,61,1,16,78,4,12,1,17,4,30,28,13,6,4,14,11,6,55,9,66,5,14,8,
70,3,2,6,3,15,8,1,2,12,1,20,37,1,3,66,3,11,2,1,21,2,1,1,27,11}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); double Arg5 = 306025.109; verify_case(5, Arg5, expectedArea(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    TrianglePainting ___test;

    VI x1, y1, x2, y2, p;
    x1.PB(0), y1.PB(1), x2.PB(1), y2.PB(0), p.PB(50);
    x1.PB(0), y1.PB(-1), x2.PB(-1), y2.PB(0), p.PB(50);
    double ans=___test.expectedArea(x1,y1,x2,y2,p);
    cout<<ans<<endl;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
