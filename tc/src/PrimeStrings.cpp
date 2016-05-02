#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) int(a.size())
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

class PrimeStrings {
    int len(LL x) {
        int r=0; while(x>0) x/=2, ++r; return r;
    }
    VI decode(LL x) {
        VI r; while(x>0) r.pb(int(x%2)), x/=2;
        reverse(all(r)); return r;
    }
    LL solve(LL lbound, LL n, LL y, int k) {
        //printf("%lld %lld\n", lbound, n);
        if(len(n)-k<len(y)) return n-lbound+1;
        if(len(n)-k>len(y)) return 0;
        VI ns=decode(n); assert(sz(ns)==len(n));
        VI ys=decode(y); assert(sz(ys)==len(y));
        ys.resize(sz(ns), 1);

        static LL f[44][44][2][2];
        fillchar(f, 0);
        f[1][1][1][1]=1;
        rep(i, 1, sz(ns)-1) rep(c, 0, i) repn(sn, 2) repn(sy, 2) {
            repn(cur, 2) {
                if(sn && cur>ns[i]) continue;
                if ((cur==0 && i-c>=k) || cur==1) {
                    int j=c+max(0, i-c-k);
                    if(sy && cur>ys[j]) continue;
                    f[i+1][c+cur][sn && cur==ns[i]][sy && cur==ys[j]]+=f[i][c][sn][sy];
                } else {
                    f[i+1][c+cur][sn && cur==ns[i]][sy]+=f[i][c][sn][sy];
                }
            }
        }
        LL ans=0;
        rep(c, 0, sz(ns)) repn(sn, 2) repn(sy, 2) {
            ans+=f[sz(ns)][c][sn][sy];
        }
        return ans;
    }
public:
    long long getCount(long long x, long long y, int k) {
        LL cur=1, ans=0;
        while(cur<=x) {
            ans+=solve(cur, min(cur*2-1, x), y, k);
            cur*=2;
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 2LL; long long Arg1 = 1LL; int Arg2 = 1; long long Arg3 = 2LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { long long Arg0 = 6LL; long long Arg1 = 2LL; int Arg2 = 1; long long Arg3 = 4LL; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { long long Arg0 = 6LL; long long Arg1 = 1LL; int Arg2 = 3; long long Arg3 = 6LL; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { long long Arg0 = 31LL; long long Arg1 = 6LL; int Arg2 = 2; long long Arg3 = 20LL; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { long long Arg0 = 413LL; long long Arg1 = 34LL; int Arg2 = 2; long long Arg3 = 130LL; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { long long Arg0 = 1000000000LL; long long Arg1 = 1000000000LL; int Arg2 = 5; long long Arg3 = 1000000000LL; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_6() { long long Arg0 = 549755813602LL; long long Arg1 = 8369864093LL; int Arg2 = 5; long long Arg3 = 178429547459LL; verify_case(6, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    PrimeStrings ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
