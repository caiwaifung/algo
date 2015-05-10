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
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

class RectangleArea {
	struct Node {
		Node *fa;
		Node() : fa(NULL) {}
		Node *get() {
			return fa==NULL ? this : fa=fa->get();
		}
	};
public:
	int minimumQueries(vector <string> known) {
		int n=known.size();
		int m=known[0].size();
		vector<Node*> r(n), c(m);
		forn(i, n) r[i]=new Node();
		forn(i, m) c[i]=new Node();
		forn(i, n) forn(j, m)
			if(known[i][j]=='Y') {
				Node *x=r[i]->get();
				Node *y=c[j]->get();
				if(x!=y) x->fa=y;
			}
		int cnt=0;
		forn(i, n) if(r[i]->fa==NULL) ++cnt;
		forn(i, m) if(c[i]->fa==NULL) ++cnt;
		return cnt-1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NN",
 "NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minimumQueries(Arg0)); }
	void test_case_1() { string Arr0[] = {"YNY",
 "NYN",
 "YNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minimumQueries(Arg0)); }
	void test_case_2() { string Arr0[] = {"YY",
 "YY",
 "YY",
 "YY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, minimumQueries(Arg0)); }
	void test_case_3() { string Arr0[] = {"NNNNNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, minimumQueries(Arg0)); }
	void test_case_4() { string Arr0[] = {"NNYYYNN",
 "NNNNNYN",
 "YYNNNNY",
 "NNNYNNN",
 "YYNNNNY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(4, Arg1, minimumQueries(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	RectangleArea ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
