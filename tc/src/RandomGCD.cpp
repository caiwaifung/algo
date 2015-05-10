#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const int MOD=int(1e9)+7;
const int MAXN=100010;

class RandomGCD {
public:
	int cal(int x, int le, int ri, int n) {
		int c=ri/x-(le-1)/x;
		int ans=1;
		for(; n>0; n>>=1, c=LL(c)*LL(c)%MOD)
			if(n&1) ans=LL(ans)*LL(c)%MOD;
		return ans;
	}
	int countTuples(int N, int K, int low, int high) {
		int n=high-low;
		int ans;
		if(low<=n) {
			static int f[MAXN*2];
			forint(i, 1, high) f[i]=cal(i, low, high, N);
			forintdown(i, high, 1) {
				for(int j=i*2; j<=high; j+=i)
					(f[i]-=f[j]) %=MOD;
			}
			if(K<=high) ans=f[K];
			else ans=0;
		} else {
			static int f[MAXN];
			forint(i, 1, n) f[i]=cal(i, low, high, N);
			forintdown(i, n, 1) {
				for(int j=i*2; j<=n; j+=i)
					(f[i]-=f[j]) %=MOD;
				int j=low/i*i;
				if(j<low) j+=i;
				while(j<=high) --f[i], j+=i;
			}
			if(K<=high && K>=low) ans=1;
			else if(K<=n && K>=1) ans=f[K];
			else ans=0;
		}
		ans=(ans%MOD+MOD)%MOD;
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 4; int Arg4 = 3; verify_case(0, Arg4, countTuples(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 100; int Arg2 = 2; int Arg3 = 4; int Arg4 = 0; verify_case(1, Arg4, countTuples(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 5; int Arg3 = 5; int Arg4 = 1; verify_case(2, Arg4, countTuples(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 73824; int Arg1 = 17347; int Arg2 = 9293482; int Arg3 = 9313482; int Arg4 = 0; verify_case(3, Arg4, countTuples(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 222; int Arg1 = 222; int Arg2 = 222; int Arg3 = 22222; int Arg4 = 339886855; verify_case(4, Arg4, countTuples(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	RandomGCD ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
