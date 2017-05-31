#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
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

// {{{
// clang-format off
#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for (int i = int(a); i <= int(b); ++i)
#define irep(i, a, b) for (int i = int(a); i >= int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define popcount __builtin_popcount
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<double> VD;
typedef vector<bool> VB;
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
typedef vector<PDD> VPD;
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef vector<VD> VVD;
typedef vector<VB> VVB;
typedef vector<VS> VVS;
typedef vector<VPI> VVPI;
typedef vector<VPL> VVPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
// clang-format on
// }}}

class NAddOdd {
public:
    unordered_map<LL, LL> m;
    int k;

    LL go(LL n) {
        if(n <= k) return 0;
        if(m.count(n)) return m[n];
        LL ans = 0;
        ans += go(n / 2) + n / 2 - (k + 1) / 2 + 1;
        if(n >= k + 2) {
            ans += go((n - 1) / 2 + (k + 1) / 2) +
                   2 * ((n - 1) / 2 - (k + 1) / 2 + 1);
        }
        return m[n] = ans;
    }

    long long solve(long long L, long long R, int _K) {
        m.clear();
        k = _K;
        return go(R) - go(L - 1);
    }
    // {{{

    // BEGIN CUT HERE
public:
    void run_test(int Case) {
        if((Case == -1) || (Case == 0)) test_case_0();
        if((Case == -1) || (Case == 1)) test_case_1();
        if((Case == -1) || (Case == 2)) test_case_2();
        if((Case == -1) || (Case == 3)) test_case_3();
        if((Case == -1) || (Case == 4)) test_case_4();
    }

private:
    template <typename T> string print_array(const vector<T>& V) {
        ostringstream os;
        os << "{ ";
        for(typename vector<T>::const_iterator iter = V.begin();
            iter != V.end(); ++iter)
            os << '\"' << *iter << "\",";
        os << " }";
        return os.str();
    }
    void verify_case(int Case, const long long& Expected,
                     const long long& Received) {
        cerr << "Test Case #" << Case << "...";
        if(Expected == Received)
            cerr << "PASSED" << endl;
        else {
            cerr << "FAILED" << endl;
            cerr << "\tExpected: \"" << Expected << '\"' << endl;
            cerr << "\tReceived: \"" << Received << '\"' << endl;
        }
    }
    void test_case_0() {
        long long Arg0 = 5LL;
        long long Arg1 = 5LL;
        int Arg2 = 1;
        long long Arg3 = 5LL;
        verify_case(0, Arg3, solve(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        long long Arg0 = 1LL;
        long long Arg1 = 99999LL;
        int Arg2 = 99999;
        long long Arg3 = 0LL;
        verify_case(1, Arg3, solve(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        long long Arg0 = 16LL;
        long long Arg1 = 17LL;
        int Arg2 = 3;
        long long Arg3 = 9LL;
        verify_case(2, Arg3, solve(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        long long Arg0 = 3LL;
        long long Arg1 = 7LL;
        int Arg2 = 5;
        long long Arg3 = 4LL;
        verify_case(3, Arg3, solve(Arg0, Arg1, Arg2));
    }
    void test_case_4() {
        long long Arg0 = 1645805087361625LL;
        long long Arg1 = 9060129311830846LL;
        int Arg2 = 74935;
        long long Arg3 = 421014795656548226LL;
        verify_case(4, Arg3, solve(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    NAddOdd ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
