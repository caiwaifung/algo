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

template<size_t N, size_t E> class MaxFlow {
	struct Edge {
		int y;  LL w;
		Edge *next, *oppo;
	} edges[E*2];
	int e_cnt;
	Edge *g[N], *ce[N];
	int n, src, dst;

	int d[N], q[N];
	bool build() {
		memset(d, 0, sizeof(d));
		d[q[1]=src]=1;
		for(int ss=0, tt=1; ss<tt; ) {
			int x=q[++ss];
			for(Edge *e=ce[x]=g[x]; e!=NULL; e=e->next)
				if(e->w>0 && d[e->y]==0)
					d[q[++tt]=e->y]=d[x]+1;
		}
		return d[dst]>0;
	}
	LL find(int x, LL rest) {
		if(x==dst) return rest;
		LL ans=0;
		for(Edge *&e=ce[x]; e!=NULL; e=e->next)
			if(e->w>0 && d[e->y]>d[x]) {
				LL cur=find(e->y, min(e->w,rest));
				e->w-=cur; e->oppo->w+=cur;
				ans+=cur; rest-=cur;
				if(rest==0) break;
			}
		return ans;
	}

	public:
	void initialize(int _n, int _s, int _t) {
		n=_n, src=_s, dst=_t;
		memset(g, 0, sizeof(g));
		e_cnt=0;
	}
	void add_edge(int x, int y, LL w1, LL w2) {
		Edge *e1=&edges[e_cnt++];
		Edge *e2=&edges[e_cnt++];
		e1->y=y, e1->w=w1, e1->oppo=e2, e1->next=g[x], g[x]=e1;
		e2->y=x, e2->w=w2, e2->oppo=e1, e2->next=g[y], g[y]=e2;
	}
	LL compute() {
		LL ans=0, INFI;
		memset(&INFI, 100, sizeof(INFI));
		while(build()) ans+=find(src, INFI);
		return ans;
	}
};

const int dx[4]={0, 1, 0, -1};
const int dy[4]={1, 0, -1, 0};

class FoxAndGo3 {
	public:
	int maxEmptyCells(vector <string> board) {
		MaxFlow<55*55, 55*55*4+55*55> flow;
		int n=board.size();
		int m=board[0].size();
		int s=n*m+1, t=n*m+2;
		flow.initialize(n*m+2, s, t); 
		vector<VI> id; int cur_id=0;
		id.resize(n);
		forn(i, n) {
			id[i].resize(m);
			forn(j, m) id[i][j]=++cur_id;
		}
		int ans=0;
		forn(i, n) forn(j, m) {
			if(board[i][j]=='o') {
				flow.add_edge(s, id[i][j], 1, 0);
				forn(k, 4) {
					int i0=i+dx[k], j0=j+dy[k];
					if(i0<0 || i0>=n || j0<0 || j0>=m) continue;
					if(board[i0][j0]=='.')
						flow.add_edge(id[i][j], id[i0][j0], 1<<20, 0);
				}
				++ans;
			}
			if(board[i][j]=='.') {
				flow.add_edge(id[i][j], t, 1, 0);
				++ans;
			}
		}
		ans-=(int)flow.compute();
		return ans;
	}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { string Arr0[] = {"o.o",
			".o.",
			"o.o"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, maxEmptyCells(Arg0)); }
		void test_case_1() { string Arr0[] = {"...",
			".o.",
			"..."}
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(1, Arg1, maxEmptyCells(Arg0)); }
		void test_case_2() { string Arr0[] = {"xxxxx",
			"xxoxx",
			"xo.ox",
			"xxoxx",
			"xxxxx"}
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, maxEmptyCells(Arg0)); }
		void test_case_3() { string Arr0[] = {".xox.",
			".o.ox",
			"x.o.o",
			"ox.ox",
			".ox.."}
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(3, Arg1, maxEmptyCells(Arg0)); }
		void test_case_4() { string Arr0[] = {"o.o.o",
			".ox..",
			"oxxxo",
			"..x..",
			"o.o.o"}
		; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(4, Arg1, maxEmptyCells(Arg0)); }
		void test_case_5() { string Arr0[] = {"...",
			"...",
			"..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(5, Arg1, maxEmptyCells(Arg0)); }

		// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	FoxAndGo3 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
