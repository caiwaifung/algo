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

const LL MOD=LL(1e9)+7;

class TheCowDivOne {
public:
	LL N;
	LL pow(LL a, LL b) {
		LL x=1;
		for(; b>0; b>>=1, a=a*a%MOD)
			if(b&1) x=x*a%MOD;
		return x;
	}
	LL gcd(LL a, LL b) {
		return b==0?a:gcd(b,a%b);
	}
	LL inv(LL x) {
		return pow(x, MOD-2);
	}
	map<PII, LL> fv;
	LL F(LL m, LL c, LL p) {
		LL g=gcd(c, p);
		if(m==1) return N*g/p;
	//cout<<m<<" "<<c<<" "<<p<<endl;
		PII cur=MP(int(m),int(p));
		if(c==1 && fv.find(cur)!=fv.end())
			return fv[cur];
		LL x=F(m-1, 1, g);
		LL y=F(m-1, c+1, p);
		LL ans=x*(N*g/p)-y*(m-1);
		ans=(ans%MOD+MOD)%MOD;
		if(c==1) fv[cur]=ans;
		return ans;
	}
	int find(int N, int K) {
		fv.clear();
		this->N=N;
		LL ans=F(K, 1, N), tmp=1;
		forint(i, 1, K) (tmp*=i)%=MOD;
		(ans*=inv(tmp))%=MOD;
		//printf("%lu\n",fv.size());
		LL sz=fv.size()*sizeof(*fv.begin());
		//printf("%.3lf\n", sz/1024./1024.);
		//printf("%lu\n",fv.size());
		return (int)ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 7; int Arg1 = 4; int Arg2 = 5; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 58; int Arg1 = 4; int Arg2 = 7322; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 47; int Arg2 = 219736903; verify_case(3, Arg2, find(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000000000; int Arg1 = 1000; int Arg2 = 666683069; verify_case(4, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TheCowDivOne ___test;
	//___test.run_test(1);return 0;
	___test.run_test(-1);
	scanf("%*d");
	return 0;
}
// END CUT HERE
