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
const int MAXN=3030;
const LL MOD=LL(1e9)+7;

LL binom[MAXN][MAXN];
int g[MAXN], g_lnk[MAXN*2], g_nxt[MAXN*2];
int n;

int pa[MAXN], pn;
int pre[MAXN];
void dfs(int x, int fa) {
	pre[x]=fa;
	for(int e=g[x]; e; e=g_nxt[e])
		if(g_lnk[e]!=fa)
			dfs(g_lnk[e], x);
}
void find_path(int s1, int s2) {
	dfs(s1, 0);
	pn=0;
	for(int x=s2; x!=0; x=pre[x])
		pa[++pn]=x;
	reverse(pa+1, pa+pn+1);
}

bool vis[MAXN];
LL u[MAXN]; int sz[MAXN];
int sum_sz[MAXN];
void go(int x) {
	u[x]=1, sz[x]=0;
	for(int e=g[x], y; e; e=g_nxt[e])
		if(!vis[y=g_lnk[e]]) {
			vis[y]=true;
			go(y); u[x]=(u[x]*u[y]%MOD*binom[sz[x]+sz[y]][sz[y]])%MOD;
			sz[x]+=sz[y];
		}
	sz[x]++;
}

class TwoEntrances {
public:
	void pre() {
		fillchar(binom, 0);
		forn(i, MAXN) binom[i][0]=binom[i][i]=1;
		forn(i, MAXN) forint(j, 1, i-1) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;
	}
	int count(vector <int> a, vector <int> b, int s1, int s2) {
		pre();
		fillchar(g, 0);
		n=(int)a.size()+1;
		forn(i, n-1) {
			int x=a[_ i], y=b[_ i]; ++x, ++y;
			static int e=0;
			g_lnk[++e]=y, g_nxt[e]=g[x], g[x]=e;
			g_lnk[++e]=x, g_nxt[e]=g[y], g[y]=e;
		}
		++s1, ++s2;

		find_path(s1, s2);
		
		fillchar(vis, false);
		forint(i, 1, pn) vis[pa[i]]=true;
		forint(i, 1, pn) go(pa[i]);
		sum_sz[0]=0;
		forint(i, 1, pn) sum_sz[i]=sum_sz[i-1]+sz[pa[i]];

		static LL f[MAXN][MAXN];
		fillchar(f, 0);
		forint(i, 1, pn) f[i][i]=u[pa[i]];
		forintdown(i, pn, 1) forint(j, i, pn) {
			LL tmp;
			if(i>1) {
				tmp=f[i][j];
				(tmp*=u[pa[i-1]])%=MOD;
				int sz1=sum_sz[j]-sum_sz[i-1], sz2=sz[pa[i-1]]-1;
				(tmp*=binom[sz1+sz2][sz1])%=MOD;
				(f[i-1][j]+=tmp)%=MOD;
			}
			if(j<n) {
				tmp=f[i][j];
				(tmp*=u[pa[j+1]])%=MOD;
				int sz1=sum_sz[j]-sum_sz[i-1], sz2=sz[pa[j+1]]-1;
				(tmp*=binom[sz1+sz2][sz1])%=MOD;
				(f[i][j+1]+=tmp)%=MOD;
			}
		}
		LL ans=f[1][pn];
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; int Arg3 = 1; int Arg4 = 4; verify_case(0, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; int Arg3 = 2; int Arg4 = 9; verify_case(1, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0, 1, 1, 3, 3, 3, 6, 7, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 9; int Arg4 = 16000; verify_case(2, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0, 0, 1, 2, 3, 1, 2, 0, 6, 5, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10, 11, 12}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 6; int Arg4 = 310464; verify_case(3, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 0; int Arg4 = 2; verify_case(4, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TwoEntrances ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
