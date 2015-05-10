#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
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

template<size_t MAX_N, size_t MAX_E> struct Graph {
	int e_link[MAX_E]; int e_next[MAX_E];
	int first[MAX_N], degree[MAX_N];
	int n, e;
	void initalize(int nodes) {
		memset(first, 0, sizeof(first));
		memset(degree, 0, sizeof(degree));
		n = nodes;
		e = 0;
	}
	void add_edge(int x, int y) {
		e_link[++ e] = y;
		e_next[e] = first[x];
		first[x] = e;
		degree[y] ++;
	}
};

template<size_t MAX_N, size_t MAX_E> class SCC {
	int low[MAX_N], dfn[MAX_N], cnt;
	int stack[MAX_N], top;
	void dfs(const Graph<MAX_N, MAX_E> &graph, Graph<MAX_N, MAX_E> &blocks,
			int belong[], int head[], int x) {
		low[x] = dfn[x] = ++ cnt;
		stack[++ top] = x;
		belong[x] = -1;
		for (int e = graph.first[x]; e > 0; e = graph.e_next[e]) {
			int y = graph.e_link[e];
			if (-1 == belong[y])
				low[x] = min(low[x], dfn[y]);
			if (0 == belong[y]) {
				dfs(graph, blocks, belong, head, y);
				low[x] = min(low[x], low[y]);
			}
		}
		if (low[x] == dfn[x]) {
			head[++ blocks.n] = x;
			do {
				belong[stack[top --]] = blocks.n;
			} while (stack[top + 1] != x);
		}
	}
public:	
	void compute_scc(const Graph<MAX_N, MAX_E> &graph, Graph<MAX_N, MAX_E> &blocks,
			int belong[], int head[]) {
		blocks.initalize(0);
		for (int i = 1; i <= graph.n; i ++)
			belong[i] = 0;
		cnt = top = 0;
		for (int i = 1; i <= graph.n; i ++)
			if (0 == belong[i])
				dfs(graph, blocks, belong, head, i);
	}	
};

template<size_t MAX_N, size_t MAX_E> class TwoSat {
	Graph<MAX_N*2, MAX_E*2> graph, blocks;
	SCC<MAX_N*2, MAX_E*2> scc;
	int belong[MAX_N*2], head[MAX_N*2];
	int stack[MAX_N*2];
	bool answer[MAX_N*2];
	int n;   
	
public:
	void initialize(int nodes) {
		graph.initalize(nodes * 2);
		n = nodes;
	}
	
	void add_conflict(int x, int sx, int y, int sy) {
		graph.add_edge(x + sx*n, y + (sy^1)*n);
		graph.add_edge(y + sy*n, x + (sx^1)*n);
	}
	
	bool compute(int scheme[]) {
		scc.compute_scc(graph, blocks, belong, head);
	
		for (int i = 1; i <= n; i ++)
			if (belong[i] == belong[i+n])
				return false;
		for (int x = 1; x <= graph.n; x ++)
			for (int i = graph.first[x]; i > 0; i = graph.e_next[i])
				if (belong[x] != belong[graph.e_link[i]])
					blocks.add_edge(belong[graph.e_link[i]], belong[x]);
			
		memset(answer, true, sizeof(answer));
		int top = 0;
		for (int x = 1; x <= blocks.n; x ++)
			if (blocks.degree[x] == 0)
				stack[++ top] = x;
		while (top > 0) {
			int x = stack[top --];
			#define oppo(x) ((x)<=n?(x)+n:(x)-n)
			if (answer[x])
				answer[belong[oppo(head[x])]]=false;
			for (int i = blocks.first[x]; i > 0; i = blocks.e_next[i])
				if (-- blocks.degree[blocks.e_link[i]] == 0)
					stack[++ top] = blocks.e_link[i];
		}
		for (int i = 1; i <= n; i ++)
			scheme[i] = (answer[belong[i]] ? 0 : 1);
		return true;
	}
};

const int MAXN=110;
const int MAXV=110;
const int MAXQ=2010;

TwoSat<MAXN*MAXV, MAXN*MAXV + MAXQ*MAXV> sat;

