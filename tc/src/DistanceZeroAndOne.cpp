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

class DistanceZeroAndOne {
public:
    vector<string> construct(vector<int> dist0, vector<int> dist1) {
        const int n = sz(dist0);
        vector<VI> g(n, VI(n, 1 << 20));
        repn(i, n) g[i][i] = 0;
        repn(i, n) repn(j, n) if(i != j) {
            if(abs(dist0[i] - dist0[j]) <= 1 && abs(dist1[i] - dist1[j]) <= 1) {
                g[i][j] = 1;
            }
        }
        repn(k, n) repn(i, n) repn(j, n) setmin(g[i][j], g[i][k] + g[k][j]);
        repn(i, n) {
            if(g[0][i] != dist0[i]) return VS();
            if(g[1][i] != dist1[i]) return VS();
        }
        VS r(n, string(n, 'N'));
        repn(i, n) repn(j, n) if(g[i][j] == 1) r[i][j] = 'Y';
        return r;
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
    void verify_case(int Case, const vector<string>& Expected,
                     const vector<string>& Received) {
        cerr << "Test Case #" << Case << "...";
        if(Expected == Received)
            cerr << "PASSED" << endl;
        else {
            cerr << "FAILED" << endl;
            cerr << "\tExpected: " << print_array(Expected) << endl;
            cerr << "\tReceived: " << print_array(Received) << endl;
        }
    }
    void test_case_0() {
        int Arr0[] = {0, 2, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {2, 0, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arr2[] = {"NNY", "NNY", "YYN"};
        vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(0, Arg2, construct(Arg0, Arg1));
    }
    void test_case_1() {
        int Arr0[] = {0, 2, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 0, 2};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arr2[] = {};
        vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(1, Arg2, construct(Arg0, Arg1));
    }
    void test_case_2() {
        int Arr0[] = {3, 1, 1, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 0, 1, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arr2[] = {};
        vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(2, Arg2, construct(Arg0, Arg1));
    }
    void test_case_3() {
        int Arr0[] = {0, 1, 1, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 0, 1, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arr2[] = {"NYYY", "YNYY", "YYNN", "YYNN"};
        vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(3, Arg2, construct(Arg0, Arg1));
    }
    void test_case_4() {
        int Arr0[] = {0, 3, 1, 2, 2, 3, 4, 4};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {3, 0, 2, 1, 2, 3, 4, 4};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arr2[] = {"NNYNNNNN", "NNNYNNNN", "YNNYYNNN", "NYYNYNNN",
                         "NNYYNYNN", "NNNNYNYY", "NNNNNYNN", "NNNNNYNN"};
        vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(4, Arg2, construct(Arg0, Arg1));
    }
    void test_case_5() {
        int Arr0[] = {0, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 0};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arr2[] = {"NY", "YN"};
        vector<string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(5, Arg2, construct(Arg0, Arg1));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    DistanceZeroAndOne ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
