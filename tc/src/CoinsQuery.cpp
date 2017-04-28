#include <algorithm>
#include <bitset>
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
int popcount_ll(LL x) { return __builtin_popcountll(x); }
int popcount(int x) { return __builtin_popcount(x); }
// clang-format on
// }}}

const int MOD = LL(1e9) + 7;
const int N = 100;
const int LOG = 30;

struct P {
    LL v = -1, c = 0;
    P() {}
    P(LL v, LL c) : v(v), c(c) {}

    static P one() { return P(0, 1); }
    P operator*(const P& b) const {
        if(v < 0 || b.v < 0) {
            return P();
        } else {
            return P(v + b.v, c * b.c % MOD);
        }
    }
    P operator+(const P& b) const {
        if(v == b.v) {
            LL t = c + b.c;
            if(t >= MOD) t -= MOD;
            return P(v, t);
        } else {
            return v > b.v ? *this : b;
        }
    }
    void operator+=(const P& b) { *this = *this + b; }
};

struct Mat {
    P a[N][N];
    int n, m;

    Mat(int n, int m) : n(n), m(m) {}
    void add(int i, int j, P val) { a[i][j] += val; }

    Mat operator*(const Mat& b) const {
        Mat c(n, b.m);
        assert(m == b.n);
        repn(i, n) repn(j, b.m) repn(k, m) { c.a[i][j] += a[i][k] * b.a[k][j]; }
        return c;
    }
};

ostream& operator<<(ostream& os, const P& p) {
    return os << "(" << p.c << ", " << p.v << ")";
}

class CoinsQuery {
public:
    vector<long long> query(vector<int> w, vector<int> v, vector<int> query) {
        vector<Mat> m(LOG, Mat(N, N));
        repn(i, sz(w)) m[0].add(0, w[i] - 1, P(v[i], 1));
        repn(i, N - 1) m[0].add(i + 1, i, P::one());
        replr(i, 1, LOG) m[i] = m[i - 1] * m[i - 1];

        VL ans;
        for(const auto& n : query) {
            Mat a(N, 1);
            a.add(0, 0, P::one());
            repn(i, LOG) if(n & (1 << i)) { a = m[i] * a; }
            if(a.a[0][0].v >= 0) {
                ans.pb(a.a[0][0].v), ans.pb(a.a[0][0].c);
            } else {
                ans.pb(-1), ans.pb(-1);
            }
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
        int Arr0[] = {2, 3, 5};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {20, 30, 50};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {1, 2, 3, 4, 5, 6};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        long Arr3[] = {-1, -1, 20, 1, 30, 1, 40, 1, 50, 3, 60, 2};
        vector<long long> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(0, Arg3, query(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        int Arr0[] = {7, 4, 3, 8};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {10, 20, 17, 13};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {10, 100, 1000, 100000};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        long Arr3[] = {54, 3, 564, 33, 5664, 333, 566664, 33333};
        vector<long long> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(1, Arg3, query(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        int Arr0[] = {2, 3, 5};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 10, 100};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {1, 2, 3, 4, 5, 6};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        long Arr3[] = {-1, -1, 1, 1, 10, 1, 2, 1, 100, 1, 20, 1};
        vector<long long> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(2, Arg3, query(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        int Arr0[] = {1, 1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {10, 20, 30, 40, 50};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        long Arr3[] = {10,       1024, 20,        1048576, 30,
                       73741817, 40,   511620083, 50,      898961331};
        vector<long long> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(3, Arg3, query(Arg0, Arg1, Arg2));
    }
    void test_case_4() {
        int Arr0[] = {1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1000000000};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        int Arr2[] = {1, 1000000000};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        long Arr3[] = {1000000000, 1, 1000000000000000000, 1};
        vector<long long> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(4, Arg3, query(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

void test_big() {
    CoinsQuery ___test;
    ___test.query(
        {97, 96, 97, 98, 97, 97, 99, 99, 97, 97, 96, 97, 98, 97,
         97, 96, 99, 98, 99, 99, 99, 99, 98, 99, 97, 96, 96, 96,
         98, 98, 99, 98, 99, 99, 98, 96, 99, 97, 99, 97, 99},
        {365356, 355157, 364026, 363920, 362328, 365993, 371142, 366857, 361011,
         359849, 357528, 359623, 364419, 360460, 360820, 359979, 366946, 365858,
         369540, 373408, 372723, 372722, 366352, 370180, 362818, 358089, 359757,
         359340, 363012, 363403, 368451, 365718, 367882, 366952, 369792, 356895,
         367434, 361219, 370668, 359758, 368162},
        {761,       265341471, 42727293,  150347323, 84077,     428485421,
         126070698, 283274831, 232533,    7906394,   56,        460734255,
         326881204, 9430,      67510942,  694181292, 269579539, 971163821,
         844697941, 375370099, 1503,      823919382, 73768314,  9177004,
         607853811, 483411,    143870,    15853201,  14,        135720771,
         62909,     751022064, 505073354, 361601719, 3344727,   91706242,
         34,        18473157,  934706979, 59,        480397707, 666061307,
         167468900, 896753694, 110586164, 7166,      50,        3425657,
         311314680, 3865265,   536227461, 752946275, 7696,      8891,
         89,        66888,     867680593, 25835,     57798,     817042130,
         868286092, 368624,    194621,    8471,      85,        80583745,
         996312143, 495,       977273101, 7,         277329216, 325,
         267731610, 387715232, 53907,     949908142, 273564043, 604482049,
         4555,      778586576, 654338303, 10907011,  587,       8244493,
         128582161, 440313947, 536526551, 262084447, 453429130, 72980,
         4,         49960,     6,         80588});
}

// BEGIN CUT HERE
int main() {
    CoinsQuery ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
