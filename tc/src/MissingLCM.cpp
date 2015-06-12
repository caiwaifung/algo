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
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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

int a[3000010];
class MissingLCM {
    void put(int x) {
        for(int i=2; i*i<=x; ++i)
            if(x%i==0) {
                int t=0; while(x%i==0) x/=i, ++t;
                setmax(a[i], t);
            }
        if(x>1) setmax(a[x], 1);
    }
public:
    int getMin(int N) {
        fillchar(a, 0);
        forint(i, 1, N) put(i);
        int M=N+1;
        forint(i, 1, N) {
            int t=1;
            forn(j, a[i]) t*=i;
            int t2=N/t*t+t;
            setmax(M, t2);
        }
        return (int)(M);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 4; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 6; verify_case(2, Arg1, getMin(Arg0)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 8; verify_case(3, Arg1, getMin(Arg0)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 10; verify_case(4, Arg1, getMin(Arg0)); }
	void test_case_5() { int Arg0 = 42; int Arg1 = 82; verify_case(5, Arg1, getMin(Arg0)); }
	void test_case_6() { int Arg0 = 999999; int Arg1 = 1999966; verify_case(6, Arg1, getMin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    MissingLCM ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
