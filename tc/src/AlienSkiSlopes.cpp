#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define _ (int)
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

class AlienSkiSlopes {
public:
    vector <int> raise(vector <int> h) {
        int n=(int)round(sqrt(h.size()));
        vector<VI> a(n, VI(n));
        repn(i, n) repn(j, n) a[i][j]=h[i*n+j];

        VI cx(n, 1<<30), cy(n, 0), lnk(n, -1);
        repn(cur, n) {
            VI slack(n, 1<<30), pre(n, -1);
            vector<bool> vis(n, false);
            int j0=-1;
            while(1) {
                if(j0>=0) vis[j0]=true;
                int i0=(j0<0?cur:lnk[j0]);
                if(i0<0) break;
                int d=1<<30, j1=-1;
                repn(j, n) if(!vis[j]) {
                    if(setmin(slack[j], cx[i0]+cy[j]-a[i0][j])) pre[j]=j0;
                    if(setmin(d, slack[j])) j1=j;
                }
                cx[cur]-=d;
                repn(j, n) if(vis[j]) {
                    cx[lnk[j]]-=d;
                    cy[j]+=d;
                } else {
                    slack[j]-=d;
                }
                j0=j1;
            }
            while(j0>=0) {
                int j=pre[j0];
                lnk[j0]=(j<0?cur:lnk[j]), j0=j;
            }
        }
        return cy;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {1,0,0,
 0,1,0,
 0,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, raise(Arg0)); }
	void test_case_1() { int Arr0[] = {1,2,3,4,
 2,3,4,1,
 3,4,1,2,
 4,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, raise(Arg0)); }
	void test_case_2() { int Arr0[] = {91, 19, 50, 21, 56,
 22, 96, 16, 30, 26,
 85, 1, 87, 63, 31,
 44, 25, 8, 94, 78,
 46, 55, 88, 41, 52}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {44, 13, 46, 22, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, raise(Arg0)); }
	void test_case_3() { int Arr0[] = {1000000000,0,0,
 1000000000,0,0,
 1000000000,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1000000000, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, raise(Arg0)); }
	void test_case_4() { int Arr0[] = {3,1,4,1,5,
 9,2,6,5,3,
 5,8,9,7,9,
 3,2,3,8,4,
 6,2,6,4,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 0, 1, 0, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, raise(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    AlienSkiSlopes ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
