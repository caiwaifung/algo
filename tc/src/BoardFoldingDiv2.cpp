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

#define _ (size_t)
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


// ------------------------ template ends here ------------------------ //
class BoardFoldingDiv2 {
public:
	LL h(int x[], int k) {
		LL p=0;
		forn(i, k) p=p*2+x[i];
		return p;
	}
	int paper[55][55];
	int n, m;

	LL a[55];
	bool same(int i1, int j1, int i2, int j2) {
		while(i1<=j1 && i2<=j2) {
			if(a[i1]!=a[j2]) return false;
			++i1, --j2;
		}
		return true;
	}

	int go() {
		forn(i, n) a[i+1]=h(paper[i], m);
		//forn(i, n) printf("%d\n", (int)a[i]);

		static bool ok[55][55];
		fillchar(ok, false);
		ok[1][n]=true;
		//printf("@@ %d\n", same(1,1,2,2));
		forint(i, 1, n) forintdown(j, n, i)
			if(ok[i][j]) {
				forint(k, i, j) {
					int len=k-i+1;
					if(k+len>j) continue;
					if(same(i,k, k+1, k+len))
						ok[k+1][j]=true;
				}
				forint(k, i, j) {
					int len=j-k+1;
					if(k-len<i) continue;
					if(same(k,j, k-len,k-1))
						ok[i][k-1]=true;
				}
			}
		int ans=0;
		forint(i, 1, n) forint(j, i, n) if(ok[i][j]) ++ans;
		return ans;
	}

	int howMany(vector <string> p) {
		n=p.size(), m=p[0].size();
		forn(i, n) forn(j, m) paper[i][j]=int(p[_ i][_ j]-'0');
		int ans1=go();
		static int tmp[55][55];
		forn(i, n) forn(j, m) tmp[j][i]=paper[i][j];
		swap(n, m);
		forn(i, n) forn(j, m) paper[i][j]=tmp[i][j];
		int ans2=go();
		printf("1=%d\n",ans1);
		printf("2=%d\n",ans2);
		return int(ans1*ans2);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"10",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, howMany(Arg0)); }
	void test_case_1() { string Arr0[] = {"1111111",
 "1111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 84; verify_case(1, Arg1, howMany(Arg0)); }
	void test_case_2() { string Arr0[] = {"0110",
 "1001",
 "1001",
 "0110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, howMany(Arg0)); }
	void test_case_3() { string Arr0[] = {"0",
 "0",
 "0",
 "1",
 "0",
 "0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(3, Arg1, howMany(Arg0)); }
	void test_case_4() { string Arr0[] = {"000",
 "010",
 "000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, howMany(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BoardFoldingDiv2 ___test;
	/*
	___test.run_test(1);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
