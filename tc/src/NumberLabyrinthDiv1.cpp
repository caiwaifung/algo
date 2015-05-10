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

const LL MOD=LL(1e9)+9;
const int MAXL=1000000;

class NumberLabyrinthDiv1 {
public:
	int ax[44], ay[44], hop[44];
	int n;

	int find(int x, int y) {
		forint(i, 1, n)
			if(ax[i]==x && ay[i]==y)
				return i;
		return 0;
	}

	LL walk(int x, int y, int k) {
		static bool flag=false;
		static LL C[12][12];
		static int wf[MAXL+10][12];
		if(!flag) {
			flag=true;
			static int s[MAXL+10];

			fillchar(wf, 0);
			wf[0][0]=1;
			fillchar(s, 0);
			forint(i, 0, MAXL) s[i]=1;
			forint(k, 1, 10) {
				forint(i, 1, MAXL) wf[i][k]=s[i-1];
				s[0]=0;
				forint(i, 1, MAXL) s[i]=(s[i-1]+wf[i][k])%MOD;
			}
			forint(i, 0, 10) C[i][0]=C[i][i]=1;
			forint(i, 1, 10) forint(j, 1, i-1) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
		}
		LL t=0;
		forint(i, 0, k) {
			int kx=i, ky=k-i;
		//printf("walk i=%d/%d  x=%d y=%d kx=%d ky=%d\n",i,k,x,y,kx,ky);
			LL ans=C[k][i];
			(ans*=(LL)wf[x][kx]) %=MOD;
			(ans*=(LL)wf[y][ky]) %=MOD;
			(t+=ans)%=MOD;
		//printf("walk i=%d/%d end\n",i,k);
		}
		return t;
	}

	int jump_lx, jump_ly;
	LL jmp[44][12];
	
	void jump_run(int x, int y) { // call: N
		if(x==jump_lx && y==jump_ly)
			return;
		jump_lx=x, jump_ly=y;
		forint(i, 1, n) forint(k, 0, 10) {
			if(ax[i]<x || ay[i]<y) {
				jmp[i][k]=0;
				continue;
			}
			LL ans=walk(ax[i]-x, ay[i]-y, k);
			//cout<<"jmp["<<i<<","<<k<<"]: ans="<<ans<<" (x="<<ax[i]-x<<", y="<<ay[i]-y<<")"<<endl;
			forint(j, 1, i-1) {
				if(ax[j]>ax[i] || ay[j]>ay[i]) continue;
				if(ax[j]<x || ay[j]<y) continue;
				forint(k2, 0, k) {
					LL tmp=jmp[j][k2];
					(tmp*=walk(ax[i]-ax[j], ay[i]-ay[j], k-k2)) %=MOD;
					ans=(ans-tmp+MOD)%MOD;
				}
			}
			//cout<<"jmp["<<i<<","<<k<<"]="<<ans<<endl;
			jmp[i][k]=ans;
		}
	}
	LL jump(int x, int y, int i, int k) {
		int x2=ax[i], y2=ay[i];
		if(x>x2 || y>y2) return 0;
		jump_run(x, y);
		return jmp[i][k];
	}

	LL f[44][12];

	int getNumberOfPaths(vector <int> X, vector <int> Y, vector <int> val, int xFinish, int yFinish, int K) {
		n=X.size();
		forint(i, 1, n) {
			ax[i]=X[size_t(i-1)];
			ay[i]=Y[size_t(i-1)];
			hop[i]=val[size_t(i-1)];
		}
		forint(i, 1, n) forint(j, i+1, n)
			if(ax[i]>ax[j] || (ax[i]==ax[j] && ay[i]>ay[j])) {
				swap(ax[i], ax[j]);
				swap(ay[i], ay[j]);
				swap(hop[i], hop[j]);
			}
		++n;
		ax[n]=xFinish;
		ay[n]=yFinish;
		//printf("#\n");

		jump_lx=jump_ly=-1;

		//printf("#\n");

		fillchar(f, 0);
		forint(i, 1, n) forint(k, 0, K)
			(f[i][k]+=jump(0, 0, i, k)) %=MOD;

		forint(i, 1, n) forn(tt, 2) forint(k, 0, K) {
			int x2=ax[i], y2=ay[i];
			if(tt) x2+=hop[i];
				else y2+=hop[i];
			int j=find(x2, y2);
			//if(i==n) printf("hop=%d x2=%d y2=%d j=%d\n",hop[i],x2,y2,j);
			if(j>0)
				(f[j][k]+=f[i][k]) %=MOD;
			else {
				forint(j, i+1, n) forint(k2, k, K)
					(f[j][k2]+=f[i][k]*jump(x2, y2, j, k2-k)) %=MOD;
			}
		}

		LL ans=0;
		forint(k, 0, K) {
			(ans+=f[n][k]) %=MOD;
		}

		return int(ans);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) {
		if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; int Arg5 = 2; int Arg6 = 2; verify_case(0, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arr0[] = {}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; int Arg5 = 3; int Arg6 = 14; verify_case(1, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arr0[] = {2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; int Arg5 = 3; int Arg6 = 18; verify_case(2, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arr0[] = {1, 3, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; int Arg4 = 5; int Arg5 = 4; int Arg6 = 210; verify_case(3, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arr0[] = {1, 19, 20, 21, 21, 21, 20, 19, 19}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 11, 11, 11, 10, 9, 9, 9, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 2, 2, 2, 2, 2, 2, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 20; int Arg4 = 10; int Arg5 = 4; int Arg6 = 1778; verify_case(4, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_5() { int Arr0[] = {13, 224, 77, 509, 1451, 43, 379, 142, 477}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1974, 375, 38, 783, 3, 1974, 1790, 1008, 2710}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {30, 1845, 360, 11, 837, 84, 210, 4, 6704}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 509; int Arg4 = 2011; int Arg5 = 10; int Arg6 = 196052726; verify_case(5, Arg6, getNumberOfPaths(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	NumberLabyrinthDiv1 ___test;
	/*
	___test.run_test(0);
	/*/
	___test.run_test(-1);
	//*/
	return 0;
}
// END CUT HERE
