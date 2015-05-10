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

int n;

class ElephantDrinking {
public:
	struct Grid {
		int a[55][55];
		Grid() {
			fillchar(a, 0);
		}
		Grid(VS g) {
			fillchar(a, 0);
			forn(i, n) forn(j, n)
				a[i+1][j+1]=int(g[i][j]-'0');
		}
		void rotate() {
			int b[55][55];
			forint(i, 1, n) forint(j, 1, n)
				b[i][j]=a[j][n-i+1];
			forint(i, 1, n) forint(j, 1, n)
				a[i][j]=b[i][j];
		}
	};
	void cal_f(const Grid &a, Grid &f) {
		fillchar(f.a, 0);
		forint(i, 1, n) forint(j, 1, n) {
			forint(k, 1, j)
				f.a[i][j]=max(f.a[i][j], f.a[i-1][j]+a.a[i][k]);
			forint(k, 1, i)
				f.a[i][j]=max(f.a[i][j], f.a[i][j-1]+a.a[k][j]);
		}
	}
	int maxSum(vector<string> field) {
		n=field.size();
		Grid a(field);
		Grid f[4];
		forn(i, 4) {
			cal_f(a, f[i]);
			a.rotate();
			forint(j, 0, i) f[j].rotate();
		}
		/*
		forn(i, 4) {
			printf("f[%d]:\n",i);
			forint(x, 1, n) forint(y, 1, n) printf("%d%c", f[i].a[x][y],y<n?' ':'\n');
		}
		*/
		int rmax[55], cmax[55];
		forint(i, 1, n) {
			rmax[i]=0;
			forint(j1, 1, n) forint(j2, j1+1, n)
				rmax[i]=max(rmax[i], a.a[i][j1]+a.a[i][j2]);
		}
		forint(j, 1, n) {
			cmax[j]=0;
			forint(i1, 1, n) forint(i2, i1+1, n)
				cmax[j]=max(cmax[j], a.a[i1][j]+a.a[i2][j]);
		}
		int rsum[55], csum[55];
		rsum[0]=csum[0]=0;
		forint(i, 1, n) {
			rsum[i]=rsum[i-1]+rmax[i];
			csum[i]=csum[i-1]+cmax[i];
		}
		int ans=0;
		forint(i1, 0, n) forint(j1, 0, n)
			forint(i2, i1+1, n+1) forint(j2, 0, n)
				ans=max(ans, f[0].a[i1][j1]+f[1].a[i1][j1+1]+f[2].a[i2][j2+1]+f[3].a[i2][j2]+rsum[i2-1]-rsum[i1]);
		forint(j1, 0, n) forint(i1, 0, n)
			forint(j2, j1+1, n+1) forint(i2, 0, n)
				ans=max(ans, f[0].a[i1][j1]+f[3].a[i1+1][j1]+f[1].a[i2][j2]+f[2].a[i2+1][j2]+csum[j2-1]-csum[j1]);
		forint(i1, 1, n) forint(j1, 1, n)
			forint(i2, 1, i1) forint(j2, j1+1, n)
				ans=max(ans, f[0].a[i1][j1]+f[1].a[i2-1][j1+1]+f[2].a[i2][j2]+f[3].a[i1+1][j2-1]);
		forint(i1, 1, n) forint(j1, 1, n)
			forint(i2, i1+1, n) forint(j2, 1, j1)
				ans=max(ans, f[0].a[i1][j1]+f[1].a[i2-1][j1+1]+f[2].a[i2][j2]+f[3].a[i1+1][j2-1]);
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"00000",
 "00110",
 "01000",
 "00100",
 "00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, maxSum(Arg0)); }
	void test_case_1() { string Arr0[] = {"111",
 "191",
 "111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(1, Arg1, maxSum(Arg0)); }
	void test_case_2() { string Arr0[] = {"1010",
 "0011",
 "1100",
 "1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(2, Arg1, maxSum(Arg0)); }
	void test_case_3() { string Arr0[] = {"0011",
 "1110",
 "0111",
 "0101"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, maxSum(Arg0)); }
	void test_case_4() { string Arr0[] = {"11100",
 "00100",
 "11111",
 "00100",
 "10111"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(4, Arg1, maxSum(Arg0)); }
	void test_case_5() { string Arr0[] = {"023771",
 "509514",
 "675579",
 "367472",
 "575198",
 "115281"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 112; verify_case(5, Arg1, maxSum(Arg0)); }
	void test_case_6() { string Arr0[] = {"11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111011111111111111101111111111",
 "11111111111000111111111100001111111111",
 "11111111111000001111111000011111111111",
 "11111111111100000000000000011111111111",
 "11111111111100000000000000011111111111",
 "11111111111100000000000000111111111111",
 "11111111111110000000000000111111111111",
 "11111111111100000000000000011111111111",
 "11111111111000000000000000001111111111",
 "11111110111000000000000000001110111111",
 "11111110010000000000000000001100111111",
 "11111111000000000000000000001001111111",
 "11111111110000000000000000000011111111",
 "11111111100000110000000011000001111111",
 "11111110000001111000001111000000111111",
 "11111100000000111000001100000000101111",
 "11110000000110111000001101100000000111",
 "11111000000111110000000111111000111111",
 "11111100001111110000000111111111111111",
 "11111111111111100000000011111111111111",
 "11111111111111100000000011111111111111",
 "11111111111111000000000011111111111111",
 "11111111111111000000000011111111111111",
 "11111111111111100000000111111111111111",
 "11111111111111100000000111111111111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 148; verify_case(6, Arg1, maxSum(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	ElephantDrinking ___test;
	//___test.run_test(0); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
