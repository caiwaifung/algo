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

template<size_t N, size_t E, class T, T INFI> class Dinic {
	struct Edge {
		int y;  T w;
		Edge *next, *oppo;
	} edges[E*2];
	Edge *g[N], *ce[N];
	int e_cnt, n, src, dst;

	int d[N], q[N];
	bool build() {
		memset(d, 0, sizeof(d)); d[q[1]=src]=1;
		for(int ss=0, tt=1; ss<tt; ) {
			int x=q[++ss];
			for(Edge *e=ce[x]=g[x]; e; e=e->next)
				if(e->w>0 && d[e->y]==0) d[q[++tt]=e->y]=d[x]+1;
		}
		return d[dst]>0;
	}
	T find(int x, T rest) {
		if(x==dst) return rest;
		T ans=0;
		for(Edge *&e=ce[x]; e; e=e->next)
			if(e->w>0 && d[e->y]>d[x]) {
				T cur=find(e->y, min(e->w,rest));
				e->w-=cur; e->oppo->w+=cur;
				ans+=cur; rest-=cur;
				if(rest==0) break;
			}
		return ans;
	}
public:
	Dinic() { init(); }
	int s() { return src; }
	int t() { return dst; }
	void init() {
		memset(g, 0, sizeof(g)); e_cnt=0;
		n=2, src=1, dst=2;
	}
	int newNode() { return ++n; }
	void addEdge(int x, int y, T w1, T w2) {
		Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
		e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
		e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
	}
	T compute() {
		T ans=0; while(build()) ans+=find(src, INFI); return ans;
	}
	T getFlow(int x, int y) {
		for(Edge *e=g[x]; e; e=e->next)
			if(e->y==y)
				return e->oppo->w;
		return 0;
	}
};

// ------------------------ template ends here ------------------------ //

Dinic<1010, 2010, int, 1<<30> dinic;

class Singing {
public:
	int solve(int N, int low, int high, vector <int> pitch) {
		static int id[1010];
		dinic.init();
		forint(i, 1, N) id[i]=dinic.newNode();
		forint(i, 1, N) {
			if(i<low)  dinic.addEdge(dinic.s(), id[i], 1<<20, 0);
			if(i>high) dinic.addEdge(id[i], dinic.t(), 1<<20, 0);
		}
		int m=(int)pitch.size();
		forint(i, 1, m-1) {
			int x=pitch[_ i-1], y=pitch[_ i];
			dinic.addEdge(id[x], id[y], 1, 1);
		}
		int ans=dinic.compute();

		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 2; int Arr3[] = {1,2,3,2,1,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(0, Arg4, solve(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 3; int Arg2 = 7; int Arr3[] = {4,4,5,5,6,5,3,6}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(1, Arg4, solve(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 2; int Arg2 = 5; int Arr3[] = {5,3,1,6,4,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(2, Arg4, solve(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 4; int Arg2 = 5; int Arr3[] = {1,4,3,5,2,5,7,5,9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; verify_case(3, Arg4, solve(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 100; int Arg1 = 20; int Arg2 = 80; int Arr3[] = {2,27,3,53,53,52,52,60,85,89,100,53,60,2,3,53,100,89,40,42,2,53,2,85}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 5; verify_case(4, Arg4, solve(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Singing ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
