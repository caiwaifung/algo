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


// ------------------------ template ends here ------------------------ //

class AliceGame {
public:
	long long findMinimumValue(long long x, long long y) {
		LL n=0, sum=0;
		while(sum<x+y) {
			++n; sum+=2*n-1;
		}
		if(sum!=x+y) return -1;
		for(LL t=0; t<=n; ++t) {
			// 1+3+...+(2*t-1) = 2*t*t/2 = t*t
			LL lv=t*t;
			// (2*n-1)+...+(2*(n-t+1)-1) = (4n-2t)*t/2 = (2n-t)*t
			LL rv=(2*n-t)*t;
			if(lv%2==x%2 && lv<=x && x<=rv) return t;
		}
		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 8LL; long long Arg1 = 17LL; long long Arg2 = 2LL; verify_case(0, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 17LL; long long Arg1 = 8LL; long long Arg2 = 3LL; verify_case(1, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 0LL; long long Arg1 = 0LL; long long Arg2 = 0LL; verify_case(2, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 9LL; long long Arg1 = 9LL; long long Arg2 = -1LL; verify_case(3, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 500000LL; long long Arg1 = 500000LL; long long Arg2 = 294LL; verify_case(4, Arg2, findMinimumValue(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	AliceGame ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
