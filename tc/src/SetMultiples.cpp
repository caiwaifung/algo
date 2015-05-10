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

class SetMultiples {
public:
	LL go(LL x, LL y) {
		LL t=y/2;
		return max(0LL, t-x+1);
	}
	LL go2(LL x1, LL y1, LL x2, LL y2) {
		LL ans=0;
		forint(i, 2, 200000) {
			LL x=(x2+i-1)/i;
			LL y=y2/i;
			y1=min(y1, y); if(x1>y1) break;
			if(x>y) continue;
			// use [x,y] to cut [x1,y1]
			if(x>y1) continue;
			if(y<x1) return ans;
			LL cx=max(x, x1), cy=min(y, y1);
			ans+=cy-cx+1;
			y1=cx-1;
			if(x1>y1) break;
		}
		for(LL i=x1; i<=y1; ++i) {
			LL u=(x2+i-1)/i;
			LL v=y2/i;
			if(u<=v) ++ans;
		}
		return ans;
	}
	long long smallestSubset(long long A, long long B, long long C, long long D) {
		LL ans1=go(A, B);
		LL ans2=go(C, D);
		LL ans3=go2(A+ans1, B, C, D);
		LL ans=(B-A+1)+(D-C+1)-(ans1+ans2+ans3);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 1LL; long long Arg2 = 2LL; long long Arg3 = 2LL; long long Arg4 = 1LL; verify_case(0, Arg4, smallestSubset(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 2LL; long long Arg2 = 3LL; long long Arg3 = 4LL; long long Arg4 = 2LL; verify_case(1, Arg4, smallestSubset(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { long long Arg0 = 2LL; long long Arg1 = 3LL; long long Arg2 = 5LL; long long Arg3 = 7LL; long long Arg4 = 3LL; verify_case(2, Arg4, smallestSubset(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 10LL; long long Arg2 = 100LL; long long Arg3 = 1000LL; long long Arg4 = 500LL; verify_case(3, Arg4, smallestSubset(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { long long Arg0 = 1000000000LL; long long Arg1 = 2000000000LL; long long Arg2 = 9000000000LL; long long Arg3 = 10000000000LL; long long Arg4 = 1254365078LL; verify_case(4, Arg4, smallestSubset(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SetMultiples ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
