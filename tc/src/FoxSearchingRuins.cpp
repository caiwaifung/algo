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

const int MAXN=1010;

struct Jewel {
	int x, y, v, yi;
	bool operator <(const Jewel &b) const {
		return MP(y, x) < MP(b.y, b.x);
	}
};

struct Fen {
	int a[1002];
	void add(int x, int v) {
		x=1001-x;
		for(; x<=1001; x+=(x&-x)) a[x]=max(a[x], v);
	}
	int get(int x) const {
		x=1001-x;
		int v=0;
		for(; x>=1; x-=(x&-x)) v=max(v, a[x]);
		return v;
	}
};

class FoxSearchingRuins {
	void upt(int &x, int y) {
		x=max(x, y);
	}
public:
	long long theMinTime(int W, int H, int jewelCount, int LR, int goalValue, int timeX, int timeY, vector <int> seeds) {
		static Jewel jewels[MAXN];
		jewels[1].x = int((seeds[1] * (LL)seeds[0] + seeds[2]) % W);
		jewels[1].y = int((seeds[4] * (LL)seeds[3] + seeds[5]) % H);
		jewels[1].v = int((seeds[7] * (LL)seeds[6] + seeds[8]) % seeds[9]);
		forint(i, 2, jewelCount) {
			jewels[i].x = int((seeds[1] * (LL)jewels[i-1].x + seeds[2]) % W);
			jewels[i].y = int((seeds[4] * (LL)jewels[i-1].y + seeds[5]) % H);
			jewels[i].v = int((seeds[7] * (LL)jewels[i-1].v + seeds[8]) % seeds[9]);
		}
		sort(jewels+1, jewels+jewelCount+1);
		int tmpCount=jewelCount;
		jewelCount=1;
		forint(i, 2, tmpCount) {
			if(jewels[i].x==jewels[jewelCount].x && jewels[i].y==jewels[jewelCount].y)
				jewels[jewelCount].v+=jewels[i].v;
			else
				jewels[++jewelCount]=jewels[i];
		}
		//forint(i, 1, jewelCount) forint(j, 1, i-1) if(jewels[i].x==jewels[j].x && jewels[i].y==jewels[j].y) {printf("ERROR!\n");goto lab;}lab:

		LL ans=1LL<<50, maxval=ans;

		static int f[MAXN][1010];
		static int fl[MAXN][1010];
		static int fr[MAXN][1010];
		fillchar(f, 0);
		fillchar(fl, 0);
		fillchar(fr, 0);
		forint(i, 1, jewelCount)
			f[i][LR]=jewels[i].v;

		static Fen tl[2010], tr[2010];
		fillchar(tl, 0);
		fillchar(tr, 0);

		// the energy function
#define el(i,cur) (LR-cur+jewels[i].x)
#define er(i,cur) (LR-cur+W-1-jewels[i].x)

		for(int le=1, ri; le<=jewelCount; le=ri+1) { // calculate it up-to-down
			for(ri=le; ri<jewelCount && jewels[ri+1].y==jewels[ri].y; )
				++ri;

			// from upside
			forint(i, le, ri) forint(cur, 0, LR) {
				upt(f[i][cur], tl[el(i,cur)].get(cur)+jewels[i].v);
				upt(f[i][cur], tr[er(i,cur)].get(cur)+jewels[i].v);
			}

			// from left or right
			forint(i, le, ri) forint(cur, 0, LR) {
				fl[i][cur]=fr[i][cur]=f[i][cur];
			}
			forint(i, le, ri-1) forint(cur, 0, LR) {
				int c2=cur-(jewels[i+1].x-jewels[i].x);
				if(c2>=0) upt(fl[i+1][c2], fl[i][cur]+jewels[i+1].v);
			}
			forintdown(i, ri, le+1) forint(cur, 0, LR) {
				int c2=cur-(jewels[i].x-jewels[i-1].x);
				if(c2>=0) upt(fr[i-1][c2], fr[i][cur]+jewels[i-1].v);
			}
			forint(i, le, ri) forint(cur, 0, LR) {
				upt(f[i][cur], max(fl[i][cur], fr[i][cur]));
			}
			//*/
			// update
			forint(i, le, ri) forint(cur, 0, LR) {
				tl[el(i,cur)].add(cur, f[i][cur]);
				tr[er(i,cur)].add(cur, f[i][cur]);
				//printf("fin f[%d][%d]=%d\n",i,cur,f[i][cur]);
			}
			forint(i, le, ri) forint(cur, 0, LR) if(f[i][cur]>=goalValue) {
				LL lr=LR-cur, dn=jewels[i].y;
				LL cost=lr*timeX+dn*timeY;
				/*
				   if(cost<ans) {
				   printf("f[%d][%d]=%d\n", i, cur, f[i][cur]);
				   printf("le=%d ri=%d n=%d\n",le,ri,jewelCount);
				   printf("lr=%d dn=%d\n",lr,dn);
				   cout<<cost<<endl;
				   }
				 //*/
				ans=min(ans, cost);
			}
		}

		if(ans==maxval) ans=-1;
		return ans;
	}

	// BEGIN CUT HERE
public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 8; int Arg2 = 5; int Arg3 = 7; int Arg4 = 10; int Arg5 = 3; int Arg6 = 1; int Arr7[] = {979, 777, 878, 646, 441, 545, 789, 896, 987, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 5LL; verify_case(0, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_1() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 10; int Arg3 = 3; int Arg4 = 10; int Arg5 = 3; int Arg6 = 10; int Arr7[] = {0, 1, 1, 0, 1, 3, 1011, 3033, 2022, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 29LL; verify_case(1, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_2() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 10; int Arg3 = 3; int Arg4 = 14; int Arg5 = 3; int Arg6 = 10; int Arr7[] = {0, 1, 1, 0, 1, 3, 1011, 3033, 2022, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 59LL; verify_case(2, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 8; int Arg2 = 10; int Arg3 = 4; int Arg4 = 14; int Arg5 = 3; int Arg6 = 10; int Arr7[] = {0, 1, 1, 0, 1, 3, 1011, 3033, 2022, 10}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 42LL; verify_case(3, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_4() { int Arg0 = 497; int Arg1 = 503; int Arg2 = 989; int Arg3 = 647; int Arg4 = 100000; int Arg5 = 13; int Arg6 = 14; int Arr7[] = {7613497, 5316789, 1334537, 2217889, 6349551, 978463, 1234567, 2345678, 3456789, 1000}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = -1LL; verify_case(4, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_5() { int Arg0 = 1000; int Arg1 = 749613275; int Arg2 = 1000; int Arg3 = 1000; int Arg4 = 7500000; int Arg5 = 97; int Arg6 = 6; int Arr7[] = {224284427, 617001937, 294074399, 606566321, 202762619, 419798101, 200613401, 640663967, 417565817, 170000}; vector <int> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); long long Arg8 = 3780225876LL; verify_case(5, Arg8, theMinTime(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	FoxSearchingRuins ___test;
	//___test.run_test(4); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
