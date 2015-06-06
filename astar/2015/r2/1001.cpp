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
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

struct Point {
    int x, y;
    void read() {
        scanf("%d%d", &x,&y);
    }
};
Point a1[55], a2[55];
bool is_hor[55];
int n;

void init() {
    scanf("%d", &n);
    forint(i, 1, n) {
        a1[i].read();
        a2[i].read();
        if(a1[i].x>a2[i].x) swap(a1[i], a2[i]);
        if(a1[i].y>a2[i].y) swap(a1[i], a2[i]);
        is_hor[i]=(a1[i].y==a2[i].y);
    }
}

bool on(Point p, int i) {
    return p.x>=a1[i].x && p.x<=a2[i].x && p.y>=a1[i].y && p.y<=a2[i].y;
}

bool ok(Point p1, Point p2) {
    forint(i, 1, n) {
        if(on(p1, i) && on(p2, i))
            return true;
    }
    return false;
}

void solve(int cs) {
    vector<Point> p;
    forint(i, 1, n) if(is_hor[i])
        forint(j, 1, n) if(!is_hor[j]) {
            Point c;
            c.x=a1[j].x, c.y=a1[i].y;
            if(c.x<a1[i].x || c.x>a2[i].x) continue;
            if(c.y<a1[j].y || c.y>a2[j].y) continue;
            p.PB(c);
        }
    int ans=0;
    forn(i, p.size()) forn(j, p.size())
        if(p[i].x<p[j].x && p[i].y<p[j].y) {
            Point p3; p3.x=p[i].x, p3.y=p[j].y;
            Point p4; p4.x=p[j].x, p4.y=p[i].y;
            if(!ok(p[i], p3)) continue;
            if(!ok(p[i], p4)) continue;
            if(!ok(p[j], p3)) continue;
            if(!ok(p[j], p4)) continue;
            ++ans;
        }
    printf("Case #%d:\n", cs);
    printf("%d\n", ans);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
