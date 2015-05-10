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

class EllysScrabble
{
public:
	string getMin(string letters, int d)
	{
		int n=letters.size();
		bool used[99]; fillchar(used, false);
		string s="";
		forn(i, n) {
			int j=-1; char best=char('Z'+1);
			if(i-d>=0 && !used[i-d]) {
				used[i-d]=true;
				s+=letters[i-d];
			} else {
				forint(k, i-d, i+d) if(k>=0 && k<n)
					if(!used[k])
						if(letters[k]<best) {
							best=letters[k];
							j=k;
						}
				used[j]=true;
				s+=best;
			}
		}
		return s;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "TOPCODER"; int Arg1 = 3; string Arg2 = "CODTEPOR"; verify_case(0, Arg2, getMin(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "ESPRIT"; int Arg1 = 3; string Arg2 = "EIPRST"; verify_case(1, Arg2, getMin(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "BAZINGA"; int Arg1 = 8; string Arg2 = "AABGINZ"; verify_case(2, Arg2, getMin(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; int Arg1 = 9; string Arg2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; verify_case(3, Arg2, getMin(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "GOODLUCKANDHAVEFUN"; int Arg1 = 7; string Arg2 = "CADDGAHEOOFLUKNNUV"; verify_case(4, Arg2, getMin(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "AAAWDIUAOIWDESBEAIWODJAWDBPOAWDUISAWDOOPAWD"; int Arg1 = 6; string Arg2 = "AAAADDEIBWAEUIODWADSBIAJWODIAWDOPOAWDUOSPWW"; verify_case(5, Arg2, getMin(Arg0, Arg1)); }
	void test_case_6() { string Arg0 = "ABRACADABRA"; int Arg1 = 2; string Arg2 = "AABARACBDAR"; verify_case(6, Arg2, getMin(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	EllysScrabble ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
