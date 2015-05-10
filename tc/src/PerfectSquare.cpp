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

	bool a[9999][410];

class PerfectSquare {
public:
	VI fac(int x) {
		VI a;
		for(int y=2; y*y<=x; ++y)
			if(x%y==0) {
				int t=0;
				while(x%y==0) ++t, x/=y;
				if(t%2==1) a.PB(y);
			}
		if(x>=2) a.PB(x);
		sort(a.begin(), a.end());
		return a;
	}
	int n, m;

	int gauss() {
		int cnt=0;
		forint(i, 1, min(n, m)) {
			forint(x, i, n) forint(y, i, m)
				if(a[x][y]) {
					forint(k, 0, m) swap(a[x][k], a[i][k]);
					forint(k, 1, n) swap(a[k][y], a[k][i]);
					goto um_ok;
				}
			break;
			um_ok:
			forint(x, i+1, n) if(a[x][i]) {
				forint(j, 0, m) a[x][j]^=a[i][j];
			}
			++cnt;
		}
		forint(x, cnt+1, n) if(a[x][0]) return 0;
		int ans=1;
		cnt=m-cnt;
		forn(i, cnt) ans=(ans*2)%int(1e9+7);
		return ans;
	}
	
	int ways(vector<int> x) {
		vector<VI> xs(x.size());
		VI all;
		forn(i, x.size()) {
		//printf("$i=%d\n",i);
			xs[i]=fac(x[i]);
			forn(j, xs[i].size())
				all.PB(xs[i][j]);
		}
		sort(all.begin(), all.end());
		all.erase(unique(all.begin(), all.end()), all.end());
		//printf("$0\n");
		forn(i, x.size())
			forn(j, xs[i].size())
				xs[i][j]=int(lower_bound(all.begin(), all.end(), xs[i][j])-all.begin());
		//printf("$1\n");

		int width=0;
		while(width*width!=(int)x.size()) ++width;
		n=width*2+all.size();
		m=x.size();
		forint(i, 1, width) {
			forint(j, 1, m)
				a[i][j]=((j-1)/width+1==i);
			a[i][0]=true;
		}
		forint(i, 1, width) {
			forint(j, 1, m)
				a[i+width][j]=((j-1)%width+1==i);
			a[i+width][0]=true;
		}
		//printf("$2\n");
		forint(i, 1, all.size()) {
			forint(j, 1, m)
				a[width*2+i][j]=false;
			a[width*2+i][0]=false;
		}
		forint(j, 1, m)
			forn(k, xs[j-1].size()) {
				int i=xs[j-1][k]+1;
				a[width*2+i][j]=true;
			}
		//printf("$3\n");

		int ans=gauss();
		
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1,
 1, 2}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
	void test_case_1() { int Arr0[] = {620, 620,
 620, 620}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, ways(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 2, 3,
 4, 5, 6,
 7, 8, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, ways(Arg0)); }
	void test_case_3() { int Arr0[] = {2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, ways(Arg0)); }
	void test_case_4() { int Arr0[] = {2, 3, 4, 5,
 6, 7, 8, 9,
 10,11,12,13,
 14,15,16,17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(4, Arg1, ways(Arg0)); }
	void test_case_5() { int Arr0[] = {9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 993282280; verify_case(5, Arg1, ways(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	PerfectSquare ___test;
	/*
	___test.run_test(0); return 0;
	/*/
	___test.run_test(-1); return 0;
	//*/
}
// END CUT HERE
