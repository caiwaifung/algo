#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
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
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VPII;

const int MAXN=5050;
const LL MOD=LL(1e9)+7;
LL C[MAXN][MAXN];
LL f[MAXN];

class LongWordsDiv1 {
	public:
		int count(int n) {
			forint(i, 0, n) C[i][0]=C[i][i]=1;
			forint(i, 1, n) forint(j, 1, i-1) 
				C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
			f[1]=1;
			forint(i, 2, n) {
				f[i]=f[i-1];
				forint(j, 1, i-2)
					(f[i]+=(f[j]*f[i-j-1]%MOD)*C[i-1][j])%=MOD;
				f[i]=f[i]*i%MOD;
			}
			return int(f[n]);
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1080; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 486425238; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	LongWordsDiv1 ___test; //cout<<___test.count(4)<<endl;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
