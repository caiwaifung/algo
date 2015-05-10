#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }

class RandomPaintingOnABoard {
public:
	double expectedSteps(vector <string> prob) {
		int n=prob.size(), m=prob[0].size();
		int a[22][22], T=0;
		if(n<=m) {
			forn(i, n) forn(j, m) T+=(a[i][j]=prob[i][j]-'0');
		} else {
			swap(n, m);
			forn(i, n) forn(j, m) T+=(a[i][j]=prob[j][i]-'0');
		}
		int cnt[1555]; fillchar(cnt, 0);
		forn(st, 1<<n) {
			int r2=0; forn(i, n) if(st&(1<<i)) r2^=1;
			int t[22]={0}, t0=0;
			forn(i, n)
				if(st&(1<<i)) {
					forn(j, m) t0+=a[i][j];
				} else {
					forn(j, m) t[j]+=a[i][j];
				}
			int f[22][1555][2];
			fillchar(f, 0);
			f[0][t0][r2]=1;
			forn(j, m) forn(r, 2) {
				forint(x, 0, T) f[j+1][x][r]+=f[j][x][r];
				forint(x, 0, T-t[j]) f[j+1][x+t[j]][r^1]+=f[j][x][r];
			}
			forint(x, 1, T) cnt[x]+=f[m][x][1];
			forint(x, 1, T) cnt[x]-=f[m][x][0];
		}
		double ans=0.;
		forint(x, 1, T) ans+=cnt[x]*(double)T/(double)x;
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"10",
 "01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.0; verify_case(0, Arg1, expectedSteps(Arg0)); }
	void test_case_1() { string Arr0[] = {"11",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.6666666666666665; verify_case(1, Arg1, expectedSteps(Arg0)); }
	void test_case_2() { string Arr0[] = {"11",
 "12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 3.9166666666666665; verify_case(2, Arg1, expectedSteps(Arg0)); }
	void test_case_3() { string Arr0[] = {"0976",
 "1701",
 "7119"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 11.214334077031307; verify_case(3, Arg1, expectedSteps(Arg0)); }
	void test_case_4() { string Arr0[] = {"000000000000001000000",
 "888999988889890999988",
 "988889988899980889999",
 "889898998889980999898",
 "988889999989880899999",
 "998888998988990989998",
 "998988999898990889899"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1028.7662876159634; verify_case(4, Arg1, expectedSteps(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	RandomPaintingOnABoard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
