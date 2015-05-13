#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
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

class ApplesAndOrangesEasy {
public:
    bool ok(int a[], int n, int k) {
        int s=0;
        forint(i, 1, k) s+=a[i];
        if(s>k/2) return false;
        forint(j, k+1, n) {
            s+=a[j];
            s-=a[j-k];
            if(s>k/2) return false;
        }
        return true;
    }
    int maximumApples(int N, int K, vector <int> info) {
        static int a[2020];
        fillchar(a, 0);
        for(int p: info) a[p]=1;

        forint(i, 1, N) if(a[i]==0) {
            a[i]=1;
            if(!ok(a, N, K)) a[i]=0;
        }
        int s=0;
        forint(i, 1, N) s+=a[i];

        return int(s);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(0, Arg3, maximumApples(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 3; int Arr2[] = {3, 8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(1, Arg3, maximumApples(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 9; int Arg1 = 4; int Arr2[] = {1, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; verify_case(2, Arg3, maximumApples(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 9; int Arg1 = 4; int Arr2[] = {2, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 4; verify_case(3, Arg3, maximumApples(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 23; int Arg1 = 7; int Arr2[] = {3, 2, 9, 1, 15, 23, 20, 19}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; verify_case(4, Arg3, maximumApples(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    ApplesAndOrangesEasy ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
