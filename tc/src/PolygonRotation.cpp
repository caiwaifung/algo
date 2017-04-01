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

const double PI = acos(-1);
const double EPS = 1e-12;

double sgn(double x) { return x < -EPS ? -1 : x > EPS; }
struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double b) const { return Point(x * b, y * b); }
    Point operator/(double b) const { return Point(x / b, y / b); }
    void rotate90() {
        swap(x, y);
        x = -x;
    }
    double len() const { return sqrt(x * x + y * y); }
    void normalize() { *this = *this / len(); }
    friend double mult(Point p1, Point p2) { return p1.x * p2.y - p1.y * p2.x; }
    friend double dot(Point p1, Point p2) { return p1.x * p2.x + p1.y * p2.y; }
    friend double mult(Point p0, Point p1, Point p2) {
        return mult(p1 - p0, p2 - p0);
    }
    friend double dot(Point p0, Point p1, Point p2) {
        return dot(p1 - p0, p2 - p0);
    }
    friend double dist(Point p1, Point p2) { return (p1 - p2).len(); }
    double lambda(Point s, Point t) const {  // return c: p=s+(t-s)*c
        return dot(s, t, *this) / dot(s, t, t);
    }
};
typedef vector<Point> VP;

void cut_convex(VP& a, Point p1, Point p2) {
    VP b;
    repn(i, sz(a)) {
        Point a1 = a[i], a2 = a[(i + 1) % a.size()];
        double m1 = mult(p1, p2, a1);
        double m2 = mult(p1, p2, a2);
        if(sgn(m1) * sgn(m2) < 0) {
            Point tmp;
            tmp.x = (a1.x * m2 - a2.x * m1) / (m2 - m1);
            tmp.y = (a1.y * m2 - a2.y * m1) / (m2 - m1);
            b.push_back(tmp);
        }
        if(sgn(m2) >= 0) b.push_back(a2);
    }
    a = b;
}
VP convex_cross(const VP& a, const VP& b) {
    double s = 0;
    repn(i, b.size()) s +=
        mult(b[i], b[(i + 1) % b.size()], b[(i + 2) % b.size()]);
    VP c = a;
    repn(i, b.size()) {
        Point p1 = b[i], p2 = b[(i + 1) % b.size()];
        if(s < 0) swap(p1, p2);
        cut_convex(c, p1, p2);
    }
    return c;
}

ostream& operator<<(ostream& os, const Point& p) {
    return os<<"("<<p.x<<", "<<p.y<<")";
}

class PolygonRotation {
public:
    double f(double a, double b, double d) {
        if(abs(d) < 1e-13) return 0;
        double t = (b - a) / d;
        return PI * (t * t / 3 * d * d * d + a * t * d * d + a * a * d);
    }
    double go(VP a) {
        int j = 0;
        repn(i, sz(a)) if(a[i].y > a[j].y) j = i;
        {
            VP b;
            b.insert(b.end(), a.begin() + j, a.end());
            b.insert(b.end(), a.begin(), a.begin() + j);
            a = b;
        }
        double ans = 0;
        repn(i, sz(a) - 1) {
            assert(a[i].y >= a[i + 1].y);
            ans += f(a[i].x, a[i + 1].x, a[i].y - a[i + 1].y);
        }
        return ans;
    }
    double getVolume(vector<int> x, vector<int> y) {
        int j = 1;
        while(x[j] != 0) ++j;
        VP a, b;
        rep(i, 0, j) a.pb(Point(x[i], y[i]));
        b.pb(Point(x[0], y[0]));
        irep(i, sz(x) - 1, j) b.pb(Point(-x[i], y[i]));
        VP c = convex_cross(a, b);
        cout<<c<<endl;
        double ans = go(a) + go(b) - go(c);
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
    void verify_case(int Case, const double& Expected, const double& Received) {
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
        int Arr0[] = {0, 1, 1, 0};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {1, 1, 0, 0};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        double Arg2 = 3.141592653589793;
        verify_case(0, Arg2, getVolume(Arg0, Arg1));
    }
    void test_case_1() {
        int Arr0[] = {0, 1, 0, -1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {2, 1, 0, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        double Arg2 = 2.0943951023931953;
        verify_case(1, Arg2, getVolume(Arg0, Arg1));
    }
    void test_case_2() {
        int Arr0[] = {0, 3, 0, -2, -2};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {2, 0, -3, -1, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        double Arg2 = 49.91641660703782;
        verify_case(2, Arg2, getVolume(Arg0, Arg1));
    }
    void test_case_3() {
        int Arr0[] = {0, 3, 3, 0, -1, -1};
        vector<int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0])));
        int Arr1[] = {2, 2, -2, -2, -1, 1};
        vector<int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0])));
        double Arg2 = 113.09733552923255;
        verify_case(3, Arg2, getVolume(Arg0, Arg1));
    }

    // END CUT HERE

    // }}}
};

// BEGIN CUT HERE
int main() {
    PolygonRotation ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
