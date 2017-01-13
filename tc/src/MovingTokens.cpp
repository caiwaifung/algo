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

class MovingTokens {
public:
    int move(int n, int m, vector<int> moves) {
        vector<VI> M(m, VI(n));
        repn(j, m) repn(i, n) M[j][i] = moves[j * n + i];

        vector<VI> f(n, VI(n, -1));
        repn(i, n) f[i][i] = 0;
        for(bool found = true; found;) {
            found = false;
            repn(t, m) repn(i, n) repn(j, n) {
                if(f[i][j] < 0 && f[M[t][i]][M[t][j]] >= 0) {
                    f[i][j] = t;
                    found = true;
                }
            }
        }
        VI token(n, 1);
        for(bool found = true; found;) {
            found = false;
            repn(i, n) repn(j, n) {
                if(i != j && token[i] && token[j] && f[i][j] >= 0) {
                    int x = i, y = j;
                    while(x != y) {
                        int t = f[x][y];
                        VI new_token(n, 0);
                        repn(k, n) if(token[k]) new_token[M[t][k]] = 1;
                        token = new_token;
                        x = M[t][x], y = M[t][y];
                    }
                    found = true;
                }
            }
        }
        return accumulate(all(token), 0);
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
        int Arg0 = 2;
        int Arg1 = 2;
        int Arr2[] = {0, 1, 0, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arg3 = 2;
        verify_case(0, Arg3, move(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        int Arg0 = 2;
        int Arg1 = 2;
        int Arr2[] = {0, 0, 1, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arg3 = 1;
        verify_case(1, Arg3, move(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        int Arg0 = 3;
        int Arg1 = 1;
        int Arr2[] = {0, 1, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arg3 = 2;
        verify_case(2, Arg3, move(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        int Arg0 = 2;
        int Arg1 = 5;
        int Arr2[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arg3 = 1;
        verify_case(3, Arg3, move(Arg0, Arg1, Arg2));
    }
    void test_case_4() {
        int Arg0 = 3;
        int Arg1 = 2;
        int Arr2[] = {0, 2, 2, 1, 1, 0};
        vector<int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0])));
        int Arg3 = 1;
        verify_case(4, Arg3, move(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    MovingTokens ___test;
    cout << ___test.move(
                17, 17,
                {11, 1,  2,  3,  16, 11, 6,  0,  9,  8,  10, 0,  15, 4,  8,  12,
                 4,  7,  1,  2,  3,  4,  11, 3,  5,  14, 8,  10, 5,  15, 4,  8,
                 12, 4,  7,  1,  2,  3,  4,  5,  3,  5,  10, 10, 14, 7,  12, 13,
                 8,  12, 4,  0,  1,  2,  3,  16, 0,  3,  11, 9,  8,  10, 5,  12,
                 13, 8,  15, 16, 7,  1,  2,  3,  16, 11, 3,  5,  9,  14, 10, 5,
                 15, 4,  9,  12, 4,  11, 1,  2,  3,  16, 5,  3,  0,  14, 8,  14,
                 11, 15, 16, 9,  12, 13, 5,  1,  2,  3,  16, 0,  6,  0,  9,  10,
                 8,  7,  12, 16, 9,  12, 4,  11, 1,  2,  6,  16, 5,  6,  11, 8,
                 14, 10, 5,  15, 13, 14, 12, 4,  11, 1,  2,  3,  16, 7,  3,  5,
                 8,  8,  10, 7,  12, 16, 9,  12, 16, 11, 1,  2,  3,  16, 11, 6,
                 0,  9,  9,  14, 0,  15, 16, 14, 12, 13, 5,  1,  2,  6,  13, 5,
                 6,  5,  14, 14, 8,  0,  12, 4,  14, 12, 4,  0,  1,  2,  6,  4,
                 5,  3,  7,  9,  8,  10, 0,  12, 4,  9,  12, 16, 7,  1,  2,  6,
                 4,  5,  6,  0,  9,  9,  10, 5,  15, 13, 9,  12, 4,  0,  1,  2,
                 6,  16, 7,  6,  11, 14, 9,  8,  0,  12, 4,  14, 12, 4,  7,  1,
                 2,  6,  4,  5,  3,  11, 10, 8,  10, 11, 12, 13, 8,  15, 4,  5,
                 1,  2,  3,  13, 0,  6,  11, 9,  14, 8,  0,  15, 4,  10, 15, 16,
                 0,  1,  2,  3,  16, 11, 3,  7,  14, 10, 8,  11, 15, 13, 8,  15,
                 16})
         << endl;

    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
