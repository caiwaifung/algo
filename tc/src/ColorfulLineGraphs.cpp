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

class ColorfulLineGraphs {
    LL pow(LL a, LL b, LL M) {
        LL ans=1;
        for(; b>0; b>>=1, a=(a*a)%M)
            if(b&1) ans=ans*a%M;
        return ans;
    }
public:
    int countWays(long long N, long long K, int _M) {
        LL M=_M;
        //LL ans=1;
        //forint(i, 1, N) ans=(ans*((K-1)*i+1))%M;
        LL t=N/M;
        LL s1=1; 
        forint(i, 1, M) {
            LL tmp=((K-1)%M*i+1)%M;
            s1=s1*tmp%M;
        }
        LL s2=pow(s1, t, M);
        LL ans=s2;
        for(LL i=t*M+1; i<=N; ++i) {
            LL tmp=((K-1)%M*i+1)%M;
            ans=ans*tmp%M;
        }
        return (int)ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 3LL; long long Arg1 = 2LL; int Arg2 = 100000; int Arg3 = 24; verify_case(0, Arg3, countWays(Arg0, Arg1, Arg2)); }
	void test_case_1() { long long Arg0 = 15LL; long long Arg1 = 3LL; int Arg2 = 1000000; int Arg3 = 510625; verify_case(1, Arg3, countWays(Arg0, Arg1, Arg2)); }
	void test_case_2() { long long Arg0 = 100000LL; long long Arg1 = 100000LL; int Arg2 = 999999; int Arg3 = 185185; verify_case(2, Arg3, countWays(Arg0, Arg1, Arg2)); }
	void test_case_3() { long long Arg0 = 1000000000000LL; long long Arg1 = 6LL; int Arg2 = 1000000; int Arg3 = 109376; verify_case(3, Arg3, countWays(Arg0, Arg1, Arg2)); }
	void test_case_4() { long long Arg0 = 5000LL; long long Arg1 = 1000000000000LL; int Arg2 = 314159; int Arg3 = 202996; verify_case(4, Arg3, countWays(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    ColorfulLineGraphs ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
