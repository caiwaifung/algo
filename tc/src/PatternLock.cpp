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

const int MAXN=3550;

class PatternLock {
	LL mod(LL a, LL b) {
		a=(a%b+b)%b;
		return a;
	}
public:
	int solve(int N, int MOD) {
		static LL f[MAXN][MAXN];
		static LL s[MAXN][MAXN];
		fillchar(f, 0);
		fillchar(s, 0);
		f[0][0]=s[0][0]=1;
		forint(i, 1, N) f[0][i]=0, s[0][i]=1;
		forint(i, 1, N) f[i][0]=s[i][0]=mod(f[i-1][0]*2, MOD);
		forint(t, 2, N*2) {
			forint(i, 1, N) {
				int j=t-i; if(j<1 || j>N) continue;
				f[i][j]=mod(s[j][i-1], MOD);
				s[i][j]=mod(s[i][j-1]*2+f[i][j]*(j+1), MOD);
			}
		}
		LL ans=mod(f[N][N], MOD);
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 12345667; int Arg2 = 2; verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 324124124; int Arg2 = 24; verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 5325352; int Arg2 = 504; verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 500; int Arg1 = 1000000007; int Arg2 = 286169049; verify_case(3, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PatternLock ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
