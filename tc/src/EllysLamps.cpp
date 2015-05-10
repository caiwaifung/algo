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

void setmin(int &x, int y) { if(y<x) x=y; }

class EllysLamps
{
public:
	int w[99][99];
	int a[99];
	int n;
	int f[99];
	int getMin(string lamps)
	{
		n=lamps.size();
		forint(i, 1, n) a[i]=(lamps[i-1]=='Y'?1:0);
		forint(i, 1, n) {
			int f[99][2];
			fillchar(f, 50);
			f[i][a[i]]=0;
			forint(j, i+1, n) {
				setmin(f[j][a[j]], f[j-1][0]);
				setmin(f[j][a[j]], f[j-1][1]+1);
				setmin(f[j][a[j]^1], f[j-1][1]);
				setmin(f[j][a[j]^1], f[j-1][0]+1);
				w[i][j]=min(f[j][0], f[j][1]+1);
			}
		}
		f[0]=0;
		forint(j, 1, n) {
			f[j]=f[j-1];
			forint(i, 1, j-1) f[j]=max(f[j], f[i-1]+w[i][j]);
		}
		return f[n];
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNNYN"; int Arg1 = 2; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { string Arg0 = "NNN"; int Arg1 = 0; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { string Arg0 = "YY"; int Arg1 = 0; verify_case(2, Arg1, getMin(Arg0)); }
	void test_case_3() { string Arg0 = "YNYYYNNNY"; int Arg1 = 3; verify_case(3, Arg1, getMin(Arg0)); }
	void test_case_4() { string Arg0 = "YNYYYYNYNNYYNNNNNNYNYNYNYNNYNYYYNY"; int Arg1 = 13; verify_case(4, Arg1, getMin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	EllysLamps ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
