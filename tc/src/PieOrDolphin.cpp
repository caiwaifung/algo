#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define forint(i, a, b) for(int i=(int)(a); i<=(int)(b); ++i)
#define forintdown(i, a, b) for(int i=(int)(a); i>=(int)(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPI;
#define MP make_pair
#define PB push_back
#define fi first
#define se second

const int MAXN=55;
const int n=50;

class PieOrDolphin {
public:
	VI e[MAXN][MAXN];
	int vis[MAXN], lst[MAXN];
	bool found;
	VI cycle;
	void dfs(int x, int dep) {
		vis[x]=dep; lst[dep]=x;
		forint(y, 1, n) if(e[x][y].size()>0) {
			if(vis[y]>0 && vis[y]<dep-1) {
				found=true;
				cycle.clear();
				forint(i, vis[y], vis[x])
					cycle.PB(lst[i]);
				return;
			}
			if(vis[y]==0) {
				dfs(y, dep+1);
				if(found) return;
			}
		}
		vis[x]=-1;
	}
	VI ans;
	void make(int i, int x) {
		//printf("make %d %d\n",i,x);
		if(i<0) {
			i=-i-1;
			x=3-x;
		}
		ans[i]=x;
		//printf("maked\n");
	}

	void go(int x, int la) {
		vis[x]=1;
		forint(y, 1, n) if(!vis[y]) {
			forn(i, e[x][y].size()) {
				make(e[x][y][i], la);
				go(y, la);
				la=3-la;
			}
		}
	}

	vector<int> Distribute(vector<int> choice1, vector<int> choice2) {
		forint(i, 1, n) forint(j, 1, n)
			e[i][j].clear();
		forn(i, choice1.size()) {
			int x=choice1[i]+1;
			int y=choice2[i]+1;
			e[x][y].PB(i);
			e[y][x].PB(-i-1);
		}
		//cout<<"!"<<endl;
		ans.resize(choice1.size());
		forint(i, 1, n) forint(j, 1, n) {
			while(e[i][j].size()>=2) {
				//printf("i=%d j=%d sz=%d sz2=%d\n",i,j,e[i][j].size(),e[j][i].size());
				make(e[i][j].back(), 1);
				e[i][j].pop_back();
				e[j][i].pop_back();
				//printf("i=%d j=%d\n",i,j);
				make(e[i][j].back(), 2);
				e[i][j].pop_back();
				e[j][i].pop_back();
				//printf("i=%d j=%d\n",i,j);
			}
		}
		//cout<<"#1"<<endl;
		while(1) {
			fillchar(vis, 0);
			found=false;
			forint(i, 1, n) if(vis[i]==0) {
				dfs(i, 1);
				if(found) break;
			}
			if(!found) break;
			forn(i, cycle.size()) {
				int x=cycle[i], y=cycle[(i+1)%cycle.size()];
				make(e[x][y].back(), 1);
				e[x][y].pop_back();
				e[y][x].pop_back();
			}
		}
		fillchar(vis, 0);
		forint(x, 1, n) if(vis[x]==0) {
			int deg=0;
			forint(y, 1, n) deg+=e[x][y].size();
			if(deg==1) {
				forint(y, 1, n) if(e[x][y].size()>0) {
					make(e[x][y].back(), 1);
					vis[x]=1;
					go(y, 1);
				}
			}
		}
		return ans;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {10, 20, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 30, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 1, 2, 3, 5, 6, 7, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 7, 6, 5, 3, 2, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2, 2, 2, 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {49, 0, 48, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 5, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, Distribute(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {21,4,14,0,31,46,1,34,2,3,27,19,47,46,17,11,41,12,31,0,34,18,8,14,23,40,0,18,48,35,42,24,25,32,25,44,17,6,44,34,12,39,43,39,26,
34,10,6,13,2,40,15,16,32,32,29,1,23,8,10,49,22,10,15,40,20,0,30,1,43,33,42,28,39,28,4,38,11,5,1,47,12,0,22,20,33,33,34,18,8,23,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {25,5,39,20,44,47,11,49,42,17,25,15,23,11,32,17,24,4,11,47,27,41,40,0,49,27,5,28,6,11,18,0,17,1,0,32,45,28,17,5,13,40,40,25,33,
7,8,32,12,0,39,30,8,39,23,9,8,34,34,37,5,1,24,23,0,29,11,42,29,40,24,18,37,1,21,0,31,47,23,33,45,48,31,11,40,45,24,22,19,26,37,39}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, Distribute(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	PieOrDolphin ___test;
	//___test.run_test(-1);
	___test.run_test(0);
	return 0;
}
// END CUT HERE
