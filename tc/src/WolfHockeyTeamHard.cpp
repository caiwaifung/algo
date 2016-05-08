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

const LL MOD=LL(1e9)+7;

class WolfHockeyTeamHard {
    VL fac, inv, inv_fac;
    void pre() {
        const int n=1501000;
        inv.resize(n+1);
        auto pow=[](LL a, LL b, LL m) {
            LL c=1;
            for(; b>0; b>>=1, a=a*a%m)
                if(b&1) c=c*a%m;
            return c;
        };
        inv[0]=0; rep(i, 1, n) inv[i]=pow(i, MOD-2, MOD);

        fac.resize(n+1);
        inv_fac.resize(n+1);
        fac[0]=inv_fac[0]=1;
        rep(i, 1, n) {
            fac[i]=fac[i-1]*i%MOD;
            inv_fac[i]=inv_fac[i-1]*inv[i]%MOD;
        }
    }
    LL binom(int n, int r) {
        return fac[n]*inv_fac[r]%MOD*inv_fac[n-r]%MOD;
    }

public:
    LL f(int n, int m) {
        LL c=(m+1)*inv[n+m+1]%MOD;
        return binom(2*n+m, n)*c%MOD;
    }
    int count(int N, int K) {
        pre();
        LL ans=0;
        rep(M, max(N, K+1), 2*N-1) {
            (ans+=f(M-N, 2*N-M-1))%=MOD;
            if(M>N) (ans+=f(M-N-1, 2*N-M+1))%=MOD;
        }
        (ans*=2)%=MOD;
        (ans*=fac[N])%=MOD;
        return (int)(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 12; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 5; int Arg2 = 1104; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 78; int Arg2 = 68021677; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2100; int Arg1 = 4199; int Arg2 = 0; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 81019; int Arg1 = 114514; int Arg2 = 793441075; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    WolfHockeyTeamHard ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
