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

class PingPongQueue {
public:
    vector<int> whoPlaysNext(vector<int> skills, int N, int K) {
        queue<int> q;
        repn(i, sz(skills)) q.push(i);
        PII a = mp(-1, -1), b = a;
        while(1) {
            if(a.fi < 0) a = mp(q.front(), 0), q.pop();
            if(b.fi < 0) b = mp(q.front(), 0), q.pop();
            if(skills[a.fi] < skills[b.fi]) swap(a, b);
            if(--K == 0) return VI{skills[b.fi], skills[a.fi]};
            q.push(b.fi), b = mp(-1, -1);
            if(++a.se == N) q.push(a.fi), a = mp(-1, -1);
        }
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
        int Arr0[] = {1, 2, 3};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 2;
        int Arg2 = 2;
        int Arr3[] = {2, 3};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(0, Arg3, whoPlaysNext(Arg0, Arg1, Arg2));
    }
    void test_case_1() {
        int Arr0[] = {1, 2, 3};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 2;
        int Arg2 = 4;
        int Arr3[] = {1, 2};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(1, Arg3, whoPlaysNext(Arg0, Arg1, Arg2));
    }
    void test_case_2() {
        int Arr0[] = {49, 24, 26, 12, 5,  33, 25, 30, 35, 41, 46, 23, 21,
                      3,  38, 43, 11, 19, 34, 29, 20, 32, 39, 7,  50};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 10;
        int Arg2 = 399;
        int Arr3[] = {12, 50};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(2, Arg3, whoPlaysNext(Arg0, Arg1, Arg2));
    }
    void test_case_3() {
        int Arr0[] = {30, 12};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arg1 = 34;
        int Arg2 = 80;
        int Arr3[] = {12, 30};
        vector<int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0])));
        verify_case(3, Arg3, whoPlaysNext(Arg0, Arg1, Arg2));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    PingPongQueue ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
