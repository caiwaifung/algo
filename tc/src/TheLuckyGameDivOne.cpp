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
typedef pair<LL,LL> PLL;
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //

class TheLuckyGameDivOne {
public:
	LL lucks[9999];
	int num;
	PLL events[9999];
	int en;

	void dfs(LL x) {
		if(x>LL(1e10))
			return;
		lucks[++num]=x;
		dfs(x*10+4);
		dfs(x*10+7);
	}

	LL go(LL a, LL b, LL x, LL p) {
		LL y=x+p-1;
		if(x<a || y>b) return 0;
		LL cur=0;
		int i=1;
		while(i<=en && events[i].fi<=x) {
			cur+=events[i].se;
			++i;
		}
		LL ans=cur;
		while(i<=en && events[i].fi<=y) {
			LL pos=events[i].fi;
			while(i<=en && events[i].fi==pos) {
				cur+=events[i].se;
				++i;
			}
			setmin(ans, cur);
		}
		return ans;
	}

	int find(long long a, long long b, long long p, long long q) {
		num=0;
		dfs(0);
		sort(lucks+1, lucks+num+1);
		printf("num = %d\n", num);

		b=b-q+1; p=p-q+1;
		en=0;
		forint(i, 1, num) {
			LL s=lucks[i]-q+1;
			LL t=lucks[i];
			if(t>=a && s<=b) {
				events[++en]=MP(max(s,a), 1);
				if(t<b)
					events[++en]=MP(t+1, -1);
			}
		}
		sort(events+1, events+en+1);

		LL ans=0;
		forint(i, 1, en) setmax(ans, go(a, b, events[i].fi, p));
		forint(i, 1, en) setmax(ans, go(a, b, events[i].fi-p, p));
		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 10LL; long long Arg2 = 2LL; long long Arg3 = 1LL; int Arg4 = 0; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 100LL; long long Arg2 = 100LL; long long Arg3 = 100LL; int Arg4 = 6; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { long long Arg0 = 4LL; long long Arg1 = 8LL; long long Arg2 = 3LL; long long Arg3 = 2LL; int Arg4 = 1; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { long long Arg0 = 1LL; long long Arg1 = 100LL; long long Arg2 = 75LL; long long Arg3 = 50LL; int Arg4 = 2; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	TheLuckyGameDivOne ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
