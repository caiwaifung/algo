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

const LL MOD=LL(1e9)+7;

class TaroCheckers {
public:
	int getNumber(vector <int> left, vector <int> right, int m) {
		static LL P[55][55];
		fillchar(P, 0);
		forint(i, 0, 52) {
			P[i][0]=1;
			forint(j, 1, i) P[i][j]=(P[i-1][j-1]*i)%MOD;
		}

		static LL f[222][55][55];
		static int lcnt[222], ltot[222];
		static int rtot[222];
		int n=left.size();

		fillchar(lcnt, 0);
		fillchar(ltot, 0);
		forn(i, left.size()) lcnt[left[i]]++;
		forintdown(i, m, 1) ltot[i]=ltot[i+1]+lcnt[i];
		fillchar(rtot, 0);
		forn(i, right.size()) rtot[m-right[i]+1]++;
		forint(i, 1, m) rtot[i]+=rtot[i-1];


		fillchar(f, 0);
		f[0][0][0]=1;
		forint(i, 0, m-1) forint(t, 0, n) forint(k, 0, n) {
			LL val=f[i][t][k]; if(val==0) continue;
			//printf("\nf[%d,%d,%d]=%I64d\n",i,t,k,val);

			int l=lcnt[i+1], r=rtot[i+1];
			//printf("l=%d r=%d\n",l,r);
			if(t>=l && r>k) { // cover right
				LL tmp=val;
				(tmp *= r-k) %=MOD;
				(tmp *= P[t][l]) %=MOD;
				//printf(" #1 tmp=%I64d\n", tmp);
				(f[i+1][t-l][k+1] += tmp) %=MOD;
			}
			int s=n-ltot[i+1]-rtot[i+1];
			if(t>=l && s>=1) { // cover space
				LL tmp=val;
				(tmp *= s) %=MOD;
				(tmp *= P[t][l]) %=MOD;
				//printf(" #2 tmp=%I64d\n", tmp);
				(f[i+1][t-l][k] += tmp) %=MOD;
			}
			if(t+1>=l) { // cover left
				LL tmp=val;
				(tmp *= P[t+1][l]) %=MOD;
				//printf(" #3 tmp=%I64d\n", tmp);
				(f[i+1][t-l+1][k] += tmp) %=MOD;
			}
			if(t>=l) { // cover nothing
				LL tmp=val;
				(tmp *= P[t][l]) %=MOD;
				(f[i+1][t-l][k] += tmp) %=MOD;
			}
		}
		LL ans=f[m][0][n];
		//forint(t, 0, n) (ans+=f[m][t][n]) %=MOD;
		ans=(ans%MOD+MOD)%MOD;
		return int(ans);
	}
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; int Arg3 = 1; verify_case(0, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1, 4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; int Arg3 = 6; verify_case(1, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {4, 7, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 4, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; int Arg3 = 5760; verify_case(2, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {10, 25, 100, 74}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100, 47, 27, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 200; int Arg3 = 796178974; verify_case(3, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {21, 99, 87, 12, 138, 16, 78, 36, 98, 40, 57, 10, 61, 100, 8, 110, 96, 9, 69, 110, 14, 71}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {83, 8, 25, 169, 1, 89, 109, 89, 19, 112, 39, 112, 87, 66, 116, 16, 41, 97, 52, 70, 111, 23}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 190; int Arg3 = 235017573; verify_case(4, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {3, 37, 26, 50, 8, 3, 38, 15, 58, 47, 35, 8, 27, 22, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {19, 26, 62, 15, 84, 13, 6, 46, 22, 53, 23, 8, 29, 55, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 102; int Arg3 = 528024858; verify_case(5, Arg3, getNumber(Arg0, Arg1, Arg2)); }
// END CUT HERE
};

// BEGIN CUT HERE
int main() {
	TaroCheckers ___test;
	//___test.run_test(5); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
