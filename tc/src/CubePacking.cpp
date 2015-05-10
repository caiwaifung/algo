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

class CubePacking {
public:
	int getMinimumVolume(int Ns, int Nb, int L) {
		LL ans=1LL<<50;
		forint(i, L, 2000) forint(j, i, 2000000/i) {
			LL ti=i/L, tj=j/L, tk=(Nb-1)/(ti*tj)+1;
			LL ci=i, cj=j, ck=(Ns+Nb*L*L*L-1)/(ci*cj)+1;
			LL k=max(tk*L, ck);
			setmin(ans, k*i*j);
		}
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 20; verify_case(0, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 19; int Arg1 = 1; int Arg2 = 2; int Arg3 = 27; verify_case(1, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 51; int Arg1 = 7; int Arg2 = 5; int Arg3 = 950; verify_case(2, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 12345; int Arg1 = 987; int Arg2 = 10; int Arg3 = 999400; verify_case(3, Arg3, getMinimumVolume(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CubePacking ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
