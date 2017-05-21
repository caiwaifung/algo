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

class FourLamps {
public:
    long long count(string init, int k) {
        VI b;
        repn(i, sz(init) - 1) b.pb(init[i] != init[i + 1]);
        VI ps;
        repn(i, sz(b) - 1) if(b[i] != b[i + 1]) ps.pb(i);
        if(ps.empty()) return 1;
        static LL f[55][55][2555];
        fillchar(f, 0);
        f[0][0][0] = 1;
        repn(i, sz(b) - 1) rep(j, 0, sz(ps)) rep(c, 0, 2500) {
            if(f[i][j][c] == 0) continue;
            f[i + 1][j][c] += f[i][j][c];
            if(j < sz(ps)) {
                f[i + 1][j + 1][c + abs(ps[j] - i)] += f[i][j][c];
            }
        }
        LL ans = 0;
        rep(c, 0, min(2500, k)) ans += f[sz(b) - 1][sz(ps)][c];
        return k == 1 ? ans * 2 - 1 : ans * 2;
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
        if((Case == -1) || (Case == 5)) test_case_5();
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
        string Arg0 = "0001";
        int Arg1 = 2;
        long long Arg2 = 4LL;
        verify_case(0, Arg2, count(Arg0, Arg1));
    }
    void test_case_1() {
        string Arg0 = "0001";
        int Arg1 = 1000000000;
        long long Arg2 = 4LL;
        verify_case(1, Arg2, count(Arg0, Arg1));
    }
    void test_case_2() {
        string Arg0 = "1010";
        int Arg1 = 100;
        long long Arg2 = 1LL;
        verify_case(2, Arg2, count(Arg0, Arg1));
    }
    void test_case_3() {
        string Arg0 = "000111";
        int Arg1 = 3;
        long long Arg2 = 12LL;
        verify_case(3, Arg2, count(Arg0, Arg1));
    }
    void test_case_4() {
        string Arg0 = "00000010000";
        int Arg1 = 5;
        long long Arg2 = 58LL;
        verify_case(4, Arg2, count(Arg0, Arg1));
    }
    void test_case_5() {
        string Arg0 = "10101100101010001011000100101000100001101";
        int Arg1 = 58;
        long long Arg2 = 100256132848LL;
        verify_case(5, Arg2, count(Arg0, Arg1));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    FourLamps ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