class NeverAskHerAge {
	int id[MAXN][MAXV];
	public:
		int sgn(double x, double e=1e-8) {
			return x<-e ? -1 : x>e;
		}
		double cal(double x, double y, string op) {
			if(op=="+") return x+y;
			if(op=="-") return x-y;
			if(op=="*") return x*y;
			if(op=="/") return x/y;
			return 0;
		}
		bool holds(int x, int y, string op, string rl, int val) {
			double l=cal(x, y, op);
			double r=val/1000.;
			int t=sgn(l-r);
			if(rl=="<") return t<0;
			if(rl==">") return t>0;
			if(rl=="<=") return t<=0;
			if(rl==">=") return t>=0;
			if(rl=="=") return t==0;
			return false;
		}
		int better_direction_1(string op, string rl) {
			if(rl=="<" || rl=="<=") {
				return -1;
			} else {
				return 1;
			}
		}
		int better_direction_2(string op, string rl) {
			if(rl=="<" || rl=="<=") {
				if(op=="+" || op=="*") return -1;
				else return 1;
			} else {
				if(op=="+" || op=="*") return 1;
				else return -1;
			}
		}
		void add_limit(int i1, int i2, string op, string rl, int val) {
			if(rl=="=") {
				add_limit(i1, i2, op, ">=", val);
				add_limit(i1, i2, op, "<=", val);
				return;
			}
			forint(j1, 1, 100) {
				int j2;
				if(better_direction_2(op, rl)>0) {
					for(j2=100; j2>0 && holds(j1, j2, op, rl, val); --j2);
					if(j2<1) continue;
					if(better_direction_1(op, rl)>0) {
						sat.add_conflict(id[i1][j1], 1, id[i2][j2], 1);
					} else {
						sat.add_conflict(id[i1][j1-1], 0, id[i2][j2], 1);
					}
				} else {
					for(j2=1; j2<101 && holds(j1, j2, op, rl, val); ++j2);
					if(j2>100) continue;
					if(better_direction_1(op, rl)>0) {
						sat.add_conflict(id[i1][j1], 1, id[i2][j2-1], 0);
					} else {
						sat.add_conflict(id[i1][j1-1], 0, id[i2][j2-1], 0);
					}
				}
			}
		}
		vector <int> possibleSolution(int n, vector <int> id1, vector <int> id2, vector <string> op, vector <string> rl, vector <int> val) {
			//printf("%.9lf MB\n", sizeof(sat)/1024./1024.);

			// init vars
			int num=0;
			forint(i, 1, n) forint(j, 0, 100) id[i][j]=++num;
			sat.initialize(num);

			// let vars of x[i] be 00...0011...11
			forint(i, 1, n) {
				sat.add_conflict(id[i][0], 1, id[i][0], 1);
				sat.add_conflict(id[i][100], 0, id[i][100], 0);
				forint(j, 1, 100)
					sat.add_conflict(id[i][j-1], 1, id[i][j], 0);
			}
			// add limits
			int q=id1.size();
			forn(i, q) add_limit(id1[i], id2[i], op[i], rl[i], val[i]);

			static int s[MAXN*MAXV];
			if(sat.compute(s)) {
				static int v[MAXN];
				forint(i, 1, n) forint(j, 1, 100)
					if(s[id[i][j]]>0) {
						v[i]=j;
						break;
					}
				VI ans;
				forint(i, 1, n) ans.PB(v[i]);
				return ans;
			} else {
				return vector <int>();
			}
		}
		
// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = { 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "+", "*" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { "=", "=" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 10000, 21000 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = { 3, 7 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(0, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 7; int Arr1[] = { 1, 2, 3, 4, 5, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 3, 4, 5, 6, 7 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "/", "/", "/", "/", "/", "/" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { "=", "=", "=", "=", "=", "=" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 2000, 2000, 2000, 2000, 2000, 2000 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = { 64, 32, 16, 8, 4, 2, 1 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(1, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 2; int Arr1[] = { 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "/", "/" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { ">", "<" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 2621, 2622 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = { 97, 37 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(2, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 2; int Arr1[] = { 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "*", "+" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { ">", "<=" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 6000, 5000 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {0}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(3, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arg0 = 8; int Arr1[] = { 1, 3, 5, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 4, 6, 8 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "+", "-", "*", "/" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { ">=", "<=", "=", "<=" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 200000, -99000, 3589000, 10 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = { 100, 100, 1, 100, 97, 37, 1, 100 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(4, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_5() { int Arg0 = 8; int Arr1[] = { 7, 1, 3, 4, 4, 3, 7, 2, 3, 6, 4, 4, 6, 5, 2, 8, 2, 2, 7, 6, 2, 2, 8, 6, 5, 6, 5, 4, 4, 8, 6, 1, 3, 5, 5, 4, 3, 7, 4, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 7, 6, 6, 1, 2, 4, 7, 4, 4, 8, 3, 8, 2, 4, 1, 7, 7, 6, 2, 5, 7, 6, 5, 8, 2, 8, 1, 8, 1, 3, 2, 7, 1, 2, 2, 1, 8, 3, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "/", "*", "/", "-", "*", "+", "*", "+", "/", "+", "-", "+", "*", "+", "/", "*", "-", "/", "-", "*", "/", "/", "/", "*", "/", "+", "+", "*", "*", "-", "-", "*", "+", "+", "+", "-", "+", "/", "+", "*" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { "<", "<", "<=", ">", "<", "<=", "<", ">", "<", "<=", "<=", ">", ">", ">=", "<", ">", "<", "<", ">", ">=", "<=", "<", "<=", ">=", "<=", ">=", ">=", ">=", "<=", ">=", "<=", ">", "<=", "<", ">", "<=", ">=", "<", "<=", "<=" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 47636, 5754558, 3307, -41496, 7043286, 144246, 5048203, 72315, 85384, 182630, 50604, 9802, 3843942, 152392, 60035, 149684, 94234, 31209, -73898, 195742, 8383, 71993, 98477, 4859384, 74619, 146266, 60163, 377564, 5357728, -80040, 72545, 1088942, 87517, 192354, 18629, 45785, 44151, 95334, 140360, 1063484 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = { 56, 77, 19, 59, 77, 87, 43, 51 }; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(5, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_6() { int Arg0 = 8; int Arr1[] = { 7, 1, 3, 4, 4, 3, 7, 2, 3, 6, 4, 4, 6, 5, 2, 8, 2, 2, 7, 6, 2, 2, 8, 6, 5, 6, 5, 4, 4, 8, 6, 1, 3, 5, 5, 4, 3, 7, 4, 8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 7, 6, 6, 1, 2, 4, 7, 4, 4, 8, 3, 8, 2, 4, 1, 7, 7, 6, 2, 5, 7, 6, 5, 8, 2, 8, 1, 8, 1, 3, 2, 7, 1, 2, 2, 1, 8, 3, 3 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = { "/", "*", "/", "-", "*", "+", "*", "+", "/", "+", "-", "+", "*", "+", "/", "*", "-", "/", "-", "*", "/", "/", "/", "*", "/", "+", "+", "*", "*", "-", "-", "*", "+", "+", "+", "-", "+", "/", "+", "*" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = { "=", "<", "<=", ">", "<", "<=", "<", ">", "<", "<=", "<=", ">", ">", ">=", "<", ">", "<", "<", ">", ">=", "<=", "<", "<=", ">=", "<=", ">=", ">=", ">=", "<=", ">=", "<=", ">", "<=", "<", ">", "<=", ">=", "<", "<=", "<=" }; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = { 2000, 5754558, 3307, -41496, 7043286, 144246, 5048203, 72315, 85384, 182630, 50604, 9802, 3843942, 152392, 60035, 149684, 94234, 31209, -73898, 195742, 8383, 71993, 98477, 4859384, 74619, 146266, 60163, 377564, 5357728, -80040, 72545, 1088942, 87517, 192354, 18629, 45785, 44151, 95334, 140360, 1063484 }; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arr6[] = {0}; vector <int> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(6, Arg6, possibleSolution(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	NeverAskHerAge ___test;
	___test.run_test(-1);
	system("pause");
	return 0;
}
// END CUT HERE

