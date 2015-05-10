#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
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
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VPII;

class SimilarSequencesAnother {
public:
	int getCount(int N, int bound) {
		
		return int() ;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 10000; verify_case(0, Arg2, getCount(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 687; verify_case(1, Arg2, getCount(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 8; int Arg1 = 1; int Arg2 = 1; verify_case(2, Arg2, getCount(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 123456789; int Arg2 = 439681851; verify_case(3, Arg2, getCount(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 1000000000; int Arg2 = 81; verify_case(4, Arg2, getCount(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	SimilarSequencesAnother ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
