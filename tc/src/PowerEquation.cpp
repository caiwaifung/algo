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

const LL MOD = LL(1e9) + 7;

class PowerEquation {
public:
    int count(int _n) {
        LL n = _n;
        unordered_set<LL> visited = {1};
        LL ans = n * n % MOD;
        for(LL t = 2; t * t <= n; ++t) {
            if(visited.count(t)) continue;
            int k = 0;
            for(LL cur = t; cur <= n; cur *= t) {
                visited.insert(cur);
                ++k;
            }
            rep(x, 1, k) rep(y, 1, k) {
                int g = gcd(x, y), x0 = x / g, y0 = y / g;
                LL tmp = n / max(x0, y0);
                (ans += tmp) %= MOD;
            }
        }
        (ans += (n - sz(visited)) * n) %= MOD;
        return int(ans);
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
    void verify_case(int Case, const int& Expected, const int& Received) {
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
        int Arg0 = 2;
        int Arg1 = 6;
        verify_case(0, Arg1, count(Arg0));
    }
    void test_case_1() {
        int Arg0 = 3;
        int Arg1 = 15;
        verify_case(1, Arg1, count(Arg0));
    }
    void test_case_2() {
        int Arg0 = 100;
        int Arg1 = 21620;
        verify_case(2, Arg1, count(Arg0));
    }
    void test_case_3() {
        int Arg0 = 22306;
        int Arg1 = 68467;
        verify_case(3, Arg1, count(Arg0));
    }
    void test_case_4() {
        int Arg0 = 1;
        int Arg1 = 1;
        verify_case(4, Arg1, count(Arg0));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    PowerEquation ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
