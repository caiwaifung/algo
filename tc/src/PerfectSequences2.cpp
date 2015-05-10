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

class PerfectSequences2 {
public:
	LL go_zero(VI seq) {
		LL s=0, ans=1LL<<60;
		forn(i, seq.size()) s+=seq[i];
		forn(i, seq.size())
			setmin(ans, abs(s-seq[i])+abs(seq[i]));
		return ans;
	}
	LL go_x(VI seq) {
		LL ans=1LL<<60;
		if(seq.size()%4==1) {
			forn(i, seq.size()) {
				VI t=seq;
				t.erase(t.begin()+i);
				LL tmp=0;
				forn(i, t.size()/2) {
					tmp+=abs(t[i]+1);
					tmp+=abs(t[i+t.size()/2]-1);
				}
				setmin(ans, tmp);
			}
		}
		return ans;
	}
	long long minimumMoves(vector <int> seq) {
		sort(seq.begin(), seq.end());
		LL ans=go_zero(seq);
		setmin(ans, go_x(seq));

		const int N=110;
		static LL f[55][N*2+1][N*2+1];
		fillchar(f, 50);
		f[0][0+N][1+N]=0;
		forn(i, seq.size()) {
			forint(sum, -N, N) forint(prod, -N, N) {
				LL cur=f[i][sum+N][prod+N];
				//if(cur<10) cout<<"i: "<<cur<<endl;
				forint(x, -N, N) {
					int sum2=sum+x, prod2=prod*x;
					if(sum2<-N || sum2>N || prod2<-N || prod2>N)
						continue;
					//if(x==2 && cur<10) printf("i=%d s=%d p=%d cur=%lld tmp=%lld\n",i,sum,prod,cur,cur+abs(seq[i]-x));
					setmin(f[i+1][sum2+N][prod2+N], cur+abs(seq[i]-x));
				}
			}
		}
		//cout<<f[0][0][1]<<endl;
		//cout<<f[1][2][2]<<endl;
		//cout<<f[2][4][4]<<endl;
		forint(sum, -N, N)
			setmin(ans, f[seq.size()][sum+N][sum+N]);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1000000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(0, Arg1, minimumMoves(Arg0)); }
	void test_case_1() { int Arr0[] = {-1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(1, Arg1, minimumMoves(Arg0)); }
	void test_case_2() { int Arr0[] = {4,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; verify_case(2, Arg1, minimumMoves(Arg0)); }
	void test_case_3() { int Arr0[] = {17,95,-79}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 33LL; verify_case(3, Arg1, minimumMoves(Arg0)); }
	void test_case_4() { int Arr0[] = {10,9,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 21LL; verify_case(4, Arg1, minimumMoves(Arg0)); }
	void test_case_5() { int Arr0[] = {-2,-29,-13}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 38LL; verify_case(5, Arg1, minimumMoves(Arg0)); }
	void test_case_6() { int Arr0[] = {-7,-31,2,-14}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 48LL; verify_case(6, Arg1, minimumMoves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	PerfectSequences2 ___test;
	//___test.run_test(2);return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
