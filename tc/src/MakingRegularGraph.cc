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
#define len(a) static_cast<int>((a).size())
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
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) { os << "["; repn(i, len(v)) { if(i) os << ", "; os << v[i]; } return os << "]"; }
template <class T> bool setmax(T& _a, T _b) { if(_a < _b) { _a = _b; return true; } return false; }
template <class T> bool setmin(T& _a, T _b) { if(_b < _a) { _a = _b; return true; } return false; }
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }
int read_int() { int x; scanf("%d", &x); return x; }
LL read_ll() { LL x; scanf("%lld", &x); return x; }
string read_string() { string s; cin >> s; return s; }
VI read_vi(int n = -1) { if (n < 0) scanf("%d", &n); VI a(n); repn(i, n) scanf("%d", &a[i]); return a; }
VL read_vl(int n = -1) { if (n < 0) scanf("%d", &n); VL a(n); repn(i, n) scanf("%lld", &a[i]); return a; }
VD read_vd(int n = -1) { if (n < 0) scanf("%d", &n); VD a(n); repn(i, n) scanf("%lf", &a[i]); return a; }
VPI read_vpi(int n = -1) { if (n < 0) scanf("%d", &n); VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se); return a; }
VPL read_vpl(int n = -1) { if (n < 0) scanf("%d", &n); VPL a(n); repn(i, n) scanf("%lld%lld", &a[i].fi,&a[i].se); return a; }
VPD read_vpd(int n = -1) { if (n < 0) scanf("%d", &n); VPD a(n); repn(i, n) scanf("%lf%lf", &a[i].fi,&a[i].se); return a; }
inline LL powmod(LL a, LL b, LL m) { LL r = 1; for(; b > 0; b >>= 1, a = a * a % m) { if(b & 1) r = r * a % m; } return r; }
#define IN read_int()
// clang-format on
// }}}

class MakingRegularGraph {
  public:
    vector<int> addEdges(int n, vector<int> x, vector<int> y) {
        VVI es(n);
        repn(i, len(x)) { es[x[i]].pb(y[i]), es[y[i]].pb(x[i]); }
        VI pair(n, -3), size(n, 0);
        int r = 0;
        repn(i, n) if (pair[i] == -3) {
            if (len(es[i]) == 0) {
                pair[i] = i, size[i] = 1, ++r;
            } else if (len(es[i]) == 2) {
                pair[i] = -2;
            } else {
                int cur = es[i][0], pre = i, cnt = 2;
                while (len(es[cur]) > 1) {
                    int tmp = (es[cur][0] == pre ? es[cur][1] : es[cur][0]);
                    pre = cur, cur = tmp, ++cnt;
                }
                pair[i] = cur, pair[cur] = i;
                size[i] = size[cur] = cnt;
                r += cnt;
            }
        }
        if (r > 0 && r < 3) return {-1};
        VI ans;
        repn(i, n) replr(j, i + 1, n) {
            if (pair[i] == -2 || pair[j] == -2) {
                continue;
            }
            if (pair[i] == j) {
                if (size[i] < 3 || (r - size[i] > 0 && r - size[i] < 3)) {
                    continue;
                }
                r -= size[i];
                pair[i] = pair[j] = -2;
            } else {
                int i2 = pair[i], j2 = pair[j];
                pair[i2] = j2, pair[j2] = i2;
                size[i2] = size[j2] = size[i] + size[j];
                if (i2 != i) pair[i] = -2;
                if (j2 != j) pair[j] = -2;
            }
            ans.pb(i), ans.pb(j);
        }
        return ans;
    }

    // {{{

    // BEGIN CUT HERE
  public:
    void run_test(int Case) {
        if ((Case == -1) || (Case == 0)) test_case_0();
        if ((Case == -1) || (Case == 1)) test_case_1();
        if ((Case == -1) || (Case == 2)) test_case_2();
        if ((Case == -1) || (Case == 3)) test_case_3();
        if ((Case == -1) || (Case == 4)) test_case_4();
    }

  private:
    template <typename T> string print_array(const vector<T>& V) {
        ostringstream os;
        os << "{ ";
        for (typename vector<T>::const_iterator iter = V.begin();
             iter != V.end(); ++iter)
            os << '\"' << *iter << "\",";
        os << " }";
        return os.str();
    }
    void verify_case(int Case, const vector<int>& Expected,
                     const vector<int>& Received) {
        cerr << "Test Case #" << Case << "...";
        if (Expected == Received)
            cerr << "PASSED" << endl;
        else {
            cerr << "FAILED" << endl;
            cerr << "\tExpected: " << print_array(Expected) << endl;
            cerr << "\tReceived: " << print_array(Received) << endl;
        }
    }
    void test_case_0() {
        int Arg0 = 6;
        int Arr1[] = {0, 2};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {2, 3};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {0, 1, 1, 4, 3, 5, 4, 5};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(0, Arg3, addEdges(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        int Arg0 = 4;
        int Arr1[] = {1, 2, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {2, 3, 3};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {-1};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(1, Arg3, addEdges(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        int Arg0 = 3;
        int Arr1[] = {};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {0, 1, 0, 2, 1, 2};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(2, Arg3, addEdges(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        int Arg0 = 5;
        int Arr1[] = {0};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {4};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {0, 1, 1, 2, 2, 3, 3, 4};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(3, Arg3, addEdges(Arg0, Arg1, Arg2));
    }
    void test_case_4() {
        int Arg0 = 5;
        int Arr1[] = {2};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {3};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arr3[] = {0, 1, 0, 2, 1, 4, 3, 4};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(4, Arg3, addEdges(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    MakingRegularGraph ___test;
    cout << ___test.addEdges(4, {0, 1}, {2, 2}) << endl;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
