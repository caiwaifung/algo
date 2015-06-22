#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

class Bitwisdom {
public:
    double e2(VI p) {
        /*
        vector<double> pr(p.size()); int n=(int)p.size();
        repn(i, n) pr[i]=p[i]/100.;
        double ans=0;
        repn(start, n) {
            double cs=(start==0?1:2);
            double cp=(start==0?1:(1-pr[start-1]));
            for(int cur=start; cur<n && cp>0; ++cur) {
                cp*=pr[cur];
                if(cur==n-1) ans+=cp;
                else ans+=cp*(1-pr[cur+1])*cs;
            }
        }
        */
        double dp[355][355][2]; fillchar(dp, 0);
        int n=(int)p.size();
        dp[0][0][1]=p[0]/100.;
        dp[0][0][0]=1-dp[0][0][1];
        rep(i, 1, n-1) {
            double pp=p[i]/100., qq=1-pp;
            repn(j, i) {
                dp[i][j][0]+=dp[i-1][j][0]*qq;
                dp[i][j][1]+=dp[i-1][j][1]*pp;
                dp[i][j+1][0]+=dp[i-1][j][1]*qq;
                dp[i][j+1][1]+=dp[i-1][j][0]*pp;
            }
        }
        double ans=0;
        repn(i, n) ans+=i*(dp[n-1][i][0]+dp[n-1][i][1]);
        double t=1; repn(i, n) t*=p[i]/100.;
        ans+=t;
        return ans;
    }
    double expectedActions(vector <int> p) {
        double ans=0;
        double p1=p[0]/100., p0=1.-p1;
        rep(i, 1, p.size()-1) {
            double q1=p[i]/100., q0=1.-q1;
            ans+=q1*p0+q0*p1;
            p1=q1, p0=q0;
        }
        double tmp=1;
        repn(i, p.size()) tmp*=p[i]/100.;
        ans+=tmp;
        return (double)(ans);
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.0; verify_case(0, Arg1, expectedActions(Arg0)); }
	void test_case_1() { int Arr0[] = {50, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 0.75; verify_case(1, Arg1, expectedActions(Arg0)); }
	void test_case_2() { int Arr0[] = {0, 40, 50, 60}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 1.4; verify_case(2, Arg1, expectedActions(Arg0)); }
	void test_case_3() { int Arr0[] = {37, 63, 23, 94, 12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); double Arg1 = 2.6820475464; verify_case(3, Arg1, expectedActions(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    Bitwisdom ___test;
    while(1) {
        VI p; repn(i, 10) p.pb(rand()%101);
        double v1=___test.expectedActions(p);
        double v2=___test.e2(p);
        printf("%.9lf %.9lf\n",v1-v2, v1);
        assert(fabs(v1-v2)<1e-7);
    }
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
