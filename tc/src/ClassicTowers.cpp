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

class ClassicTowers {
public:
    string solve(int x, int y, int z, char cx, char cy, char cz, LL k) {
        if(x == 0) return "";
        --x;
        if(k >= (1ll << (x + y + z))) return "";
        int s = x + y + z;
        static int f[55][55][55];
        fillchar(f, -1);
        f[0][0][0] = 0;
        rep(cur, 1, s) rep(a, 0, cur) rep(b, 0, cur - a) {
            int c = cur - a - b;
            if(k & (1ll << (cur - 1))) {
                if(b > 0 && f[c][a][b - 1] >= 0) f[a][b][c] = 2;
                if(c > 0 && f[b][a][c - 1] >= 0) f[a][b][c] = 3;
            } else {
                if(a > 0 && f[a - 1][b][c] >= 0) f[a][b][c] = 1;
            }
        }
        if(f[x][y][z] < 0) return "";
        string ans;
        ans += cx;
        while(x > 0 || y > 0 || z > 0) {
            assert(f[x][y][z] > 0);
            if(f[x][y][z] == 1) {
                ans.pb(cx), --x;
            } else if(f[x][y][z] == 2) {
                ans.pb(cy), --y;
                auto x2 = z, y2 = x, z2 = y;
                auto cx2 = cz, cy2 = cx, cz2 = cy;
                x = x2, y = y2, z = z2, cx = cx2, cy = cy2, cz = cz2;
            } else {
                ans.pb(cz), --z;
                auto x2 = y, y2 = x, z2 = z;
                auto cx2 = cy, cy2 = cx, cz2 = cz;
                x = x2, y = y2, z = z2, cx = cx2, cy = cy2, cz = cz2;
            }
        }
        reverse(all(ans));
        return ans;
    }

    string findTowers(long long k, vector<int> count) {
        int x = count[0], y = count[1], z = count[2];
        string ans = solve(x, y, z, 'A', 'B', 'C', k);
        if(ans.empty()) ans = solve(y, z, x, 'B', 'C', 'A', k);
        if(ans.empty()) ans = solve(z, x, y, 'C', 'A', 'B', k);
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
    void verify_case(int Case, const string& Expected, const string& Received) {
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
        long long Arg0 = 4LL;
        int Arr1[] = {1, 1, 2};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arg2 = "CCAB";
        verify_case(0, Arg2, findTowers(Arg0, Arg1));
    }
    void test_case_1() {
        long long Arg0 = 0LL;
        int Arr1[] = {0, 0, 50};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arg2 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
        verify_case(1, Arg2, findTowers(Arg0, Arg1));
    }
    void test_case_2() {
        long long Arg0 = 0LL;
        int Arr1[] = {10, 20, 20};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arg2 = "";
        verify_case(2, Arg2, findTowers(Arg0, Arg1));
    }
    void test_case_3() {
        long long Arg0 = 123456123456123LL;
        int Arr1[] = {10, 10, 30};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arg2 = "CCACCCACCABACCABBACCCBBCCBCCCBACCCCABBACCCCCACBCCC";
        verify_case(3, Arg2, findTowers(Arg0, Arg1));
    }
    void test_case_4() {
        long long Arg0 = 314159265358979LL;
        int Arr1[] = {15, 16, 17};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        string Arg2 = "";
        verify_case(4, Arg2, findTowers(Arg0, Arg1));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    ClassicTowers ___test;
    ___test.run_test(0);
    return 0;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
