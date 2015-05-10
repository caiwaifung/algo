#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
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

class CliqueGraph {
public:
	vector<VI> cliques;
	vector<VI> belong;
	int N;

	vector<int> dis;
	vector<bool> visited;
	queue<int> que;

	LL compute(int start) {
		dis.resize(N);
		forn(i, N) dis[i] = 1 << 30;

		visited.resize(cliques.size());
		forn(i, cliques.size()) visited[i] = false;

		que = queue<int>();
		que.push(start);
		dis[start] = 0;
		while (!que.empty()) {
			int x = que.front();
			que.pop();
			forn(i, belong[x].size()) {
				int cur = belong[x][i];
				if (!visited[cur]) {
					visited[cur] = true;
					int d = dis[x] + 1;
					forn(j, cliques[cur].size()) {
						int y = cliques[cur][j];
						if (d < dis[y]) {
							dis[y] = d;
							que.push(y);
						}
					}
				}
			}
		}

		LL ans = 0;
		forn(i, N) ans += dis[i];
		//forn(i, N) printf("d[%d,%d] = %d\n", start, i, dis[i]);
		return ans;
	}

	long long calcSum(int _N, vector <int> V, vector <int> sizes) {
		N = _N;
		cliques.resize(sizes.size());
		belong.resize(N);
		int cur = 0;
		forn(i, N) belong[i].clear();
		forn (i, cliques.size()) {
			cliques[i].clear();
			forn(j, sizes[i]) {
				int x = V[cur + j];
				cliques[i].push_back(x);
				belong[x].push_back(i);
			}
			cur += sizes[i];
		}

		long long ans = 0;
		forn(i, N) ans += compute(i);

		return ans / 2;
	}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = {0,1,2,0,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 8LL; verify_case(0, Arg3, calcSum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; int Arr1[] = {0,1,2,3,1,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 12LL; verify_case(1, Arg3, calcSum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 15; int Arr1[] = {1,3,5,7,9,11,13,0
,2,3,6,7,10,11,14,0
,4,5,6,7,12,13,14,0
,8,9,10,11,12,13,14,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {8,8,8,8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 130LL; verify_case(2, Arg3, calcSum(Arg0, Arg1, Arg2)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
	CliqueGraph ___test;
	//___test.run_test(-1);
	___test.run_test(-1);
	system("pause");
	return 0;
}
// END CUT HERE

