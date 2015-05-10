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
typedef pair<double,double> PDD;
typedef pair<int,int> PII;
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

// ------------------------ template ends here ------------------------ //

class DevuAndBeautifulSubstrings {
public:
    long long countBeautifulSubstrings(int n, int cnt) {
        const int N=52;
        static LL f[N][N][N*N];
        fillchar(f, 0);
        f[0][0][0]=1;
        forint(i, 0, n-1) forint(c, 0, i) forn(t, 2500) {
            f[i+1][1][t+1]+=f[i][c][t];
            f[i+1][c+1][t+c+1]+=f[i][c][t];
        }
        LL ans=0;
        forint(i, 0, n) ans+=f[n][i][cnt];
        return LL(ans);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; long long Arg2 = 2LL; verify_case(0, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; long long Arg2 = 0LL; verify_case(1, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 4; long long Arg2 = 4LL; verify_case(2, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 15; int Arg1 = 35; long long Arg2 = 642LL; verify_case(3, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 40; int Arg1 = 820; long long Arg2 = 2LL; verify_case(4, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 50; int Arg1 = 94; long long Arg2 = 32357325751902LL; verify_case(5, Arg2, countBeautifulSubstrings(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	DevuAndBeautifulSubstrings ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
