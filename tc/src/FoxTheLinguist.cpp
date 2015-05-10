// 17:10
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

class FoxTheLinguist {
public:
	int minimalHours(int n, vector <string> courseInfo) {
		int num=n*10+1, root=num-1;
		int g[110][110], maxval;
		fillchar(g, 50); maxval=g[0][0];
		#define id(x, y) ((x)*10+(y))
		string input=""; forn(i, courseInfo.size()) input+=courseInfo[i];
		forn(i, num) g[i][i]=0;
		for(int i=0; ; ) {
			while(i<(int)input.size() && input[i]==' ') ++i;
			if(i>=(int)input.size()) break;
			int x1=input[i++]-'A';
			int y1=input[i++]-'0';
			i+=2;
			int x2=input[i++]-'A';
			int y2=input[i++]-'0';
			i++;
			int t=input[i++]-'0';
			t=t*10+input[i++]-'0';
			t=t*10+input[i++]-'0';
			t=t*10+input[i++]-'0';
			//printf("(%d,%d) -> (%d,%d)  %d\n",x1,y1,x2,y2,t);
			for(int y=y1; y<10; ++y)
				setmin(g[id(x1,y)][id(x2,y2)], t);
		}
		forn(i, n) g[root][id(i,0)]=0;
		forn(k, num) forn(i, num) forn(j, num) setmin(g[i][j], g[i][k]+g[k][j]);

		int f[1100][110];
		fillchar(f, 50);
		forn(i, n) f[1<<i][id(i,9)]=0;
		forint(st, 1, (1<<n)-1) {
			forn(i, num) forn(j, num)
				setmin(f[st][j], f[st][i]+g[j][i]);
			forn(i, num) forint(s2, 1, (1<<n)-1)
				if((st&s2)==0)
					setmin(f[st|s2][i], f[st][i]+f[s2][i]);
		}
		int ans=f[(1<<n)-1][root];
		if(ans>=maxval) ans=-1;
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; string Arr1[] = {"A0->A9:1000 A0->A6:0300 A3->A9:0600"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 900; verify_case(0, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"A0->A9:1000 B0->B9:1000 A1->B9:0300 B1->A9:0200"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1200; verify_case(1, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; string Arr1[] = {"C0->A6:00", "01 A3", "->B9:0001 A3->C6:000", "1",
" C3->A9:0001 A9->C9:0001 A0->A9:9999",
" B0->B9:9999 C0->C9:9999 A6->A9:9999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(2, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; string Arr1[] = {"A0->A6:6666 A0->A9:9999",
" B0->B6:6666 B0->B9:9999",
" C0->C6:6666 C0->C9:9999",
" D0->D6:6666 D0->D9:9999",
" A6->B6:0666 B6->C6:0666",
" C6->D6:0666 D6->A6:0666",
" A9->B9:0099 B9->C9:0099",
" C9->D9:0099 D9->A9:0099"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10296; verify_case(3, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; string Arr1[] = {"A0->A9:9999 A0->A9:8888"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8888; verify_case(4, Arg2, minimalHours(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 1; string Arr1[] = {"A9->A9:0000",
" A9->A0:0000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(5, Arg2, minimalHours(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	FoxTheLinguist ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
