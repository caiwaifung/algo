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

#define _ (size_t)
#define all(a) a.begin(), a.end()
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

// ------------------------ template ends here ------------------------ //

class DevuAndPlantingTrees {
public:
    int maximumTreesDevuCanGrow(vector <string> garden) {
        int f[55][4]; int n=(int)garden[0].size();
        fillchar(f, 200);
        f[0][0]=0;
        forint(i, 1, n) forn(a, 4) {
            if(f[i-1][a]<0) continue;
            int a1=a&1, a2=(a>>1)&1;
            forn(b, 4) {
                int b1=b&1, b2=(b>>1)&1;
                if(garden[0][i-1]=='*' && b1==0) continue;
                if(garden[1][i-1]=='*' && b2==0) continue;
                if(a1+a2+b1+b2>1) continue;
                setmax(f[i][b], f[i-1][a]+b1+b2);
            }
        }
        int ans=0;
        forn(a, 4) setmax(ans, f[n][a]);
        return int(ans);
    }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"..", ".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_1() { string Arr0[] = {"..", ".*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_2() { string Arr0[] = {"...",
"..*"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_3() { string Arr0[] = {".....*..........",
".*.......*.*..*."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(3, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_4() { string Arr0[] = {"....*.*.*...........*........",
"*..........*..*.*.*....*...*."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(4, Arg1, maximumTreesDevuCanGrow(Arg0)); }
	void test_case_5() { string Arr0[] = {".....*..*..........*............................*",
"*..*.............*...*.*.*.*..*.....*.*...*...*.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 23; verify_case(5, Arg1, maximumTreesDevuCanGrow(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	DevuAndPlantingTrees ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
