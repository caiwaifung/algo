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

class LongestPalindrome {
public:
	int longestLength(string s) {
		int n=s.size(), ans=0;
		forn(i, n) forn(j, n) if(i<=j) {
			string t="";
			forint(k, i,j) t+=s[k];
			string p=t;
			reverse(p.begin(), p.end());
			if(p==t) ans=max(ans, j-i+1);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABAA"; int Arg1 = 3; verify_case(0, Arg1, longestLength(Arg0)); }
	void test_case_1() { string Arg0 = "ABB"; int Arg1 = 2; verify_case(1, Arg1, longestLength(Arg0)); }
	void test_case_2() { string Arg0 = "ABCBCA"; int Arg1 = 3; verify_case(2, Arg1, longestLength(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	LongestPalindrome ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
