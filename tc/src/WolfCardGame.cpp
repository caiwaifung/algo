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

#define _ (int)
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

class WolfCardGame {
public:
    vector <int> createAnswer(int N, int K) {
        int x0=0;
        for(int x: {2,3,5,7}) if(N%x!=0) { x0=x; break; }
        VI r; 
        if(x0==7) {
            if(N==90) r.pb(2);
                else r.pb(1);
            rep(i, 1, K-1) r.pb(i*x0);
        } else {
            rep(i, 1, K) r.pb(i*x0);
        }
        return r;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 20; int Arg1 = 4; int Arr2[] = {1, 2, 3, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, createAnswer(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 40; int Arg1 = 1; int Arr2[] = {39 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, createAnswer(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 97; int Arg1 = 6; int Arr2[] = {7, 68, 9, 10, 62, 58 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, createAnswer(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 12; int Arr2[] = {33, 69, 42, 45, 96, 15, 57, 12, 93, 9, 54, 99 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, createAnswer(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    WolfCardGame ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
