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

class TheGridDivOne {
	vector<int> ax, ay;
	int n;

	bool ok(int x1, int y1, int x2, int y2) {
		if(x1>x2) swap(x1,x2);
		if(y1>y2) swap(y1,y2);
		forn(i, n)
			if(ax[i]>=x1 && ax[i]<=x2 && ay[i]>=y1 && ay[i]<=y2)
				return false;
		return true;
	}

	vector<int> px, py;
	int m;
	void pre() {
		set<PII> s;
		s.insert(MP(0, 0));
		forn(i, n) {
			forint(dx, -1, 1) forint(dy, -1, 1) {
				int x=ax[i]+dx, y=ay[i]+dy;
				if(ok(x, y, x, y)) s.insert(MP(x, y));
			}
		}
		px.clear(), py.clear();
		for(set<PII>::iterator it=s.begin(); it!=s.end(); ++it)
			px.PB(it->fi), py.PB(it->se);
		m=px.size();
	}

	LL g[555][555];
public:
	int find(vector <int> x, vector <int> y, int k) {
		n=x.size(); ax=x, ay=y;
		pre();

		fillchar(g, 50);
		forn(i, m) forn(j, m)
			if(ok(px[i],py[i], px[j],py[j]))
				g[i][j]=(LL)abs(px[i]-px[j])+(LL)abs(py[i]-py[j]);
		forn(k, m) forn(i, m) forn(j, m)
			g[i][j]=min(g[i][j], g[i][k]+g[k][j]);

		int st=0;
		while(px[st]!=0 || py[st]!=0) ++st;

		LL ans=0;
		forn(i, m) {
			LL d=g[st][i];
			LL r=k-d;
			if(r>=0) {
				ans=max(ans, (LL)px[i]);
				if(ok(px[i],py[i], (int)(px[i]+r), py[i]))
					ans=max(ans, px[i]+r);
			}
		}
		cout<<ans<<endl;
		
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,-1,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {-1, 0, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, -1, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; int Arg3 = 0; verify_case(1, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; int Arg3 = 1000; verify_case(2, Arg3, find(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1,0,0,-1,-1,-2,-2,-3,-3,-4,-4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,-1,1,-2,2,-3,3,-4,4,-5,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 47; int Arg3 = 31; verify_case(3, Arg3, find(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TheGridDivOne ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
