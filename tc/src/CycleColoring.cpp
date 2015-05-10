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

class CycleColoring
{
public:
	int countColorings(vector <int> vertexCount, vector <int> fromVertex, vector <int> toVertex, int K)
	{
		static LL w[1001000][2];
		static LL f[55][2];
		LL colors;
		colors=K;
		int n=(int)vertexCount.size();

		fillchar(w, 0);
		w[1][0]=1;
		forint(i, 1, 1000100) {
			(w[i+1][1]+=w[i][0]) %=MOD;
			(w[i+1][1]+=w[i][1]*(colors-2)) %=MOD;
			(w[i+1][0]+=w[i][1]*(colors-1)) %=MOD;
		}

		fillchar(f, 0);
		f[0][0]=colors;
		forn(i, n) {
			int m=vertexCount[i], x=toVertex[(i+n-1)%n], y=fromVertex[i];
			int l=(y-x+m)%m+1, r=m-l+2;
			//printf("l=%d r=%d\n",l,r);
			(f[i+1][0]+=(f[i][0]*w[l][0]%MOD*w[r][0])) %=MOD;
			(f[i+1][1]+=(f[i][0]*w[l][1]%MOD*w[r][1])) %=MOD;
			(f[i+1][1]+=(f[i][1]*(colors-2)%MOD*w[l][1]%MOD*w[r][1])) %=MOD;
			(f[i+1][1]+=(f[i][1]*w[l][0]%MOD*w[r][0])) %=MOD;
			(f[i+1][0]+=(f[i][1]*(colors-1)%MOD*w[l][1]%MOD*w[r][1])) %=MOD;
		}
		LL ans=f[n][0];
		ans=(ans%MOD+MOD)%MOD;
		return (int)ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 12; verify_case(0, Arg4, countColorings(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 12; verify_case(1, Arg4, countColorings(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {3, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 0; verify_case(2, Arg4, countColorings(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {9, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 8; int Arg4 = 589124602; verify_case(3, Arg4, countColorings(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {14, 15, 16, 17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 10, 4, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 3, 14, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 614; int Arg4 = 818050159; verify_case(4, Arg4, countColorings(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {482373, 283712, 883, 12834, 5, 5, 482734, 99912, 35881, 277590}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {59283, 49782, 0, 0, 3, 2, 84791, 40017, 2263, 461}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {150173, 709, 11108, 0, 4, 7, 5902, 712, 190232, 390331}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 479360784; int Arg4 = 763634309; verify_case(5, Arg4, countColorings(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	CycleColoring ___test;
	//___test.run_test(0); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
