#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) static_cast<int>(a.size())
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

struct Point {
    int x=0, y=0;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    void read() { scanf("%d%d", &x,&y); }
    bool operator<(const Point& p) const {
        return x<p.x || (x==p.x && y<p.y);
    }
    Point operator-(const Point& p) const {
        return Point(x-p.x, y-p.y);
    }
    friend int cross(Point p1, Point p2) {
        return (p1.x)*(p2.y)-(p2.x)*(p1.y);
    }
    friend int cross(Point p0, Point p1, Point p2) {
        return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
    }
};

vector<Point> cal(vector<Point> a) {
    sort(all(a));
    vector<Point> b;
    for(const auto& p: a) {
        while(b.size()>1 && cross(b[b.size()-2], b[b.size()-1], p)<=0)
            b.pop_back();
        b.pb(p);
    }
    auto L=b.size(); reverse(all(a));
    for(const auto& p: a) {
        while(b.size()>L && cross(b[b.size()-2], b[b.size()-1], p)<=0)
            b.pop_back();
        b.pb(p);
    }
    b.pop_back();
    return b;
}

bool solve() {
    vector<Point> a(5);
    for(auto& p: a) p.read();
    a=cal(a);
    if(a.size()!=5) return false;
    repn(i, 5) {
        Point v1=a[(i+1)%5]-a[i];
        Point v2=a[(i+3)%5]-a[(i+2)%5];
        if(cross(v1, v2)<=0) return false;
    }
    return true;
}

int main() {
    printf("%s\n", solve()?"Yes":"No");
    return 0;
}
