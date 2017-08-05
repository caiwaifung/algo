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

class CanidsSeesaw {
public:
    int score(VI a, VI b) {
        int r = 0, s = 0, t = 0;
        repn(i, sz(a)) {
            s += a[i], t += b[i];
            if(t > s) ++r;
        }
        return r;
    }
    vector<int> construct(vector<int> wolf, vector<int> fox, int k) {
        const int n = sz(wolf);
        VI ans;
        VB used(n, false);
        repn(i, n) {
            bool found = false;
            repn(cur, n) if(!used[cur]) {
                VI t1;
                for(int p : ans) t1.pb(fox[p]);
                t1.pb(fox[cur]);
                repn(p, n) if(p != cur && !used[p]) t1.pb(fox[p]);
                VI t2 = t1;
                sort(t1.begin() + i + 1, t1.end());
                sort(t2.begin() + i + 1, t2.end(), greater<int>());
                //cout << t1 << score(wolf, t1) << endl;
                //cout << t2 << score(wolf, t2) << endl;
                //cout << endl;
                if(score(wolf, t1) <= k && score(wolf, t2) >= k) {
                    used[cur] = true, found = true, ans.pb(cur);
                    break;
                }
            }
            if(!found) return {};
        }
        return ans;
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
    void verify_case(int Case, const vector<int>& Expected,
                     const vector<int>& Received) {
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
        int Arr0[] = {3, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {4, 2};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 1;
        int Arr3[] = {1, 0};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(0, Arg3, construct(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        int Arr0[] = {1, 3};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {4, 2};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 1;
        int Arr3[] = {};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(1, Arg3, construct(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        int Arr0[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 100, 1, 100, 1, 100, 1, 100, 1, 100};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 7;
        int Arr3[] = {0, 2, 4, 1, 6, 3, 5, 7, 9, 8};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(2, Arg3, construct(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        int Arr0[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 100, 1, 100, 1, 100, 1, 100, 1, 100};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 4;
        int Arr3[] = {};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(3, Arg3, construct(Arg0, Arg1, Arg2));
    }
    void test_case_4() {
        int Arr0[] = {2};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arg2 = 0;
        int Arr3[] = {0};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(4, Arg3, construct(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    CanidsSeesaw ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
