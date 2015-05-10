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


namespace MathBasic {
	const LL MOD=LL(1e9)+7;
	LL pow(LL a, LL b) {
		LL t=1;
		for(; b>0; b>>=1, a=a*a%MOD)
			if(b&1) t=t*a%MOD;
		return t;
	}
	LL inv(LL a) {
		return pow(a, MOD-2);
	}
	LL binom(LL n, LL k) {
		LL u=1, v=1;
		forint(i, 1, k) {
			u=u*(n-i+1)%MOD;
			v=v*i%MOD;
		}
		return u*inv(v)%MOD;
	}
};
using namespace MathBasic;

// ------------------------ template ends here ------------------------ //

LL mem_f[26][26][55];
LL mem_g[26][26][26][55];

class CubeBuilding {
	int N;

	LL g(int x, int y, int c1, int c2) {
		if(x==0) {
			if(y==0) {
				if(c1==0 && c2==0) return 1;
				return 0;
			}
			return g(y, 0, c1, c2);
		}
		LL &ans=mem_g[x][y][c1][c2];
		if(ans>=0) return ans;
		ans=0;
		// put nothing
		(ans+=g(x-1, y, c1, c2)) %=MOD;
		// put c1
		if(c1>0)
			(ans+=g(x-1, y+1, c1-1, c2)) %=MOD;
		// put c2
		if(c2>0 && y>0)
			(ans+=g(x-1, y+1, c1, c2-1)) %=MOD;
		return ans;
	}

	LL f(int n, int c1, int c2) {
		if(n==0) {
			if(c1==0 && c2==0) return 1;
			return 0;
		}
		LL &ans=mem_f[n][c1][c2];
		if(ans>=0) return ans;
		ans=0;
		forint(p, 0, c1) forint(q, 0, c2)
			(ans+=f(n-1, c1-p, c2-q)*g(N, 0, p, q)) %=MOD;
		return ans;
	}
public:
	LL solve(int c1, int c2, int N) {
		this->N=N;
		return f(N, c1, c2);
	}
	LL solve(int R, int G, int B, int N) {
		LL ans=solve(R, G+B, N);
		ans=ans*binom(G+B, B)%MOD;
		return ans;
	}
	int getCount(int R, int G, int B, int N) {
		fillchar(mem_f, 0xff);
		fillchar(mem_g, 0xff);
		LL ans=0;
		(ans+=solve(R, G, B, N)) %=MOD;
		(ans+=solve(G, B, R, N)) %=MOD;
		(ans+=solve(B, R, G, N)) %=MOD;
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 1; int Arg3 = 2; int Arg4 = 4; verify_case(0, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 2; int Arg3 = 1; int Arg4 = 0; verify_case(1, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 3; int Arg4 = 162; verify_case(2, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 10; int Arg3 = 12; int Arg4 = 372185933; verify_case(3, Arg4, getCount(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	CubeBuilding ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
