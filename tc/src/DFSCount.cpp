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

LL f[1 << 14][14];
LL fac[19];

class DFSCount {
    VS g;
    int n;

    LL solve(int s, int i) {
        if(f[s][i] >= 0) return f[s][i];
        LL ans = 1;

        int r = s ^ (1 << i);
        const function<int(int)> extract = [&](int x) {
            int cur = 1 << x;
            r ^= 1 << x;
            repn(y, n) if((r & (1 << y)) && g[x][y] == 'Y') {
                cur ^= extract(y);
            }
            return cur;
        };
        int cnt = 0;
        repn(j, n) if(r & (1 << j)) {
            int cur = extract(j);
            ++cnt;
            LL tmp = 0;
            repn(k, n) if((cur & (1 << k)) && g[i][k] == 'Y') {
                tmp += solve(cur, k);
            }
            ans *= tmp;
        }
        ans *= fac[cnt];
        return f[s][i] = ans;
    }

public:
    long long count(vector<string> G) {
        fac[0] = 1;
        replr(i, 1, 19) fac[i] = fac[i - 1] * i;

        g = G, n = sz(G);
        LL ans = 0;
        fillchar(f, -1);
        repn(i, n) ans += solve((1 << n) - 1, i);
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
    void verify_case(int Case, const long long& Expected,
                     const long long& Received) {
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
        string Arr0[] = {"NYY", "YNY", "YYN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        long long Arg1 = 6LL;
        verify_case(0, Arg1, count(Arg0));
    }
    void test_case_1() {
        string Arr0[] = {"NYNN", "YNYN", "NYNY", "NNYN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        long long Arg1 = 6LL;
        verify_case(1, Arg1, count(Arg0));
    }
    void test_case_2() {
        string Arr0[] = {"NYYY", "YNYY", "YYNN", "YYNN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        long long Arg1 = 16LL;
        verify_case(2, Arg1, count(Arg0));
    }
    void test_case_3() {
        string Arr0[] = {"NYYYYYYYYYYYYY", "YNYYYYYYYYYYYY", "YYNYYYYYYYYYYY",
                         "YYYNYYYYYYYYYY", "YYYYNYYYYYYYYY", "YYYYYNYYYYYYYY",
                         "YYYYYYNYYYYYYY", "YYYYYYYNYYYYYY", "YYYYYYYYNYYYYY",
                         "YYYYYYYYYNYYYY", "YYYYYYYYYYNYYY", "YYYYYYYYYYYNYY",
                         "YYYYYYYYYYYYNY", "YYYYYYYYYYYYYN"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        long long Arg1 = 87178291200LL;
        verify_case(3, Arg1, count(Arg0));
    }
    void test_case_4() {
        string Arr0[] = {"N"};
        vector<string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        long long Arg1 = 1LL;
        verify_case(4, Arg1, count(Arg0));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    DFSCount ___test;
    ___test.run_test(-1);

    return 0;
}
// END CUT HERE
