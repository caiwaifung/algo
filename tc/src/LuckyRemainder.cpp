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


// ------------------------ template ends here ------------------------ //

class LuckyRemainder {
public:
	int getLuckyRemainder(string X) {
		const int MOD=9;
		//const int MOD=99999999;
		int C[99][99];
		forint(i, 0, 55) C[i][0]=C[i][i]=1;
		forint(i, 1, 55) forint(j, 1, i-1) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		int p10[99];
		p10[0]=1; forint(i, 1, 55) p10[i]=p10[i-1]*10%MOD;
		int ans=0;
		forn(i, X.size()) {
			int cur=int(X[i]-'0');
			int le=i, ri=X.size()-i-1;
			forint(l, 0, le) forint(r, 0, ri)
				(ans+=C[le][l]*C[ri][r]*cur*p10[r]) %=MOD;
		}
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "123"; int Arg1 = 6; verify_case(0, Arg1, getLuckyRemainder(Arg0)); }
	void test_case_1() { string Arg0 = "24816"; int Arg1 = 3; verify_case(1, Arg1, getLuckyRemainder(Arg0)); }
	void test_case_2() { string Arg0 = "8"; int Arg1 = 8; verify_case(2, Arg1, getLuckyRemainder(Arg0)); }
	void test_case_3() { string Arg0 = "11235813213455"; int Arg1 = 7; verify_case(3, Arg1, getLuckyRemainder(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	LuckyRemainder ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
