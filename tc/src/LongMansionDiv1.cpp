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

class LongMansionDiv1 {
public:
    long long minimalTime(vector<int> t, int sX, int sY, int eX, int eY) {
        const int n = sz(t);
        VL a(n), b(n);
        a[sX] = t[sX];
        irep(i, sX - 1, 0) a[i] = a[i + 1] + t[i];
        rep(i, sX + 1, n - 1) a[i] = a[i - 1] + t[i];
        repn(i, n) {
            volatile int k = int(t[i] * abs(sY - eY));
            b[i] = a[i] + k;
        }
        rep(i, 1, n - 1) setmin(b[i], b[i - 1] + t[i]);
        irep(i, n - 2, 0) setmin(b[i], b[i + 1] + t[i]);
        return b[eX];
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
        int Arr0[] = {5, 3, 10};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 2;
        int Arg2 = 0;
        int Arg3 = 2;
        int Arg4 = 2;
        long long Arg5 = 29LL;
        verify_case(0, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_1() {
        int Arr0[] = {5, 3, 10};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 0;
        int Arg2 = 2;
        int Arg3 = 0;
        int Arg4 = 0;
        long long Arg5 = 15LL;
        verify_case(1, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_2() {
        int Arr0[] = {137, 200, 184, 243, 252, 113, 162};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 0;
        int Arg2 = 2;
        int Arg3 = 4;
        int Arg4 = 2;
        long long Arg5 = 1016LL;
        verify_case(2, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_3() {
        int Arr0[] = {995,  996, 1000, 997,  999,  1000, 997,  996, 1000, 996,
                      1000, 997, 999,  996,  1000, 998,  999,  995, 995,  998,
                      995,  998, 995,  997,  998,  996,  998,  996, 997,  1000,
                      998,  997, 995,  1000, 996,  997,  1000, 997, 997,  999,
                      998,  995, 999,  999,  1000, 1000, 998,  997, 995,  999};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 18;
        int Arg2 = 433156521;
        int Arg3 = 28;
        int Arg4 = 138238863;
        long long Arg5 = 293443080673LL;
        verify_case(3, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_4() {
        int Arr0[] = {1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 0;
        int Arg2 = 0;
        int Arg3 = 0;
        int Arg4 = 0;
        long long Arg5 = 1LL;
        verify_case(4, Arg5, minimalTime(Arg0, Arg1, Arg2, Arg3, Arg4));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    LongMansionDiv1 ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
