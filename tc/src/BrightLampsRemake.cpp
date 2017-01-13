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

class BrightLampsRemake {
public:
    int bitcnt(LL x) { return __builtin_popcountll(x); }

    vector<long long> maxAndCount(string _init, vector<string> _buttons) {
        int n = sz(_init);
        const auto parse = [&](string s) {
            LL r = 0;
            repn(i, n) if(s[i] == '1') r |= (1ll << i);
            return r;
        };
        const auto swap_bits = [](LL* x, int i, int j) {
            if(i == j) return;
            LL bi = ((*x) & (1ll << i)) > 0;
            LL bj = ((*x) & (1ll << j)) > 0;
            (*x) ^= (bi << i) ^ (bj << j);
            (*x) ^= (bi << j) ^ (bj << i);
        };
        LL init = parse(_init);
        VL vs(sz(_buttons));
        transform(all(_buttons), vs.begin(), parse);

        int num = 0;
        while(num < n && num < sz(vs)) {
            bool found = false;
            replr(i, num, sz(vs)) {
                replr(j, num, n) if(vs[i] & (1ll << j)) {
                    if(i != num) {
                        swap(vs[num], vs[i]);
                    }
                    if(j != num) {
                        swap_bits(&init, num, j);
                        for(LL& v : vs) swap_bits(&v, num, j);
                    }
                    found = true;
                    break;
                }
                if(found) break;
            }
            if(!found) break;
            assert((vs[num] & (1ll << num)) > 0);
            replr(i, num + 1, sz(vs)) if(vs[i] & (1ll << num)) {
                vs[i] ^= vs[num];
            }
            ++num;
        }
        LL free = sz(vs) - num;
        cout << n << " " << sz(vs) << " " << num << " " << free << endl;
        vs.erase(vs.begin() + num, vs.end());
        irepn(i, num) {
            assert((vs[i] & (1ll << i)) > 0);
            repn(j, i) if(vs[j] & (1ll << i)) { vs[j] ^= vs[i]; }
        }
        VL ans;
        if(sz(vs) <= 27) {
            ans = solve_small(n, vs, init);
        } else {
            ans = solve_large(n, vs, init);
        }
        ans[1] <<= free;
        return ans;
    }

    VL solve_small(int , VL vs, LL init) {
        int best = 0;
        LL cnt = 0;
        const function<void(int, LL)> dfs = [&](int i, LL cur) {
            if(i == sz(vs)) {
                int val = bitcnt(cur);
                if(setmax(best, val)) cnt = 0;
                if(best == val) ++cnt;
                return;
            }
            dfs(i + 1, cur);
            dfs(i + 1, cur ^ vs[i]);
        };
        dfs(0, init);
        return {best, cnt};
    }

    VL solve_large(int n, VL vs, LL init) {
        const auto update = [](LL& a, LL b) {
            constexpr LL MC = (1ll << 50) - 1;
            constexpr LL MV = ~MC;
            if((b & MV) > (a & MV)) {
                a = b;
            } else if((b & MV) == (a & MV)) {
                a += (b & MC);
            }
        };
        int m = n - sz(vs);
        printf("%d\n", 1 << m);
        vector<VL> f(2, VL(1 << m));
        int o1 = 0, o2 = 1;
        f[o1][0] = 1;
        repn(i, sz(vs)) {
            fill(all(f[o2]), 0);
            repn(s, 1 << m) {
                if(f[o1][s] == 0) continue;
                int contrib = int(vs[i] >> sz(vs));
                LL v0 = (init & (1ll << i)) > 0;
                update(f[o2][s], f[o1][s] + (v0 << 50));
                update(f[o2][s ^ contrib], f[o1][s] + ((1 - v0) << 50));
            }
            swap(o1, o2);
        }
        LL ans = 0;
        repn(s, 1 << m) {
            update(ans, f[o1][s] + ((LL)bitcnt(s ^ (init >> sz(vs))) << 50));
        }
        return {ans >> 50, ans & ((1ll << 50) - 1)};
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
    void verify_case(int Case, const vector<long long>& Expected,
                     const vector<long long>& Received) {
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
        string Arg0 = "0000";
        string Arr1[] = {"1010", "0100", "0001"};
        vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        long Arr2[] = {4, 1};
        vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(0, Arg2, maxAndCount(Arg0, Arg1));
    }
    void test_case_1() {
        string Arg0 = "1011";
        string Arr1[] = {"0000", "0000", "0000"};
        vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        long Arr2[] = {3, 8};
        vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(1, Arg2, maxAndCount(Arg0, Arg1));
    }
    void test_case_2() {
        string Arg0 = "00000";
        string Arr1[] = {"11000", "01100", "00110", "00011", "10001"};
        vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        long Arr2[] = {4, 10};
        vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(2, Arg2, maxAndCount(Arg0, Arg1));
    }
    void test_case_3() {
        string Arg0 = "10000";
        string Arr1[] = {"11000", "01100", "00110", "00011", "10001"};
        vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        long Arr2[] = {5, 2};
        vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(3, Arg2, maxAndCount(Arg0, Arg1));
    }
    void test_case_4() {
        string Arg0 = "0";
        string Arr1[] = {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                         "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                         "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                         "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                         "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};
        vector<string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        long Arr2[] = {0, 1125899906842624};
        vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        verify_case(4, Arg2, maxAndCount(Arg0, Arg1));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    BrightLampsRemake ___test;
    ___test.run_test(-1);
    cout << ___test.maxAndCount(
                "00101111001001010000100111010010100110001111100001",
                {"10001100000110101100001110000100110000000100100110",
                 "10110110010001100101001110100111100001011000010001",
                 "10111110101001000011010001100010110111110100011100",
                 "01111101011100101110000010001110010100100101101100",
                 "11101000010100001010101010011100101110110001001111",
                 "11000110000110100001101110001010110011100011110111",
                 "10011100011000101111100001011001100101001011110010",
                 "00101110011111101010111110101101110000010100010001",
                 "10001011101101010100000010110001000011000111000001",
                 "00000001101110100010011001101100001001101000001011",
                 "11001101101011101001010100111101101001110010001000",
                 "01010101010000101100001111001001000111101000001010",
                 "00011011010000000101101100000001100100110101000001",
                 "01001010111011011110010101011100100100111110010100",
                 "10001101001100110100100001110010111001001011111011",
                 "10110010011111101010001111001111010001010111101000",
                 "11100001110011100011001100100011101001110111011000",
                 "00001101110100011001001011001010010101110000011000",
                 "11010111110111001110101101010100001101000111011110",
                 "10100100000010000010011010100110110001101111111110",
                 "00011100000011001101001110010100001110001110111011",
                 "11011011000000101010111111110101110101001101011100",
                 "11100100100111001010100001010010011110110000100010",
                 "10101111001010000100001000011000010101010010010111",
                 "10010110011100011111101101011001001000100110010001",
                 "00111001100000110000100001100000110011000100010100",
                 "01111010000011110001111100110001101111001111110100",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000",
                 "00000000000000000000000000000000000000000000000000"})
         << endl;
    return 0;
}
// END CUT HERE
