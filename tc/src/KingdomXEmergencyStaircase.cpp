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

const int n=50+12;
const int MAXN=n+2;
const int MAXW=12;


int cost[MAXW];

class KingdomXEmergencyStaircase {

	struct Side {
		int emer[MAXN];
		LL memo[MAXN][MAXN][MAXN][MAXW];
		Side(string s) {
			fillchar(emer, 0);
			forn(i, s.size()) if(s[size_t(i)]=='Y')
				emer[i+1]=1;
			forint(i, 1, n) emer[i]+=emer[i-1];

			fillchar(memo, 0xff);
		}
		int countEmer(int i, int j) {
			if(i==j) return 0;
			return emer[j-1]-emer[i];
		}
		LL floor(int i) {
			if(countEmer(0, i)==0)
				return 0;
			LL ans=1LL<<60;
			forint(j, 0, i-1)
				if(countEmer(0, j)==0)
					setmin(ans, cost[i-j]+cal(j,i,0));
			return ans;
		}
		LL cal(int i, int j, int d) {
			return cal2(i, j, j, d);
		}
		LL cal2(int i, int j, int p, int d) {
			LL &ans=memo[i][j][p][d];
			if(ans>=0) return ans;
			if(countEmer(i, p)==0)
				return ans=0;

			ans=1LL<<60;

			forint(d2, 0, d-1)
				setmin(ans, cost[j-i]+cal2(i,j,p,d2));
			forint(k, i+1, p-1)
				setmin(ans, cost[j-k]+cal2(k,j,p,0)+cal2(i,j,k,d));

			forint(k, i+1, p-1)
				setmin(ans, cost[d+(k-i)]+cal(i,k,d)+cal2(k,j,p,d+(k-i)));
			forint(k, p, j-1)
				setmin(ans, cost[d+(p-i)]+cal2(i,k,p,d));
			return ans;
		}
	};
public:
	long long determineCost(string leftBuilding, string rightBuilding, vector <int> _cost) {
		int w=(int)_cost.size();
		forint(i, 1, w) cost[i]=_cost[size_t(i-1)];
		Side *ls=new Side(leftBuilding);
		Side *rs=new Side(rightBuilding);

		LL f[MAXN][MAXN];
		LL ans=1LL<<60;
		fillchar(f, 50);
		setmin(f[0][w/2], cost[w]+rs->floor(w/2));
		setmin(f[w/2][0], cost[w]+ls->floor(w/2));
		forint(i, 0, n) forint(j, 0, n) {
			if(abs(i-j)>w/2) continue; // impossible
			if(ls->countEmer(i, n)==0 && rs->countEmer(j, n)==0)
				setmin(ans, f[i][j]);
			forint(k, i+1, min(j+w/2,n))
				setmin(f[k][j], f[i][j]+cost[k+w/2-j]+ls->cal(i, k, i+w/2-j));
			forint(k, j+1, min(i+w/2,n))
				setmin(f[i][k], f[i][j]+cost[k+w/2-i]+rs->cal(j, k, j+w/2-i));
		}
		//printf("f[4][2]=%lld\n",f[4][2]);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNYY"; string Arg1 = "NNNY"; int Arr2[] = {10, 40, 18, 25}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 98LL; verify_case(0, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "N"; string Arg1 = "Y"; int Arr2[] = {1, 1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 1000LL; verify_case(1, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "NNNNNNNY"; string Arg1 = "NNNNNNNY"; int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 17LL; verify_case(2, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN"; string Arg1 = "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNY"; int Arr2[] = {800000000,800000000,800000000,800000000,800000000,800000000,800000000,800000000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 6400000000LL; verify_case(3, Arg3, determineCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "NNY"; string Arg1 = "NNYYY"; int Arr2[] = {10000, 10, 40, 10000, 80, 80}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 220LL; verify_case(4, Arg3, determineCost(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	KingdomXEmergencyStaircase ___test;
	//___test.run_test(0); return 0;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
