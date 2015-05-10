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

int black[55*3500];
int n;

class MathContest {
public:
	int countBlack(string ballSequence, int repetitions) {
		n=(int)ballSequence.size();
		forint(i, 1, n) black[i]=(ballSequence[size_t(i-1)]=='B'?1:0);
		int len=n*repetitions;
		forint(i, n+1, len) black[i]=black[i-n];
		int rev=0, inv=0;
		int ans=0;
		for(int i=1, j=len; i<=j; ) {
			int cur;
			if(rev==0) {
				cur=black[i++]^inv;
			} else {
				cur=black[j--]^inv;
			}
			ans+=cur;
			rev^=cur^1, inv^=cur;
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "BBWWB"; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, countBlack(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "BBB"; int Arg1 = 10; int Arg2 = 1; verify_case(1, Arg2, countBlack(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "BW"; int Arg1 = 10; int Arg2 = 20; verify_case(2, Arg2, countBlack(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "WWWWWWWBWWWWWWWWWWWWWW"; int Arg1 = 1; int Arg2 = 2; verify_case(3, Arg2, countBlack(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	MathContest ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
