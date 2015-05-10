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

class SplitStoneGame {
public:
	string k(vector<int> number) {
		return "LOSE";
	}
	string winOrLose(vector <int> number) {
		bool f[55][55];
		int n=50;
		forint(i, 0, n) f[i][0]=false;
		forint(i, 1, n) {
			forint(j, 1, i) {
				f[i][j]=false;
				if(j-1>=2) if(!f[i-1][j-1]) f[i][j]=true;
				if(j-1>=1 && i-j>=1) if(!f[i-1][j]) f[i][j]=true;
				if(i-j>=2) if(!f[i-1][j+1]) f[i][j]=true;
			}
		}
		forint(i, 1, 30) {forint(j, 0, i) printf("%d", f[i][j]?1:0); printf("\n");}
		n=number.size();
		int t=0; forn(i, n) if(number[i]>1) ++t;
		return f[n][t]?"WIN":"LOSE";
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LOSE"; verify_case(0, Arg1, winOrLose(Arg0)); }
	void test_case_1() { int Arr0[] = {2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LOSE"; verify_case(1, Arg1, winOrLose(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "WIN"; verify_case(2, Arg1, winOrLose(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 3, 2, 2, 4, 3, 1, 4, 4, 1, 2, 4, 4, 1, 4, 3, 1, 4, 2, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "WIN"; verify_case(3, Arg1, winOrLose(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 9, 1, 3, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LOSE"; verify_case(4, Arg1, winOrLose(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	SplitStoneGame ___test;
	___test.run_test(-1);
	forint(i, 1, 50) forint(j, 0, i) {
		VI numbers;
		forn(k, j) numbers.PB(2);
		forn(k, i-j) numbers.PB(1);
		if(___test.winOrLose(numbers)!=___test.k(numbers)) {
			printf("err @ %d: %d*[2], %d*[1]\n", i,j, i-j);
			printf("ans=%s\n", ___test.winOrLose(numbers).c_str());
			printf("out=%s\n", ___test.k(numbers).c_str());
			for(;;);
		} else printf("correct. %d %d\n",i,j);
	}
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
