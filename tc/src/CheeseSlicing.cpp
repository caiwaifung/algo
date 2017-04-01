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

int f[110][110][110];

class CheeseSlicing {
public:
    int limit;

    int go(int a, int b, int c) {
        if(a < b) swap(a, b);
        if(a < c) swap(a, c);
        if(b < c) swap(b, c);
        int& ans = f[a][b][c];
        if(ans >= 0) return ans;
        ans = 0;
        if(c >= limit) ans = a * b;
        rep(i, 1, a - 1) setmax(ans, go(i, b, c) + go(a - i, b, c));
        rep(i, 1, b - 1) setmax(ans, go(a, i, c) + go(a, b - i, c));
        rep(i, 1, c - 1) setmax(ans, go(a, b, i) + go(a, b, c - i));
        return ans;
    }

    int totalArea(int A, int B, int C, int S) {
        limit = S;
        fillchar(f, 0xff);
        return go(A, B, C);
    }

    // {{{

    // BEGIN CUT HERE
public:
    void run_test(int Case) {
        if((Case == -1) || (Case == 0)) test_case_0();
        if((Case == -1) || (Case == 1)) test_case_1();
        if((Case == -1) || (Case == 2)) test_case_2();
        if((Case == -1) || (Case == 3)) test_case_3();
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
        int Arg0 = 1;
        int Arg1 = 3;
        int Arg2 = 3;
        int Arg3 = 2;
        int Arg4 = 0;
        verify_case(0, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_1() {
        int Arg0 = 5;
        int Arg1 = 3;
        int Arg2 = 5;
        int Arg3 = 3;
        int Arg4 = 25;
        verify_case(1, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_2() {
        int Arg0 = 5;
        int Arg1 = 5;
        int Arg2 = 5;
        int Arg3 = 2;
        int Arg4 = 58;
        verify_case(2, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3));
    }
    void test_case_3() {
        int Arg0 = 49;
        int Arg1 = 92;
        int Arg2 = 20;
        int Arg3 = 3;
        int Arg4 = 30045;
        verify_case(3, Arg4, totalArea(Arg0, Arg1, Arg2, Arg3));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    CheeseSlicing ___test;
    cout<<___test.totalArea(11,11,11,10)<<endl;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
