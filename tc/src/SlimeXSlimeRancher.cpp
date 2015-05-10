#include <algorithm>
#include <iostream>
#include <numeric>
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

VI parse_ints(VS ss) {
	istringstream in(accumulate(all(ss), string("")));
	VI xs; int x;
	while(in>>x) xs.push_back(x);
	return xs;
}

VI discretize(VI &a) {
	VI t=a; sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	for(size_t i=0; i<t.size(); i++)
		t[i]=lower_bound(a.begin(), a.end(), t[i])-a.begin()+1;
	return t;
}

class SlimeXSlimeRancher {
	LL go(VPI &s, int i, int j, VI &ax, VI &ay) {
		LL ans=0;
		forn(k, s.size()) {
			int x=s[k].fi, y=s[k].se;
			if(x<=i && y<=j)
				ans+=ax[i-1]-ax[x-1]+ay[j-1]-ay[y-1];
		}
		return ans;
	}
public:
	long long train(vector <string> _ax, vector <string> _ay, vector <string> _az) {
		VI ax, ay, az;
		VI xs=discretize(ax=parse_ints(_ax)); int mx=ax.size();
		VI ys=discretize(ay=parse_ints(_ay)); int my=ay.size();
		VI zs=discretize(az=parse_ints(_az)); int mz=az.size();
		int n=xs.size();
		VPI sx[155], sy[155], sz[155];
		forn(i, n) {
			int x=xs[i], y=ys[i], z=zs[i];
			sx[x].PB(MP(y, z));
			sy[y].PB(MP(x, z));
			sz[z].PB(MP(x, y));
		}
		static LL f[155][155][155];
		fillchar(f, 55);
		f[1][1][1]=0;
		forint(i, 1, mx) forint(j, 1, my) forint(k, 1, mz) {
		//printf("%d,%d,%d: %lld\n",i,j,k,f[i][j][k]);
			setmin(f[i+1][j][k], f[i][j][k]+go(sx[i+1], j, k, ay, az));
			setmin(f[i][j+1][k], f[i][j][k]+go(sy[j+1], i, k, ax, az));
			setmin(f[i][j][k+1], f[i][j][k]+go(sz[k+1], i, j, ax, ay));
		}
		LL ans=f[mx][my][mz];

		return (ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 6 2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1 3 5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"5 4 3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 5LL; verify_case(0, Arg3, train(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"3 2 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"6 5 4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"9 8 7"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, train(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"1 2", "3 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"12 3 ", "4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 2 ", "34"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 36LL; verify_case(2, Arg3, train(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"1 1 1 1000000000 1000000000 1000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1000000000 1000000000 1000000000 1 1 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1 1 1 2 2 2"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 2999999997LL; verify_case(3, Arg3, train(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SlimeXSlimeRancher ___test;
	//___test.run_test(3); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
