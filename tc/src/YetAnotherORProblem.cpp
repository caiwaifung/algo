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

const LL MOD=LL(1e9)+9;

class YetAnotherORProblem {
public:
	int r[10][64];
	int n;
	int countSequences(vector<long long> R) {
		n=(int)R.size();
		forn(i, n) {
			LL x=R[size_t(i)];
			forn(j, 64) {
				r[i][j]=int(x&1); x>>=1;
			}
		}

		LL f[65][1<<10];
		fillchar(f, 0);
		f[64][0]=1;
		forintdown(i, 63, 0) forn(s, 1<<n) {
			LL cur=f[i+1][s];
			forn(j, n+1) {
				int s2=s; bool flag=true;
				forn(k, n) {
					int x=0; if(k==j) x=1;
					if((s&(1<<k))==0) {
						if(x>r[k][i]) flag=false;
						if(x<r[k][i]) s2|=(1<<k);
					}
				}
				if(flag)
					(f[i][s2]+=cur) %=MOD;
			}
		}
		LL ans=0;
		forn(s, 1<<n) (ans+=f[0][s]) %=MOD;
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {3,5}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(0, Arg1, countSequences(Arg0)); }
	void test_case_1() { long Arr0[] = {3,3,3}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(1, Arg1, countSequences(Arg0)); }
	void test_case_2() { long Arr0[] = {1,128}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 194; verify_case(2, Arg1, countSequences(Arg0)); }
	void test_case_3() { long Arr0[] = {26,74,25,30}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8409; verify_case(3, Arg1, countSequences(Arg0)); }
	void test_case_4() { long Arr0[] = {1000000000,1000000000}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 420352509; verify_case(4, Arg1, countSequences(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	YetAnotherORProblem ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
