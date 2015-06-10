#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<int,int> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

struct Point {
    int x, y, i;
    bool operator <(const Point &p) const {
        if(x!=p.x) return x<p.x;
        return y>p.y;
    }
    Point() { }
    Point(int _x, int _y) : x(_x), y(_y) { }
    Point operator +(const Point &p) const { return Point(x+p.x, y+p.y); }
    Point operator -(const Point &p) const { return Point(x-p.x, y-p.y); }
    Point operator *(int b) const { return Point(x*b, y*b); }
    Point operator /(int b) const { return Point(x/b, y/b); }
    friend int mult(Point p1, Point p2) { return p1.x*p2.y-p1.y*p2.x; }
    friend int dot(Point p1, Point p2) { return p1.x*p2.x+p1.y*p2.y; }
    friend int mult(Point p0, Point p1, Point p2) { return mult(p1-p0, p2-p0); }
    friend int dot(Point p0, Point p1, Point p2) { return dot(p1-p0, p2-p0); }
};


int main() {
    int n, cur=0; cin>>n;
    vector<Point> a(n); 
    for(Point &p: a) {
        cin>>p.x>>p.y;
        p.i=++cur;
        p.x*=-1, p.y*=-1;
    }
    sort(all(a));

    vector<Point> b;
    for(Point &p: a) {
        if(b.empty()) {
            b.PB(p); continue;
        }
        if(p.y>b.back().y) continue;
        while(b.size()>=2 && mult(b[b.size()-2], b.back(), p)<0)
            b.pop_back();
        b.PB(p);
    }
    VI ans;
    for(Point &p: b) ans.PB(p.i);
    sort(all(ans));
    for(int i: ans) cout<<i<<" "; cout<<endl;

    return 0;
}
