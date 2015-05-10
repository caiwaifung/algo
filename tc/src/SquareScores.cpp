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

class SquareScores {
public:
	VI p; string s;
	double prob(int i, char c) {
		if(s[_ i]=='?') {
			int j=(int)(c-'a');
			if((int)p.size()<=j) return 0;
			return p[_ j]/100.0;
		}
		else {
			if(s[_ i]==c) return 1;
			else return 0;
		}
	}
	double calcexpectation(vector <int> _p, string _s) {
		p=_p, s=_s;
		double ans=0;
		forn(i, s.size()) {
			char le='a', ri='z';
			if(s[_ i]!='?') le=ri=s[_ i];
			for(char ch=le; ch<=ri; ++ch) {
				double tmp=1;
				forint(j, i, s.size()-1) {
					tmp*=prob(j, ch);
					if(tmp==0) break;
					//printf("i=%d j=%d tmp=%.2lf\n",i,j,tmp);
					ans+=tmp;
				}
			}
		}
		return double(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 99}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "aaaba"; double Arg2 = 8.0; verify_case(0, Arg2, calcexpectation(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {10, 20, 70}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "aa?bbbb"; double Arg2 = 15.0; verify_case(1, Arg2, calcexpectation(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {10, 20, 30, 40}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "a??c?dc?b"; double Arg2 = 11.117; verify_case(2, Arg2, calcexpectation(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {25, 25, 21, 2, 2, 25}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "a??b???????ff??e"; double Arg2 = 21.68512690712425; verify_case(3, Arg2, calcexpectation(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "??????????????????????????????"; double Arg2 = 31.16931963781721; verify_case(4, Arg2, calcexpectation(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {4, 3, 4, 3, 8, 2, 4, 3, 4, 4, 3, 2, 4, 4, 3, 4, 2, 4, 7, 6, 4, 4, 3, 4, 4, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "makigotapresentfromniko"; double Arg2 = 23.0; verify_case(5, Arg2, calcexpectation(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SquareScores ___test;
	/*
	___test.run_test(1);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
