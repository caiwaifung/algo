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

const int MAXN=2555;
int fl[MAXN][MAXN], fr[MAXN][MAXN];
LL p[MAXN];

class LittleElephantAndRGB {
public:
	int minG;
	int fc(int cur, char c) {
		if(cur==minG) return minG;
		return c=='G' ? cur+1 : 0;
	}
	long long getNumber(vector <string> list, int minGreen) {
		minG=minGreen;
		string s="";
		forn(i, list.size()) s+=list[i];
		int n=s.size();

		fillchar(fl, 0);
		forint(i, 1, n) {
			char ch=s[i-1];
			fl[i][ch=='G']++;
			forint(j, 0, minGreen)
				fl[i][fc(j,ch)]+=fl[i-1][j];
		}
		fillchar(fr, 0);
		forintdown(i, n, 1) {
			char ch=s[i-1];
			fr[i][ch=='G']++;
			forint(j, 0, minGreen)
				fr[i][fc(j,ch)]+=fr[i+1][j];
		}

		LL ans=0;
		fillchar(p, 0);
		forint(i, 1, n) {
			forint(j, 0, minGreen) {
				//printf("i=%d s[%d]=%lld fr[%d][%d]=%lld\n", i,minGreen-j,p[minGreen-j],i,j,fr[i][j]);
				ans+=p[minGreen-j]*(LL)fr[i][j];
				}
			LL sum=0;
			forintdown(j, minGreen, 0) {
				sum+=(LL)fl[i][j];
				//printf("fl[%d][%d]=%lld\n",i,j,fl[i][j]);
				p[j]+=sum;
				}
		}
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"GRG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 1LL; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"GG", "GG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 9LL; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"GRBGRBBRG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 11LL; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"RRBRBBRRR", "R", "B"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; long long Arg2 = 0LL; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"GRGGGRBRGG", "GGGGGGGG", "BRGRBRB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long long Arg2 = 12430LL; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	LittleElephantAndRGB ___test;
	___test.run_test(-1);
	//___test.run_test(1);
	return 0;
}
// END CUT HERE
