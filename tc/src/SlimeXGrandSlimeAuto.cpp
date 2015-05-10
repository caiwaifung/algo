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

template<size_t N, size_t E, class T> class MinCostFlow {
	struct Edge {
		int y; T c, w;
		Edge *next, *oppo;
	} edges[E*2];
	Edge *g[N];
	int e_cnt, n, src, dst;

	bool inside[N];
	Edge *pre[N];
	int q[N];
	T d[N];
public:
	MinCostFlow() { init(); }
	int s() { return src; }
	int t() { return dst; }
	void init() {
		memset(g, 0, sizeof(g)); e_cnt=0;
		n=2, src=1, dst=2;
	}
	int newNode() { return ++n; }
	void addEdge(int x, int y, T w, T c) {
	//printf("add %d %d %d %d\n",x,y,w,c);
		Edge *e1=&edges[e_cnt++], *e2=&edges[e_cnt++];
		e1->y=y, e1->c=+c, e1->w=w, e1->oppo=e2, e1->next=g[x], g[x]=e1;
		e2->y=x, e2->c=-c, e2->w=0, e2->oppo=e1, e2->next=g[y], g[y]=e2;
	}
	pair<T,T> compute() {
		T flow=0, cost=0;
		while(1) {
			memset(pre, 0, sizeof(pre));
			memset(d, 100, sizeof(d));
			memset(inside, false, sizeof(inside));
			int ss=0, tt=1;
			q[1]=src, d[src]=0, inside[src]=true;
			while(ss!=tt) {
				if(++ss==N) ss=1;
				int x=q[ss]; inside[x]=false;
				for(Edge *e=g[x]; e; e=e->next)
					if(e->w>0 && d[x]+e->c<d[e->y]) {
						int y=e->y;
						d[y]=d[x]+e->c;
						pre[y]=e;
						if(!inside[y]) {
							inside[y]=true;
							if(++tt==N) tt=1;
							q[tt]=y;
						}
					}
			}
			if(pre[dst]==NULL)
				break;
			T cur=pre[dst]->w;
			for(int y=dst, x; y!=src; y=x) {
				cur=min(cur, pre[y]->w);
				x=pre[y]->oppo->y;
			}
			flow+=cur;
			cost+=cur*d[dst];
			for(int y=dst, x; y!=src; y=x) {
				pre[y]->w-=cur;
				pre[y]->oppo->w+=cur;
				x=pre[y]->oppo->y;
			}
		}
		return make_pair(flow, cost);
	}
};

class SlimeXGrandSlimeAuto {
	int parse(char c) {
		if(c=='.') return 1<<28;
		if(c>='0' && c<='9') return int(c-'0'+1);
		if(c>='a' && c<='z') return int(c-'a'+11);
		if(c>='A' && c<='Z') return int(c-'A'+37);
		return 0;
	}
public:
	int travel(vector <int> cars, vector <int> districts, vector <string> roads, int inverseWalkSpeed, int inverseDriveSpeed) {
		int n=roads.size();
		int g[55][55];
		fillchar(g, 500);
		forn(i, n) forn(j, n) g[i][j]=parse(roads[i][j]);
		forn(i, n) g[i][i]=0;
		forn(k, n) forn(i, n) forn(j, n) setmin(g[i][j], g[i][k]+g[k][j]);

		MinCostFlow<55*2, 55*2+55*55, int> net;
		VI di(districts.size()); int dci;
		VI ci(cars.size());

		forn(i, di.size()) di[i]=net.newNode();
		forn(i, ci.size()) ci[i]=net.newNode();
		dci=net.newNode();

		forn(i, di.size()) net.addEdge(net.s(), di[i], 1, 0);
		forn(i, ci.size()) net.addEdge(ci[i], net.t(), 1, 0);
		net.addEdge(dci, net.t(), 9999, 0);
		forn(i, di.size()) {
			int y=districts[i], x=(i>0?districts[i-1]:0);
			forn(j, ci.size()) {
				int z=cars[j];
				net.addEdge(di[i], ci[j], 1, g[x][z]*inverseWalkSpeed+g[z][y]*inverseDriveSpeed);
			}
			net.addEdge(di[i], dci, 1, g[x][y]*inverseWalkSpeed);
		}
		int ans=net.compute().se;
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
"..0.",
"...1",
"0..2",
".12."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; int Arg4 = 1; int Arg5 = 36; verify_case(0, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".A.",
"A.B",
".B."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 1; int Arg5 = 262; verify_case(1, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arr0[] = {2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".a4",
"a..",
"4.."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 1; int Arg5 = 95; verify_case(2, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".B.",
"B.A",
".A."}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 1; int Arg5 = 262; verify_case(3, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arr0[] = {2,5,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,5,1,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {
".12.4.",
"1....7",
"2..3..",
"..3..5",
"4.....",
".7.5.."}
; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 53; int Arg4 = 37; int Arg5 = 1259; verify_case(4, Arg5, travel(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	SlimeXGrandSlimeAuto ___test;
	/*
	___test.run_test(2);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
