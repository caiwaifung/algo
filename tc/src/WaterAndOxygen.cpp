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
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<double> VD;
typedef vector<string> VS;
typedef vector<PII> VPI;
typedef vector<PLL> VPL;
template <class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os << "(" << v.first << ", " << v.second << ")"; }
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, sz(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
// clang-format on
// }}}

class WaterAndOxygen {
public:
    double maxDays(int remainH2O, int remainO2, int costH2O, int costO2) {
        long double rH = remainH2O, rO = remainO2, cH = costH2O, cO = costO2;

        if(rH / cH < rO / cO) {
            return rH / cH;
        } else {
            return (rH + 2 * rO) / (cH + 2 * cO);
        }
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
    void verify_case(int Case, const double& Expected, const double& Received) {
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
        int Arg0 = 64;
        int Arg1 = 70;
        int Arg2 = 3;
        int Arg3 = 7;
        double Arg4 = 12.0;
        verify_case(0, Arg4, maxDays(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_1() {
        int Arg0 = 99;
        int Arg1 = 102;
        int Arg2 = 1;
        int Arg3 = 1;
        double Arg4 = 99.0;
        verify_case(1, Arg4, maxDays(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_2() {
        int Arg0 = 101;
        int Arg1 = 99;
        int Arg2 = 1;
        int Arg3 = 1;
        double Arg4 = 99.66666666666667;
        verify_case(2, Arg4, maxDays(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_3() {
        int Arg0 = 123456789;
        int Arg1 = 987654321;
        int Arg2 = 123;
        int Arg3 = 456;
        double Arg4 = 1003713.731707317;
        verify_case(3, Arg4, maxDays(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_4() {
        int Arg0 = 987654321;
        int Arg1 = 123456789;
        int Arg2 = 456;
        int Arg3 = 123;
        double Arg4 = 1758643.7307692308;
        verify_case(4, Arg4, maxDays(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_5() {
        int Arg0 = 0;
        int Arg1 = 0;
        int Arg2 = 13;
        int Arg3 = 27;
        double Arg4 = 0.0;
        verify_case(5, Arg4, maxDays(Arg0, Arg1, Arg2, Arg3));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    WaterAndOxygen ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
