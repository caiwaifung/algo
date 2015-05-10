#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const int MOD=int(1e9)+7;
int f[5050][55][105];

class AlternativePiles
{
public:
	int count(string C, int M)
	{
		fillchar(f, 0);
		f[0][0][0]=1;
		forn(i, C.size()) forint(j, 0, M) forn(k, 2*M) {
			int val=f[i][j][k]; if(val==0) continue;
			bool cr=(C[i]=='R' || C[i]=='W');
			bool cg=(C[i]=='G' || C[i]=='W');
			bool cb=(C[i]=='B' || C[i]=='W');
			if(cr && j<M) (f[i+1][j+1][(k+1)%(2*M)]+=val) %=MOD;
			if(cg && j>0) (f[i+1][j-1][(k+1)%(2*M)]+=val) %=MOD;
			if(cb) (f[i+1][j][k]+=val) %=MOD;
		}
		return f[C.size()][0][0];
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "WRGWWRGW"; int Arg1 = 2; int Arg2 = 3; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "RRGG"; int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "BBBB"; int Arg1 = 5; int Arg2 = 1; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"; int Arg1 = 50; int Arg2 = 265470435; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "WRWRGWWGWWWRWBWRWGWWRWBWWRGWBWGRGWWGWGRWGRWBRWBW"; int Arg1 = 7; int Arg2 = 7400348; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	AlternativePiles ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
