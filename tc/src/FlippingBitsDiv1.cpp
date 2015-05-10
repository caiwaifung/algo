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

const int LIM=18;

class FlippingBitsDiv1 {
public:
	int solve2(string s, int m) {
		int len=s.size();
		int n=(len-1)/m+1;
		int tn=len/m;
		int ans=1<<30;
		forn(st, 1<<tn) {
			bool fp[22], cfp=false;
			int val=0;
			forintdown(i, n-1, 0) {
				if(st&(1<<i)) cfp=!cfp, ++val;
				fp[i]=cfp;
			}
			//printf("st=%d v=%d\n",st,val);
			forn(i, m) {
				int c0=0, c1=0;
				for(int j=i, j0=0; j<len; j+=m, ++j0) {
					int x=s[j]-'0';
					if(fp[j0]) x^=1;
					if(x==0) ++c0; else ++c1;
				}
				//printf("i=%d 0=%d 1=%d\n",i,c0,c1);
				val+=min(c0, c1);
			}
			//printf("st=%d v=%d\n",st,val);
			setmin(ans, val);
		}
		return ans;
	}
	int solve1(string s, int m) {
		int len=s.size();
		int n=(len-1)/m+1;
		int ans=1<<30;
		forn(st, 1<<m) {
			int f[333][2];
			fillchar(f, 50);
			f[n][0]=0;
			forintdown(i, n, 1) forint(j, 0, 1) forint(k, 0, 1) {
				int val=f[i][j]+k;
				//printf("i=%d j=%d k=%d val=%d\n",i,j,k,val);
				forn(p, m) {
					int x=(i-1)*m+p;
					if(x>=len) continue;
					x=s[x]-'0'; int y=(st>>p)&1;
					val+=(x^j^k^y);
				}
				//printf("i=%d j=%d k=%d val=%d\n",i,j,k,val);
				setmin(f[i-1][j^k], val);
			}
			setmin(ans, f[0][0]);
			setmin(ans, f[0][1]);
		}
		return ans;
	}
	int getmin(vector<string> S, int M) {
		string s="";
		forn(i, S.size()) s+=S[i];
		if(M*M<=(int)s.size()) {
			return solve1(s, M);
		} else {
		//printf("2\n");
			return solve2(s, M);
		}
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"00111000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, getmin(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"101100001101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(1, Arg2, getmin(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"11111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 0; verify_case(2, Arg2, getmin(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"1101001000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 1; verify_case(3, Arg2, getmin(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"1","10","11","100","101","110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 4; verify_case(4, Arg2, getmin(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"1001011000101010001111111110111011011100110001001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 16; verify_case(5, Arg2, getmin(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	FlippingBitsDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
