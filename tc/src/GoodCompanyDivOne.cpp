#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
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
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VPII;

const int MAXN=33;
const int MAXC=33;

struct Net {
	int g[MAXN*3][MAXN*3], c[MAXN*3][MAXN*3];
	int n;
	Net(int n) : n(n) {
		fillchar(g, 0); fillchar(c, 0);
	}
	void add(int i, int j, int t) {
		g[i][j]=1;
		c[i][j]=t, c[j][i]=-t;
	}
	int que[MAXN*3], dst[MAXN*3], pre[MAXN*3];
	bool ins[MAXN*3];
	int compute(int st, int en) {
		int ans=0;
		while(1) {
			int ss=0, tt=1; que[1]=st;
			fillchar(dst, 55); int maxval=dst[0];
			dst[st]=0;
			fillchar(ins, false); ins[st]=true;
			while(ss!=tt) {
				if(++ss==MAXN*3) ss=1;
				int x=que[ss]; ins[x]=false;
				forint(y, 1, n) if(g[x][y]>0 && dst[x]+c[x][y]<dst[y]) {
					dst[y]=dst[x]+c[x][y];
					pre[y]=x;
					if(!ins[y]) {
						ins[y]=true;
						if(++tt==MAXN*3) tt=1;
						que[tt]=y;
					}
				}
			}
			if(dst[en]==maxval) break;
			ans+=dst[en];
			for(int x=pre[en], y=en; y!=st; y=x, x=pre[x]) {
				--g[x][y];
				++g[y][x];
			}
		}
		return ans;
	}
};

class GoodCompanyDivOne {
public:
	int lc[MAXN], rc[MAXN], sons[MAXN];
	int n, cn;
	int cst[MAXC];
	int g[MAXN][MAXC];
	void dfs(int x) {
		int ans[MAXC];
		for(int y=lc[x]; y; y=rc[y])
			dfs(y);
		forint(c, 1, cn) {
			Net net(sons[x]+cn+2);
			for(int y=lc[x], i=1; y; y=rc[y], ++i) {
				net.add(sons[x]+cn+1, i, 0);
				forint(cy, 1, cn) if (cy!=c) {
					net.add(i, sons[x]+cy, g[y][cy]);
				}
			}
			forint(cy, 1, cn) net.add(sons[x]+cy, sons[x]+cn+2, 0);
			int cur=net.compute(sons[x]+cn+1, sons[x]+cn+2);
			ans[c]=cur+cst[c];
		}
		fillchar(g[x], 55);
		forint(i, 1, cn) forint(j, 1, cn) if(i!=j) {
			g[x][i]=min(g[x][i], ans[i]+cst[j]);
			g[x][j]=min(g[x][j], ans[i]+cst[j]);
		}
	}
	int minimumCost(vector <int> superior, vector <int> training) {
		n=superior.size();
		fillchar(lc, 0);
		fillchar(sons, 0);
		forint(x, 2, n) {
			int y=superior[x-1]+1;
			rc[x]=lc[y], lc[y]=x;
			++sons[y];
		}
		cn=training.size();
		forint(i, 1, cn) cst[i]=training[i-1];
		forint(x, 1, n) if(1+sons[x]>cn) return -1;
		dfs(1);
		int ans=1<<30;
		//forint(x, 1, n) forint(i, 1, cn) printf("g[%d,%d]=%d\n",x,i,g[x][i]);
		forint(i, 1, cn) ans=min(ans, g[1][i]);
		
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minimumCost(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-1, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(1, Arg2, minimumCost(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, minimumCost(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-1, 0, 0, 2, 2, 2, 1, 1, 6, 0, 5, 4, 11, 10, 3, 6, 11, 7, 0, 2, 13, 14, 2, 10, 9, 11, 22, 10, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 2, 6, 6, 8, 3, 3, 1, 1, 5, 8, 6, 8, 2, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 71; verify_case(3, Arg2, minimumCost(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	GoodCompanyDivOne ___test;
	//___test.run_test(0); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
