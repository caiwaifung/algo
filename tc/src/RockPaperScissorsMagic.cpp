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

const int MOD=int(1e9)+7;
LL binom[1010][1010];

class RockPaperScissorsMagic {
public:
	int count(int win, int lose, int tie, vector <int> card) {
		forint(i, 0, 1000) binom[i][0]=binom[i][i]=1;
		forint(i, 1, 1000) forint(j, 1, i-1)
			binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;

		if(win==lose && tie==win) {
			LL ans=1;
			forn(i, card.size()) (ans*=3)%=MOD;
			return int(ans);
		} else {
			static LL t[3][2020][2020];
			const int D=1005;
			fillchar(t, 0);
			forn(c, 3) {
				int n=(int)std::count(all(card), c);
				forint(x, 0, n) forint(y, 0, n-x) {
					int z=n-x-y;
					(t[c][x-y+D][x-z+D]+=binom[n][x]*binom[n-x][y]%MOD) %=MOD;
				}
			}
			LL ans=0;
			forn(i, D*2) forn(j, D*2) {
				LL tmp=1;
				forn(c, 3) (tmp*=t[c][i][j])%=MOD;
				(ans+=tmp)%=MOD;
			}
			return int(ans);
		}
		return int(0);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 1; int Arr3[] = {0,1,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; verify_case(0, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 1; int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 6; verify_case(1, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arr3[] = {1,0,2,2,2,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 729; verify_case(2, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 514; int Arg1 = 451; int Arg2 = 145; int Arr3[] = {0,0,0,0,0,1,1,1,1,1,1,2,2,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(3, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 3; int Arg1 = 6; int Arg2 = 9; int Arr3[] = {0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2336040; verify_case(4, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 514; int Arg1 = 451; int Arg2 = 145; int Arr3[] = {0,0,0,1,1,1,1,1,1,2,2,2,2,2,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 116100; verify_case(5, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	RockPaperScissorsMagic ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
