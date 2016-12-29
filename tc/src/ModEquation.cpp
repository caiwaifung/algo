#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
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
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const LL MOD=LL(1e9)+7;

LL inv(LL a) {
    LL b=MOD-2, r=1;
    for(; b>0; b>>=1, a=a*a%MOD)
        if(b&1) r=r*a%MOD;
    return r;
}

VL solve(int n, int p, int t, VI query) {
    static LL po[55], ipo[55];
    po[0]=ipo[0]=1;
    rep(i, 1, 50) {
        po[i]=po[i-1]*p%MOD;
        ipo[i]=inv(po[i]);
        //cout<<po[i]<<" "<<ipo[i]<<" "<<(po[i]*ipo[i]%MOD)<<endl;
    }
    static LL pick[55], ipick[55];
    rep(k, 0, t) {
        pick[k]=(k==t ? 1 : po[t-k-1]*(p-1)%MOD);
        ipick[k]=inv(pick[k]);
    }

    static LL f[55][55];
    fillchar(f, 0);
    f[0][0]=1;
    repn(i, n) rep(j, 0, t) {
        rep(k, 0, t) {
            (f[i+1][min(t,j+k)]+=f[i][j]*pick[k])%=MOD;
        }
    }
    //c:rep(j, 0, t) printf("f[%d,%d]=%lld\n",n,j,f[n][j]);

    VL ans;
    for(int q: query) {
        int k=t;
        while(q%po[k]!=0) --k;
        LL val=f[n][k]*ipick[k]%MOD;
        ans.pb(val);
    }
    return ans;
}

class ModEquation {
public:
    vector <int> count(int n, int K, vector <int> query) {
        VI ans(sz(query), 1);
        const auto apply=[&](VL tmp) {
            repn(i, sz(ans)) {
                LL v=LL(ans[i])*tmp[i]%MOD;
                ans[i]=int(v);
            }
        };
        for(int x=2; x*x<=K; ++x) {
            if(K%x==0) {
                int p=x, t=0;
                while(K%x==0) K/=x, ++t;
                apply(solve(n, p, t, query));
            }
        }
        if(K>1) {
            apply(solve(n, K, 1, query));
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arr2[] = {0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3, 1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 4; int Arr2[] = {0,1,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {8, 2, 4, 2 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 6; int Arr2[] = {4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2016 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 2; int Arr2[] = {0,0,0,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 1, 1, 1, 1, 1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    ModEquation ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
