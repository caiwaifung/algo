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

class SubtreeSumHash {
    LL pow(LL a, LL b) {
        LL r = 1;
        for(; b > 0; b >>= 1, a = a * a % MOD) {
            if(b & 1) r = r * a % MOD;
        }
        return r;
    }

    vector<VI> es;
    vector<LL> ws;
    int n;

    vector<LL> f;
    LL ans;

    void dfs(int x, int fa) {
        f[x] = ws[x];
        for(int y : es[x]) {
            if(y != fa) {
                dfs(y, x);
                (f[x] *= f[y]) %= MOD;
            }
        }
        (ans += f[x]) %= MOD;
        (++f[x]) %= MOD;
    }

public:
    int count(vector<int> weight, vector<int> p, int x) {
        es.clear(), ws.clear(), f.clear();
        n = sz(weight);
        ws.resize(n);
        repn(i, n) ws[i] = pow(x, weight[i]);
        es.resize(n);
        repn(i, sz(p)) es[i + 1].pb(p[i]), es[p[i]].pb(i + 1);

        f.resize(n);
        ans = 0;
        dfs(0, -1);
        return int((ans % MOD + MOD) % MOD);
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
        int Arr0[] = {1, 2, 3};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {0, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 10;
        int Arg3 = 1102110;
        verify_case(0, Arg3, count(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        int Arr0[] = {123456789, 987654321, 111111111, 999999999};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {0, 0, 0};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 1;
        int Arg3 = 11;
        verify_case(1, Arg3, count(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        int Arr0[] = {10};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 10;
        int Arg3 = 999999937;
        verify_case(2, Arg3, count(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        int Arr0[] = {3, 7, 6, 8, 9, 4, 2, 1, 5, 6, 7, 8, 9, 6, 1, 2, 3, 5};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {0, 0, 0, 3, 1, 1, 2, 0, 0, 3, 7, 8, 9, 0, 0, 4, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 987654321;
        int Arg3 = 46327623;
        verify_case(3, Arg3, count(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    SubtreeSumHash ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
