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

const LL MOD=LL(1e9)+7;
const int MAXN=2550;
const int MAXK=15;

class Stackol {
public:
	int countPrograms(vector <string> outputFragments, int k) {
		string s;
		forn(i, outputFragments.size()) s+=outputFragments[i];
		int cb[MAXN], ib[MAXN];
		int n=s.size();
		cb[0]=0;
		forint(i, 1, n) {
			cb[i]=cb[i-1];
			if(s[i-1]=='B') ++cb[i];
			ib[i]=cb[i]-cb[i-1];
		}

		static LL f[MAXN][MAXK];
		fillchar(f, 0);
		f[0][0]=1;
		forint(i, 0, n) forint(c, 1, k) {
			(f[i][c]+=f[i][c-1])%=MOD;
			forintdown(j, i, 1) {
				int flag=0;
				int nb=cb[i]-cb[j-1];
				if(nb==0) flag=1;
				else {
					int k=i-nb+1;
					if(ib[k]==0) ++flag;
					if(ib[j]==1) ++flag;
				}
				(f[i][c]+=flag*f[j-1][c-1])%=MOD;
			}
		}
		LL ans=0;
		forint(c, 0, k) (ans+=f[n][c])%=MOD;
		return int(ans) ;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; verify_case(0, Arg2, countPrograms(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"AAAA","BABA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, countPrograms(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"AB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 1; verify_case(2, Arg2, countPrograms(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"AAABABABAABA", "AA", "BBAB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 94; verify_case(3, Arg2, countPrograms(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"AAAAAAAAAAAA","B"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 120; verify_case(4, Arg2, countPrograms(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Stackol ___test;
	//___test.run_test(0);return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
