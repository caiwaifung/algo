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
typedef vector<string> VS;
typedef vector<int> VI;
typedef vector<PII> VPI;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //


class PalindromizationDiv1 {
	int MAXV;
	enum OpName { ADD, DEL, CHANGE };
	struct Op {
		OpName op;
		int c, c2, x;
		Op(string s) {
			istringstream in(s);
			string cmd, t;
			in>>cmd;
			if(cmd=="add") op=ADD;
			if(cmd=="erase") op=DEL;
			if(cmd=="change") op=CHANGE;
			in>>t; c=int(t[0]-'a');
			if(op==CHANGE) {
				in>>t; c2=int(t[0]-'a');
			}
			in>>x;
		}
	};
public:
	int c_add[33], c_del[33], c_change[33][33];
	int a[55];
	int n;
	int f[55][55];
	int go(int i, int j) {
	//printf("go %d %d\n",i,j);
		if(i>=j) return 0;
		int &ans=f[i][j];
		if(ans>=0) return ans;
		ans=MAXV;
		forn(k, 26) {
			setmin(ans, go(i+1, j)+min(MAXV, c_change[a[i]][k]+c_add[k]));
			setmin(ans, go(i, j-1)+min(MAXV, c_change[a[j]][k]+c_add[k]));
		}
		setmin(ans, go(i+1, j)+c_del[a[i]]);
		setmin(ans, go(i, j-1)+c_del[a[j]]);
		forn(k, 26)
			setmin(ans, go(i+1, j-1)+min(MAXV, c_change[a[i]][k]+c_change[a[j]][k]));
		return ans;
	}

	int getMinimumCost(string word, vector <string> operations) {
	printf("#\n");
		n=word.size();
		forint(i, 1, n) a[i]=int(word[i-1]-'a');
		fillchar(c_add, 55);
		fillchar(c_del, 55);
		fillchar(c_change, 55);
		MAXV=c_add[0];

		forn(i, operations.size()) {
			Op op(operations[i]);
			if(op.op==ADD) c_add[op.c]=op.x;
			if(op.op==DEL) c_del[op.c]=op.x;
			if(op.op==CHANGE) c_change[op.c][op.c2]=op.x;
		}
		forn(k, 26) setmin(c_change[k][k], 0);
		forn(k, 26) forn(i, 26) forn(j, 26)
			setmin(c_change[i][j], c_change[i][k]+c_change[k][j]);
		forn(i, 26) forn(j, 26) {
			setmin(c_add[i], c_add[j]+c_change[j][i]);
			setmin(c_del[i], c_del[j]+c_change[i][j]);
		}

		fillchar(f, 0xff);
		int ans=go(1, n);
		if(ans==MAXV) ans=-1;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "racecar"; string Arr1[] = {}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(0, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "topcoder"; string Arr1[] = {"erase t 1", "erase o 1", "erase p 1", "erase c 1", "erase d 1", "erase e 1", "erase r 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "topcoder"; string Arr1[] = {"erase t 10", "erase o 1", "erase p 1", "erase c 1", "erase d 1", "erase e 1", "erase r 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(2, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "caaaaaab"; string Arr1[] = {"change b a 100000", "change c a 100000", "change c d 50000", "change b e 50000", "erase d 50000", "erase e 49999"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 199999; verify_case(3, Arg2, getMinimumCost(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "moon"; string Arr1[] = {"erase o 5", "add u 7", "change d p 3", "change m s 12", "change n d 6", "change s l 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(4, Arg2, getMinimumCost(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PalindromizationDiv1 ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
