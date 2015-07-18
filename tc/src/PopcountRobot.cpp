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

class PopcountRobot {
public:
    int countBlack(long long T, int Q, int M, int x, int y) {
        {
        int x=0, y=0;
        repn(t, 50) {
            int cnt=0; for(int tmp=t; tmp>0; tmp/=2) cnt+=tmp%2;
            if(cnt%4==0) ++x;
            if(cnt%4==1) ++y;
            if(cnt%4==2) --x;
            if(cnt%4==3) --y;
            printf("%2d: %d, %d  -> %d\n",t,x,y,abs(x)+abs(y));
        }
        }
        exit(1);
        //return (int)();
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 5LL; int Arg1 = 10; int Arg2 = 2; int Arg3 = -1; int Arg4 = -2; int Arg5 = 2; verify_case(0, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { long long Arg0 = 30LL; int Arg1 = 500000; int Arg2 = 5; int Arg3 = 3; int Arg4 = 4; int Arg5 = 0; verify_case(1, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { long long Arg0 = 2015LL; int Arg1 = 500000; int Arg2 = 50; int Arg3 = 12; int Arg4 = 34; int Arg5 = 40000; verify_case(2, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { long long Arg0 = 1000000000000000000LL; int Arg1 = 500000; int Arg2 = 1000000000; int Arg3 = 94296562; int Arg4 = -42562967; int Arg5 = 32306; verify_case(3, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { long long Arg0 = 720875421873LL; int Arg1 = 500000; int Arg2 = 312; int Arg3 = -288; int Arg4 = 36; int Arg5 = 68000; verify_case(4, Arg5, countBlack(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PopcountRobot ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
