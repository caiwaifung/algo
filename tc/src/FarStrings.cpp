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

class FarStrings {
public:
	int cal(string s, string t) {
		int n=t.size();
		int f[33][33];
		f[0][0]=0;
		forint(i, 1, n) f[i][0]=f[0][i]=i;
		forint(i, 1, n) forint(j, 1, n) {
			if(s[i-1]==t[j-1] || s[i-1]=='?')
				f[i][j]=f[i-1][j-1];
			else f[i][j]=min(min(f[i-1][j]+1, f[i][j-1]+1), f[i-1][j-1]+1);
		}
		return f[n][n];
	}
	vector<string> find(string t) {
		int n=t.size();
		vector<string> ans;
		forint(i, 1, n) {
			string s="";
			forn(j, n) {
				s+=' ';
				for(char c='a'; c<='z'; ++c) {
					s[j]=c;
					string s1=s, s2=s;
					while((int)s1.size()<n) {
						s1+='?';
						s2+='.';
					}
					if(cal(s1, t)<=i && cal(s2, t)>=i)
						break;
				}
			}
			ans.PB(s);
		}
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "atan"; string Arr1[] = {"aaan", "aaaa", "aaba", "babb" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { string Arg0 = "ir"; string Arr1[] = {"ar", "aa" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { string Arg0 = "aaa"; string Arr1[] = {"aab", "abb", "bbb" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { string Arg0 = "bazinga"; string Arr1[] = {"aazinga", "aaainga", "aaaanga", "aaaaaga", "aaaaaaa", "aaaaaab", "abbaabb" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, find(Arg0)); }
	void test_case_4() { string Arg0 = "bcdab"; string Arr1[] = {"acdab", "aadab", "aaaab", "aaaaa", "aaaca" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, find(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	FarStrings ___test;
	___test.run_test(-1);
	//___test.run_test(1);
	return 0;
}
// END CUT HERE
