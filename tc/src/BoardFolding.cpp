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

const LL M1=LL(1e9)+7;
const LL P1=LL(911);
const LL M2=LL(1e9)+9;
const LL P2=LL(65535);

class BoardFolding {
	LL hash1(int x[], int n) {
		LL p=0;
		forn(i, n) p=(p*P1+x[i])%M1;
		return p;
	}
public:
	int tonum(char c) {
		if (c>='0' && c<='9') return int(c-'0'+0);
		if (c>='a' && c<='z') return int(c-'a'+10);
		if (c>='A' && c<='Z') return int(c-'A'+36);
		if (c=='#') return 62;
		if (c=='@') return 63;
		exit(1);
	}
	
	int paper[255][255];
	int n, m;

	LL a[255];
	LL h1[255], h2[255], hp[255];
	LL geth1(int i, int j) {
		--i;
		LL t=h1[j]-h1[i]*hp[j-i];
		t%=M2;
		if(t<0) t+=M2;
		return t;
	}
	LL geth2(int i, int j) {
		++j;
		LL t=h2[i]-h2[j]*hp[j-i];
		t%=M2;
		if(t<0) t+=M2;
		return t;
	}

	int go() {
		forn(i, n) a[i]=hash1(paper[i], m);

//forn(i, n) printf("a[%d]=%lld\n",i,a[i]);
		hp[0]=1; forint(i, 1, n) hp[i]=hp[i-1]*P2%M2;

		h1[0]=0;
		forint(i, 1, n) 
			h1[i]=(h1[i-1]*P2+a[i-1])%M2;
		h2[n+1]=0;
		forintdown(i, n, 1)
			h2[i]=(h2[i+1]*P2+a[i-1])%M2;

		//cout<<geth1(1, 2)<<" "<<geth2(3, 4)<<endl;
		//cout<<geth2(1, 2)<<" "<<geth1(3, 4)<<endl;

		static bool ok[255][255];
		fillchar(ok, false);
		ok[1][n]=true;
		forint(i, 1, n) forintdown(j, n, i)
			if(ok[i][j]) {
				forint(k, i, j) {
					int len=k-i+1;
					if(k+len>j) continue;
					if(geth1(i,k)==geth2(k+1, k+len))
						ok[k+1][j]=true;
				}
				forint(k, i, j) {
					int len=j-k+1;
					if(k-len<i) continue;
					if(geth1(k,j)==geth2(k-len,k-1))
						ok[i][k-1]=true;
				}
			}
		int ans=0;
		forint(i, 1, n) forint(j, i, n) if(ok[i][j]) ++ans;
		return ans;
	}

	int howMany(int N, int M, vector <string> compressedPaper) {
		forn(i, N) forn(j, M)
			paper[i][j]=(tonum(compressedPaper[i][j/6]) >> (j%6)) % 2;
		n=N, m=M;

		int ans1=go(); printf("ans1=%d\n", ans1);

		static int tmp[255][255];
		forn(i, n) forn(j, m) tmp[j][i]=paper[i][j];
		swap(n, m);
		forn(i, n) forn(j, m) paper[i][j]=tmp[i][j];

		int ans2=go(); printf("ans2=%d\n", ans2);
		return int(ans1*ans2);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; string Arr2[] = {"1", "3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 7; string Arr2[] = {"@@", "@@"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 84; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 4; string Arr2[] = {"6", "9", "9", "6"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 9; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; string Arr2[] = {"0", "2", "6", "@", "4", "A"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 3; int Arg1 = 3; string Arr2[] = {"0", "2", "0"}
; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	BoardFolding ___test;
	/*
	___test.run_test(2);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
