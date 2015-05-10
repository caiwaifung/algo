#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define PB push_back
#define MP make_pair
#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) for(int i=0; i<(int)(n); ++i)
#define forndown(i, n) for(int i=(int)(n)-1; i>=0; --i)
#define fillchar(a, x) memset(a, x, sizeof(a))
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }

class TriangleXor {
public:
	int theArea(int W) {
		double ans=0;
		int cnt=10000;
		forn(cnti, cnt) {
			double y=(double)(cnti+0.1)/(double)cnt;
			vector<double> le, ri;
			forint(i, 0, W) {
				double l=(double)i*y;
				double r=(double)W-(double)(W-i)*y;
				le.PB(l), ri.PB(r);
				//printf("i=%d l=%.5lf r=%.5lf\n",i,l,r);
			}
			double cur=0.;
			int c=0;
			for(int i=0, j=0; i<(int)le.size() || j<(int)ri.size(); ) {
				double nxt; bool sl;
				if(i<(int)le.size()) nxt=le[i], sl=true;
					else nxt=ri[j], sl=false;
				if(j<(int)ri.size() && ri[j]<nxt)
					nxt=ri[j], sl=false;
				if(c%2!=0) ans+=(nxt-cur);
				//printf("c=%d cur=%.9lf nxt=%.8lf p=%.8lf\n",c,cur,nxt,nxt-cur);
				cur=nxt;
				if(sl) ++i, ++c;
					else ++j, --c;
			}
		}
		ans/=(double)cnt;
		//printf("ans=%.9lf\n", ans);
		int ret=(int)(ans+1E-4);
		return ret;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 0; verify_case(0, Arg1, theArea(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; verify_case(1, Arg1, theArea(Arg0)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 1; verify_case(2, Arg1, theArea(Arg0)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 2; verify_case(3, Arg1, theArea(Arg0)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 2; verify_case(4, Arg1, theArea(Arg0)); }
	void test_case_5() { int Arg0 = 12345; int Arg1 = 4629; verify_case(5, Arg1, theArea(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	TriangleXor ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
