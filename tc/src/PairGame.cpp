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

class PairGame {
public:
	int maxSum(int a, int b, int c, int d) {
		while(a!=c || b!=d) {
			if(a+b>c+d) {
				if(a==0 || b==0) return -1;
				if(a>b) a-=b; else b-=a;
			} else {
				if(c==0 || d==0) return -1;
				if(c>d) c-=d; else d-=c;
			}
		}
		return a+b;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; int Arg2 = 2; int Arg3 = 1; int Arg4 = 2; verify_case(0, Arg4, maxSum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 15; int Arg1 = 4; int Arg2 = 10; int Arg3 = 7; int Arg4 = 7; verify_case(1, Arg4, maxSum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 10; int Arg3 = 10; int Arg4 = -1; verify_case(2, Arg4, maxSum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 1001; int Arg2 = 2000; int Arg3 = 2001; int Arg4 = 1001; verify_case(3, Arg4, maxSum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 10944; int Arg1 = 17928; int Arg2 = 7704; int Arg3 = 21888; int Arg4 = 144; verify_case(4, Arg4, maxSum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; verify_case(5, Arg4, maxSum(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	PairGame ___test;
	/*
	___test.run_test(0); return 0;
	/*/
	___test.run_test(-1); return 0;
	//*/
}
// END CUT HERE
