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

class ColorfulCoins
{
public:
	int pow(int x, int y) {
		int ans=1;
		for(; y>0; y>>=1, x=min(9999,x*x))
			if(y&1) ans=min(9999,ans*x);
		return ans;
	}
	int minQueries(vector<long long> values)
	{
		VI t;
		forn(i, values.size()-1) {
			LL x=values[i+1]/values[i];
			if(x<=66) t.PB(int(x));
		}
		sort(t.begin(), t.end());
		for(int ans=1; ; ++ans) {
			bool flag=true;
			forn(i, t.size()) {
				int need=i+1;
				int have=pow(t[i], ans)-1;
				if(have<need) flag=false;
			}
			if(flag) return ans;
		}
		return -1;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {1}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minQueries(Arg0)); }
	void test_case_1() { long Arr0[] = {1, 3}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minQueries(Arg0)); }
	void test_case_2() { long Arr0[] = {1, 2, 4}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minQueries(Arg0)); }
	void test_case_3() { long Arr0[] = {1, 2, 4, 8, 16}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minQueries(Arg0)); }
	void test_case_4() { long Arr0[] = {1, 2, 6, 30, 90, 270, 810, 2430, 7290, 29160, 87480, 262440, 787320, 3149280,
  9447840, 28343520, 56687040, 170061120, 510183360, 1530550080, 3061100160,
  9183300480, 27549901440, 82649704320, 247949112960, 1239745564800, 3719236694400,
  14876946777600, 44630840332800, 223154201664000, 669462604992000, 2008387814976000,
  6025163444928000, 12050326889856000, 24100653779712000, 72301961339136000,
  289207845356544000, 867623536069632000}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(4, Arg1, minQueries(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	ColorfulCoins ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
