#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

class MinimumCuts {
    VPI es[100];
    int go(int x) {
        if(es[x].empty()) return 1<<25;
        int ans=0;
        for(PII p: es[x]) {
            int tmp=min(go(p.fi), p.se);
            ans+=tmp;
        }
        return ans;
    }
public:
    int costPaid(vector <int> parent, vector <int> cost) {
        repn(i, 100) es[i].clear();
        repn(i, parent.size())
            es[parent[i]].pb(mp(i+1, cost[i]));
        int ans=go(0);
        return (int)(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, costPaid(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10000, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10001; verify_case(1, Arg2, costPaid(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 0, 1, 1, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 5, 1, 2, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(2, Arg2, costPaid(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 0, 1, 1, 2, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9, 9, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, costPaid(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0, 1, 0, 3, 3, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 5, 10000, 100, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 105; verify_case(4, Arg2, costPaid(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {27, 284, 7, 1, 111, 2015, 1, 1, 1, 2, 10, 17, 13, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 52; verify_case(5, Arg2, costPaid(Arg0, Arg1)); }
	void test_case_6() { int Arr0[] = {0, 1, 0, 1, 3, 2, 3, 6, 8, 7, 4, 9, 9, 6, 10, 4, 11, 7, 18,
16, 8, 16, 15, 22, 22, 14, 21, 20, 24, 28, 13, 26, 29, 29, 28,
27, 10, 36, 11, 34, 38, 26, 39, 31, 18, 14, 31, 41, 47, 40,
20, 39, 34, 40, 38, 23, 35, 43, 50, 25, 41, 23, 30, 36, 43, 37,
61, 2, 44, 69, 65, 48, 19, 47, 58, 68, 25, 45, 55, 45, 15, 68,
42, 73, 73, 64, 62, 83, 72, 86, 54, 44, 67, 80, 50, 54, 58,
71, 35}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2714, 8445, 7931, 3073, 338, 5428, 5719, 7455, 1386, 4879, 6745,
9486, 9264, 2855, 3930, 325, 2129, 7512, 1146, 6774, 1092, 3306,
2253, 7968, 404, 9278, 900, 6980, 6728, 7924, 2308, 7956, 1617,
6089, 6500, 5671, 6799, 6173, 7896, 6474, 8416, 9090, 5205, 369,
1494, 5153, 7984, 6363, 6116, 9575, 3544, 1842, 9909, 5197, 3293,
9745, 4953, 6965, 6891, 8881, 5356, 9616, 4567, 6300, 9093, 3292,
7460, 8419, 5144, 7595, 1955, 4363, 3320, 639, 9029, 6785, 5149,
3985, 7341, 2095, 7374, 5089, 2263, 6470, 459, 8487, 1312, 5259,
6601, 8680, 9472, 5855, 6010, 1892, 7915, 326, 2713, 380, 9887}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8771; verify_case(6, Arg2, costPaid(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    MinimumCuts ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
