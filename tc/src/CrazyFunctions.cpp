#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
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
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const LL MOD=LL(1e9)+7;

class CrazyFunctions {
public:
    int count(int n, int k) {
        static int binom[5050][5050];
        rep(i, 0, n) binom[i][0]=binom[i][i]=1;
        rep(i, 1, n) rep(j, 1, i-1) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;

        static LL f[5050], g[5050];
        f[0]=g[0]=1;
        rep(i, 1, n) {
            f[i]=i*g[i-1]%MOD;
            g[i]=0;
            rep(j, 1, i) (g[i]+=binom[i-1][j-1]*g[i-j]%MOD*f[j])%=MOD;
        }
        //rep(i, 1, n) printf("f[%d]=%lld g[%d]=%lld\n",i,f[i],i,g[i]);

        LL ans=binom[n][k]; rep(i, 1, k) (ans*=i)%=MOD;
        n-=k;
        static LL h[5050];
        h[0]=1;
        rep(i, 1, n) {
            h[i]=0;
            rep(j, 1, i) (h[i]+=binom[i-1][j-1]*h[i-j]%MOD*f[j]%MOD*k)%=MOD;
        }
        (ans*=h[n])%=MOD;

        return (int)(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 9; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 6; verify_case(4, Arg2, count(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 900; verify_case(5, Arg2, count(Arg0, Arg1)); }
	void test_case_6() { int Arg0 = 5000; int Arg1 = 5000; int Arg2 = 541108809; verify_case(6, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    CrazyFunctions ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
