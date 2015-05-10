#include <cctype>
#include <queue>
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
const string YES="Possible";
const string NO="Impossible";

int g[MAXN], g_lnk[MAXN*2], g_nxt[MAXN*2], g_cst[MAXN*2];
int n;

LL d[MAXN][22222];
bool vis[MAXN][22222];

class LongLongTripDiv1
{
	public:

		string isAble(int N, vector <int> A, vector <int> B, vector <int> D, long long T)
		{
			n=N; int e=0; fillchar(g, 0);
			forn(i, A.size()) {
				int a=A[i]+1, b=B[i]+1, c=D[i];
				g_lnk[++e]=b, g_cst[e]=c, g_nxt[e]=g[a], g[a]=e;
				g_lnk[++e]=a, g_cst[e]=c, g_nxt[e]=g[b], g[b]=e;
			}

			if(g[1]==0) return NO;
			int w=g_cst[g[1]]*2;

			/*
			priority_queue<pair<LL,PII> > que;
			fillchar(d, 55);
			fillchar(vis, false);
			d[1][0]=0; que.push(MP(0,MP(1,0)));
			while(!que.empty()) {
				PII cur=que.top().se; que.pop();
				int x=cur.fi, xw=cur.se;
				if(vis[x][xw]) continue;
				vis[x][xw]=true;
				for(int i=g[x]; i; i=g_nxt[i]) {
					int y=g_lnk[i], yw=(xw+g_cst[i])%w;
					if(d[x][xw]+g_cst[i]<d[y][yw]) {
						d[y][yw]=d[x][xw]+g_cst[i];
						que.push(MP(-d[y][yw], MP(y,yw)));
					}
				}
			}
			*/
			set<pair<LL,PII> > que;
			fillchar(d, 55);
			fillchar(vis, false);
			d[1][0]=0; que.insert(MP(0,MP(1,0)));
			while(!que.empty()) {
				PII cur=que.begin()->se; que.erase(que.begin());
				int x=cur.fi, xw=cur.se;
				if(vis[x][xw]) continue;
				vis[x][xw]=true;
				for(int i=g[x]; i; i=g_nxt[i]) {
					int y=g_lnk[i], yw=(xw+g_cst[i])%w;
					if(d[x][xw]+g_cst[i]<d[y][yw]) {
						que.erase(MP(d[y][yw], MP(y,yw)));
						d[y][yw]=d[x][xw]+g_cst[i];
						que.insert(MP(d[y][yw], MP(y,yw)));
					}
				}
			}

			if(d[n][T%w]>T) return NO;
			else return YES;
		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { int Arg0 = 3; int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {7,6,5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 11LL; string Arg5 = "Possible"; verify_case(0, Arg5, isAble(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_1() { int Arg0 = 3; int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {7,6,5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 25LL; string Arg5 = "Possible"; verify_case(1, Arg5, isAble(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_2() { int Arg0 = 2; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 9LL; string Arg5 = "Possible"; verify_case(2, Arg5, isAble(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_3() { int Arg0 = 2; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 1000000000000000000LL; string Arg5 = "Impossible"; verify_case(3, Arg5, isAble(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_4() { int Arg0 = 4; int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {10,10,10}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 1000LL; string Arg5 = "Impossible"; verify_case(4, Arg5, isAble(Arg0, Arg1, Arg2, Arg3, Arg4)); }
		void test_case_5() { int Arg0 = 9; int Arr1[] = {4,8,5,8,3,6,2,6,7,6,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,7,1,5,1,3,1,1,5,4,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {6580,8822,1968,673,1394,9337,5486,1746,5229,4092,195}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 937186357646035002LL; string Arg5 = "Impossible"; verify_case(5, Arg5, isAble(Arg0, Arg1, Arg2, Arg3, Arg4)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	LongLongTripDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
