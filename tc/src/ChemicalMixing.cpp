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

bool f[1010][5010];
PII lst[1010*5010];
int len;

class ChemicalMixing {
	void P(int x, int y) {
		if(!f[x][y]) {
			f[x][y]=true; lst[++len]=MP(x, y);
		}
	}
public:
	double closestBlend(vector <int> volume, vector <int> solute, int minVolume, double desiredStrength) {
		fillchar(f, false); len=0;
		P(0, 0);
		forn(i, volume.size()) {
			int tl=len;
			forint(j, 1, tl) {
				P(lst[j].fi+solute[i], lst[j].se+volume[i]);
			}
		}
		double ans=1e50;
		forint(x, 1, 1000) forint(y, minVolume, 5000)
			if(f[x][y]) ans=min(ans, abs(desiredStrength-(double)x/(double)y));
		
		return double(ans) ;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; double Arg3 = 0.20; double Arg4 = 0.04999999999999999; verify_case(0, Arg4, closestBlend(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {10, 10, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 5,  5,  5,  0} ; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 35; double Arg3 = 0.5; double Arg4 = 0.125; verify_case(1, Arg4, closestBlend(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {20, 20, 20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {15, 15, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 40; double Arg3 = 0.5; double Arg4 = 0.0; verify_case(2, Arg4, closestBlend(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {50, 50, 50, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {12, 4, 20, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 100; double Arg3 = 0.5; double Arg4 = 0.18; verify_case(3, Arg4, closestBlend(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	ChemicalMixing ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
