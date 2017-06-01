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

class PreInPost {
public:
    static constexpr int kPre = 0;
    static constexpr int kPost = 1;
    static constexpr int kIn = 2;
    int order_id(string o) {
        if(o == "pre") return kPre;
        if(o == "post") return kPost;
        if(o == "in") return kIn;
        return -1;
    }

    const VI kNo = {-1};
    VI s, a1, a2, where1, where2;

    VI cat(VI a, const VI& b) {
        if(a == kNo || b == kNo) return kNo;
        a.insert(a.end(), all(b));
        return a;
    }
    VI cat(const VI& a, const VI& b, const VI& c) { return cat(cat(a, b), c); }

    bool same_set(int p1, int p2, int len) {
        repn(i, len) {
            int j = where2[a1[p1 + i]];
            if(j < p2 && j >= p2 + len) return false;
        }
        return true;
    }

    unordered_map<LL, bool> mem;

    VI dfs(int e1, int p1, int e2, int p2, int len, int expand) {
        if(len == 0) return VI();
        if(!same_set(p1, p2, len)) return kNo;

        LL id = 0;
        id = id * 3 + e1, id = id * 3 + e2;
        id = id * 200 + p1, id = id * 200 + p2;
        id = id * 201 + len;
        if(mem.count(id)) {
            if(!expand) {
                return mem[id] ? VI() : kNo;
            } else {
                if(!mem[id]) return kNo;
            }
        }
        bool& ans = mem[id];
        ans = false;

        // cout << e1 << " " << p1 << " " << e2 << " " << p2 << " " << len <<
        // endl;

        int swapped = false;
        if(e1 > e2) swap(e1, e2), swap(p1, p2), swapped = true;
        const auto sa1 = [&](int p) { return swapped ? a2[p] : a1[p]; };
        const auto sa2 = [&](int p) { return swapped ? a1[p] : a2[p]; };
        // const auto sw1 = [&](int x) { return swapped ? where2[x] : where1[x];
        // };
        const auto sw2 = [&](int x) { return swapped ? where1[x] : where2[x]; };
        const auto sdfs = [&](int ex, int px, int ey, int py, int l, int exp) {
            if(swapped) {
                return dfs(ey, py, ex, px, l, exp);
            } else {
                return dfs(ex, px, ey, py, l, exp);
            }
        };

        if(e1 == kPre && e2 == kIn) {
            int x = sa1(p1), m = sw2(x) - p2;
            if(m < 0 || m >= len) return kNo;
            VI l, r;
            rep(op, 0, expand) {
                l = sdfs(s[0], p1 + 1, s[2], p2, m, op);
                if(l == kNo) return kNo;
                r = sdfs(s[1], p1 + m + 1, s[3], p2 + m + 1, len - m - 1, op);
                if(r == kNo) return kNo;
            }
            ans = true;
            return expand ? cat(l, r, {x}) : VI();
        } else if(e1 == kPost && e2 == kIn) {
            int x = sa1(p1 + len - 1), m = sw2(x) - p2;
            if(m < 0 || m >= len) return kNo;
            VI l, r;
            rep(op, 0, expand) {
                l = sdfs(s[4], p1, s[2], p2, m, op);
                if(l == kNo) return kNo;
                r = sdfs(s[5], p1 + m, s[3], p2 + m + 1, len - m - 1, op);
                if(r == kNo) return kNo;
            }
            ans = true;
            return expand ? cat({x}, l, r) : VI();
        } else {
            int x = sa1(p1);
            if(sa2(p2 + len - 1) != x) return kNo;
            repn(m, len) {
                bool ok = true;
                VI l, r;
                rep(op, 0, expand) {
                    l = sdfs(s[0], p1 + 1, s[4], p2, m, op);
                    if(l == kNo) {
                        ok = false;
                        break;
                    }
                    r = sdfs(s[1], p1 + 1 + m, s[5], p2 + m, len - m - 1, op);
                    if(r == kNo) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    ans = true;
                    return expand ? cat(l, {x}, r) : VI();
                }
            }
            return kNo;
        }

        return VI();
    }

    vector<int> findMissing(vector<string> _s, vector<int> _a1, vector<int> _a2,
                            string e1, string e2) {
        mem.clear();

        s.clear();
        for(const auto& o : _s) s.pb(order_id(o));
        a1 = _a1, a2 = _a2;
        assert(sz(a1) == sz(a2));
        where1.resize(sz(a1)), where2.resize(sz(a1));
        repn(i, sz(a1)) {
            --a1[i], --a2[i];
            where1[a1[i]] = where2[a2[i]] = i;
        }

        VI ans = dfs(order_id(e1), 0, order_id(e2), 0, sz(a1), 1);
        if(ans == kNo) ans = VI();
        for(int& x : ans) ++x;
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
        string Arr0[] = {"post", "in", "pre", "post", "in", "pre"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 2, 3, 4, 5};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {2, 4, 3, 5, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        string Arg3 = "pre";
        string Arg4 = "post";
        int Arr5[] = {2, 1, 3, 5, 4};
        vector<int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0])));
        verify_case(0, Arg5, findMissing(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_1() {
        string Arr0[] = {"post", "in", "pre", "post", "in", "pre"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {2, 1, 3, 5, 4};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {1, 2, 3, 4, 5};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        string Arg3 = "in";
        string Arg4 = "pre";
        int Arr5[] = {2, 4, 3, 5, 1};
        vector<int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0])));
        verify_case(1, Arg5, findMissing(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_2() {
        string Arr0[] = {"pre", "pre", "in", "in", "post", "post"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        string Arg3 = "post";
        string Arg4 = "pre";
        int Arr5[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        vector<int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0])));
        verify_case(2, Arg5, findMissing(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_3() {
        string Arr0[] = {"pre", "pre", "in", "in", "post", "post"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        string Arg3 = "post";
        string Arg4 = "in";
        int Arr5[] = {1};
        vector<int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0])));
        verify_case(3, Arg5, findMissing(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_4() {
        string Arr0[] = {"pre", "in", "post", "pre", "in", "post"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {9, 3, 4, 1, 6, 5, 2, 7, 8};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {3, 9, 1, 4, 2, 7, 8, 5, 6};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        string Arg3 = "in";
        string Arg4 = "post";
        int Arr5[] = {6, 1, 9, 3, 4, 5, 8, 7, 2};
        vector<int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0])));
        verify_case(4, Arg5, findMissing(Arg0, Arg1, Arg2, Arg3, Arg4));
    }
    void test_case_5() {
        string Arr0[] = {"pre", "in", "in", "post", "post", "pre"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 2, 3};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {2, 3, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        string Arg3 = "post";
        string Arg4 = "pre";
        int Arr5[] = {};
        vector<int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0])));
        verify_case(5, Arg5, findMissing(Arg0, Arg1, Arg2, Arg3, Arg4));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    PreInPost ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
