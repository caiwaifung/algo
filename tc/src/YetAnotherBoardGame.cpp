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

class YetAnotherBoardGame {
public:
	int full;
	void perform0(int a[], int i, int s) {
		a[i]^=(s>>1);
		a[i]^=((s<<1)&full);
		if(i>0) a[i-1]^=s;
		a[i+1]^=s;
	}
	void perform1(int a[], int i, int s) {
		a[i]^=s;
		a[i]^=(s>>1);
		a[i]^=((s<<1)&full);
		if(i>0) a[i-1]^=s;
		a[i+1]^=s;
	}
	int bcnt(int x) {
		return x==0 ? 0 : 1+bcnt(x-(x&-x));
	}
	int minimumMoves(vector<string> board) {
		int n=board.size();
		int m=board[0].size();
		int ans=1<<30, maxval=ans;
		int a[15];
		forn(i, n) {
			a[i]=0;
			forn(j, m) if(board[i][j]=='W') a[i]|=(1<<j);
		}
		full=(1<<m)-1;
		forn(sp, 1<<m) {
			int sq=full^sp;
			for(int s0=sp; ; s0=(s0-1)&sp) {
				int curans=0;
				int b[15]; forn(i, n) b[i]=a[i];
				perform1(b, 0, s0); curans+=bcnt(s0);
				for(int i=1; i<n; ++i) {
					int s=b[i-1];
					if((s|sp)==sp) {
						perform1(b, i, s); curans+=bcnt(s);
					} else if((s|sq)==sq) {
						perform0(b, i, s); curans+=bcnt(s);
					} else {
						curans=-1; break;
					}
				}
				if(curans>=0 && b[n-1]==0)
					setmin(ans, curans);
				if(s0==0) break;
			}
			for(int s0=sq; ; s0=(s0-1)&sq) {
				int curans=0;
				int b[15]; forn(i, n) b[i]=a[i];
				perform0(b, 0, s0); curans+=bcnt(s0);
				for(int i=1; i<n; ++i) {
					int s=b[i-1];
					if((s|sp)==sp) {
						perform1(b, i, s); curans+=bcnt(s);
					} else if((s|sq)==sq) {
						perform0(b, i, s); curans+=bcnt(s);
					} else {
						curans=-1; break;
					}
				}
				if(curans>=0 && b[n-1]==0)
					setmin(ans, curans);
				if(s0==0) break;
			}
		}
		if(ans==maxval) ans=-1;
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minimumMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"BBW",
 "WWW",
 "BWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, minimumMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {"WBW",
 "BBW",
 "WBW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, minimumMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, minimumMoves(Arg0)); }
	void test_case_4() { string Arr0[] = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, minimumMoves(Arg0)); }
	void test_case_5() { string Arr0[] = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; verify_case(5, Arg1, minimumMoves(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	YetAnotherBoardGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
