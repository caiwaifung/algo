#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>
#include <sstream>
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

#define sz(a) ((a).size())
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
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

const int N=100;

struct Bipartite {
    bool a[N][N];
    int mx[N], my[N];
    bool vx[N], vy[N];
    int n;

    bool find(int i) {
        vx[i]=true;
        repn(j, n) if(a[i][j] && !vy[j]) {
            vy[j]=true;
            if(my[j]<0 || find(my[j])) {
                mx[i]=j, my[j]=i;
                return true;
            }
        }
        return false;
    }

    int maxmatch() {
        fillchar(mx, 0xff); fillchar(my, 0xff);
        int ans=0;
        repn(cur, n) {
            fillchar(vx, false); fillchar(vy, false);
            if(find(cur)) ++ans;
        }
        return ans;
    }

    void vc() {
        fillchar(vx, false); fillchar(vy, false);
        repn(i, n) if(mx[i]<0) {
            find(i);
        }
    }
};

class DancingForever {
public:
    vector<int> getStablePairs(string x) {
        static Bipartite b;
        b.n=int(sqrt(sz(x))+0.5);
        repn(i, b.n) repn(j, b.n) {
            b.a[i][j]=(x[i*b.n+j]=='Y');
        }
        VI ans;
        if(b.maxmatch()<b.n) {
            b.vc();
            repn(i, b.n) if(b.vy[i]) { ans.pb(b.my[i]); ans.pb(i); }
        } else {
            repn(i, b.n) { ans.pb(i); ans.pb(b.mx[i]); }
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "YYNNNYYNNNYYYNNY"; int Arr1[] = {0, 0, 1, 1, 2, 2, 3, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getStablePairs(Arg0)); }
	void test_case_1() { string Arg0 = "YNNNYYNNYYNNNNYY"; int Arr1[] = {1, 0, 2, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getStablePairs(Arg0)); }
	void test_case_2() { string Arg0 = "YNYYNYYNY"; int Arr1[] = {1, 0, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getStablePairs(Arg0)); }
	void test_case_3() { string Arg0 = "YYYNNYYYNNNNNYYNNNYYNNNYY"; int Arr1[] = {3, 3, 4, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getStablePairs(Arg0)); }
	void test_case_4() { string Arg0 = "Y"; int Arr1[] = {0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getStablePairs(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    DancingForever ___test;
    /*
       ___test.run_test(0);
    /*/
      ___test.run_test(-1);
    //*/
    return 0;
}
// END CUT HERE
