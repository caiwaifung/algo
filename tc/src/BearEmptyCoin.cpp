#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

class BearEmptyCoin {
public:
    long long winProbability(int K, int S) {
        return (long long)();
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 17; long long Arg2 = 2LL; verify_case(0, Arg2, winProbability(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = -50; long long Arg2 = 4LL; verify_case(1, Arg2, winProbability(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = -49; long long Arg2 = 2LL; verify_case(2, Arg2, winProbability(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 42; long long Arg2 = 8LL; verify_case(3, Arg2, winProbability(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 4; int Arg1 = -123456789; long long Arg2 = 6LL; verify_case(4, Arg2, winProbability(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 18; int Arg1 = 123456; long long Arg2 = 49870LL; verify_case(5, Arg2, winProbability(Arg0, Arg1)); }
	void test_case_6() { int Arg0 = 60; int Arg1 = 0; long long Arg2 = 1152921504606846976LL; verify_case(6, Arg2, winProbability(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    BearEmptyCoin ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
