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
const int N=100010;

class TreeWalker {
    struct T {
        LL u, d, c; int sz;
    };
    vector<VI> es;
    int n; LL ans;
    VL m2;
    T solve(int x, int fa) {
        T r; r.u=1, r.d=1, r.c=1, r.sz=1;
        for(int y: es[x]) if(y!=fa) {
            T cur=solve(y, x);
            r.sz+=cur.sz;
            (ans+=cur.d*r.u%MOD*m2[n-r.sz])%=MOD;
            (ans+=cur.u*r.d%MOD*m2[n-r.sz])%=MOD;
            r.u=(r.u*cur.c+cur.u*r.c)%MOD;
            r.d=(r.d*cur.c+cur.d*r.c)%MOD;
            r.c=(r.c*cur.c)%MOD;
        }
        r.u=(r.u)%MOD;
        r.d=(r.d)%MOD;
        r.c=(r.c*2)%MOD;
        //printf("x=%d u=%lld d=%lld c=%lld\n",x,r.u,r.d,r.c);
        return r;
    }
public:
    int calc(int N0, int A0, int B, int C, int M0) {
        m2.resize(N); m2[0]=1; rep(i, 1, m2.size()-1) m2[i]=m2[i-1]*2%MOD;
        n=N0; VI A(n-1);
        A[0]=A0;
        rep(i, 1, n-2) A[i]=int((LL(B)*LL(A[i-1])+C)%M0);
        es.clear(); es.resize(n+1);
        rep(i, 1, n-1) {
            int x=A[i-1]%i+1, y=i+1;
            es[x].pb(y), es[y].pb(x);
        }

        ans=0;
        solve(1, 0);
        return (int)(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 1000; int Arg5 = 34; verify_case(0, Arg5, calc(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 13824; verify_case(1, Arg5, calc(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 16; int Arg1 = 15; int Arg2 = 1; int Arg3 = 1; int Arg4 = 16; int Arg5 = 917506; verify_case(2, Arg5, calc(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 385498676; int Arg2 = 349131547; int Arg3 = 115776323; int Arg4 = 614879544; int Arg5 = 245566366; verify_case(3, Arg5, calc(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 100000; int Arg1 = 111222333; int Arg2 = 444555666; int Arg3 = 777888999; int Arg4 = 123456789; int Arg5 = 119729770; verify_case(4, Arg5, calc(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    TreeWalker ___test;
    ___test.run_test(-1);
    //___test.run_test(0);
    return 0;
}
// END CUT HERE
