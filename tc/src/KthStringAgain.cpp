#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

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
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template <class T, class S>
ostream& operator<<(ostream& os, const pair<T, S>& v) {
    return os << "(" << v.first << ", " << v.second << ")";
}
template <class T> ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    repn(i, sz(v)) {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]";
}
template <class T> bool setmax(T& _a, T _b) {
    if (_b > _a) {
        _a = _b;
        return true;
    }
    return false;
}
template <class T> bool setmin(T& _a, T _b) {
    if (_b < _a) {
        _a = _b;
        return true;
    }
    return false;
}
template <class T> T gcd(T _a, T _b) { return _b == 0 ? _a : gcd(_b, _a % _b); }

class KthStringAgain {
    LL solve(string s, string t) {
        const auto match=[](char x, char y) { return x==y || y=='*'; };
        const int n=sz(s);
        vector<VL> f(n+1, VL(n+1));
        rep(j, 0, n) f[n][j]=1;
        irepn(i, n) repn(j, n) {
            if(match(s[i], t[j])) f[i][j]+=f[i+1][j+1];
            if(match(s[i], t[j+n-i-1])) f[i][j]+=f[i+1][j];
        }
        //if(f[0][0]) cout<<s<<" "<<t<<" "<<f[0][0]<<endl;
        return f[0][0];
    }
public:
    string getKth(string s, LL k) {
        const int n = sz(s);

        string ans;
        repn(i, n) {
            for(char ch='a'; ch<='z'; ++ch) {
                string tmp=ans;
                tmp+=ch;
                while(sz(tmp)<n) tmp+='*';
                LL num=solve(s, tmp);
                if(k<=num) {
                    ans+=ch; break;
                }
                k-=num;
            }
        }
        return ans;
    }

    // BEGIN CUT HERE
public:
    void run_test(int Case) {
        if ((Case == -1) || (Case == 0))
            test_case_0();
        if ((Case == -1) || (Case == 1))
            test_case_1();
        if ((Case == -1) || (Case == 2))
            test_case_2();
        if ((Case == -1) || (Case == 3))
            test_case_3();
        if ((Case == -1) || (Case == 4))
            test_case_4();
        if ((Case == -1) || (Case == 5))
            test_case_5();
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
    void verify_case(int Case, const string& Expected, const string& Received) {
        cerr << "Test Case #" << Case << "...";
        if (Expected == Received)
            cerr << "PASSED" << endl;
        else {
            cerr << "FAILED" << endl;
            cerr << "\tExpected: \"" << Expected << '\"' << endl;
            cerr << "\tReceived: \"" << Received << '\"' << endl;
        }
    }
    void test_case_0() {
        string Arg0 = "xyz";
        long long Arg1 = 5LL;
        string Arg2 = "yzx";
        verify_case(0, Arg2, getKth(Arg0, Arg1));
    }
    void test_case_1() {
        string Arg0 = "abc";
        long long Arg1 = 1LL;
        string Arg2 = "abc";
        verify_case(1, Arg2, getKth(Arg0, Arg1));
    }
    void test_case_2() {
        string Arg0 = "abc";
        long long Arg1 = 8LL;
        string Arg2 = "cba";
        verify_case(2, Arg2, getKth(Arg0, Arg1));
    }
    void test_case_3() {
        string Arg0 = "topcoder";
        long long Arg1 = 58LL;
        string Arg2 = "ooredcpt";
        verify_case(3, Arg2, getKth(Arg0, Arg1));
    }
    void test_case_4() {
        string Arg0 = "aaaabcdeeeghhhhhiijjjkllmmooooqqrrrrssttuuvvvvvwyy";
        long long Arg1 = 38517901796974LL;
        string Arg2 = "aaaacdeehhhijklmmqqrsttvvvvwyyvuusrrrooooljjihhgeb";
        verify_case(4, Arg2, getKth(Arg0, Arg1));
    }
    void test_case_5() {
        string Arg0 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        long long Arg1 = 999999999999LL;
        string Arg2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        verify_case(5, Arg2, getKth(Arg0, Arg1));
    }

    // END CUT HERE
};

// BEGIN CUT HERE
int main() {
    KthStringAgain ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
