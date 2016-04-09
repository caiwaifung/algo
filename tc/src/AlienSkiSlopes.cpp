#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define _ (int)
#define all(a) a.begin(), a.end()
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

namespace KM {
int w[50][50];
int x[50], y[50];
int n;

bool vx[50], vy[50];
int lx[50], ly[50];

bool find(int i) {
    vx[i] = true;
    for (int j = 0; j < n; j++) {
        if (w[i][j] == x[i] + y[j] && !vy[j]) {
            vy[j] = true;
            if (ly[j] < 0 || find(ly[j])) {
                lx[i] = j; ly[j] = i;
                return true;
            }
        }
    }
    return false;
}

int solve() {
    std::fill(lx, lx + n, -1);
    std::fill(ly, ly + n, -1);
    std::fill(x, x + n, 0);
    std::fill(y, y + n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x[i] = std::max(x[i], w[i][j]);
        }
    }
    for (int k = 0; k < n; ) {
        std::fill(vx, vx + n, false);
        std::fill(vy, vy + n, false);
        if (find(k)) {
            ++k;
            continue;
        }
        int d = 0x7fffffff;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (vx[i] && !vy[j])
                    d = std::min(d, x[i] + y[j] - w[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (vx[i])
                x[i] -= d;
        }
        for (int i = 0; i < n; i++) {
            if (vy[i])
                y[i] += d;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += w[i][lx[i]];
    }
    return ans;
}
}

class AlienSkiSlopes {
public:
    int a[50][50], n;
    vector <int> raise(vector <int> h) {
        n=0; while(n*n<_ h.size()) ++n;
        repn(i, n) repn(j, n) a[i][j]=h[i*n+j];
        KM::n=n;
        repn(i, n) repn(j, n) KM::w[i][j]=a[i][j];
        KM::solve();

        VI p(n); repn(i, n) p[i]=KM::lx[i];

        VI ans(n, 0);
        repn(k, n) {
            repn(i, n) repn(j, n) {
                setmax(ans[j], ans[p[i]]+a[i][j]-a[i][p[i]]);
            }
        }
        return ans;
    }
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = {1,0,0,
 0,1,0,
 0,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, raise(Arg0)); }
	void test_case_1() { int Arr0[] = {1,2,3,4,
 2,3,4,1,
 3,4,1,2,
 4,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, raise(Arg0)); }
	void test_case_2() { int Arr0[] = {91, 19, 50, 21, 56,
 22, 96, 16, 30, 26,
 85, 1, 87, 63, 31,
 44, 25, 8, 94, 78,
 46, 55, 88, 41, 52}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {44, 13, 46, 22, 10 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, raise(Arg0)); }
	void test_case_3() { int Arr0[] = {1000000000,0,0,
 1000000000,0,0,
 1000000000,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1000000000, 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, raise(Arg0)); }
	void test_case_4() { int Arr0[] = {3,1,4,1,5,
 9,2,6,5,3,
 5,8,9,7,9,
 3,2,3,8,4,
 6,2,6,4,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 0, 1, 0, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, raise(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
    AlienSkiSlopes ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
