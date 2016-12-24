#include <algorithm>
#include <bitset>
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
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
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
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

struct Picture {
    const int n, m;
    vector<bitset<2000>> a;
    Picture(int _n, int _m) : n(_n), m(_m), a(n) {}
};

Picture simplify(const Picture& pic, int* dx=nullptr, int* dy=nullptr) {
    int x1=1<<30, x2=-1, y1=1<<30, y2=-1;
    bool found=false;
    repn(i, pic.n) repn(j, pic.m) {
        if(pic.a[i][j]) {
            found=true;
            setmin(x1, i), setmax(x2, i);
            setmin(y1, j), setmax(y2, j);
        }
    }
    if(!found) {
        return Picture(0, 0);
    }
    Picture sim(x2-x1+1, y2-y1+1);
    repn(i, sim.n) repn(j, sim.m) {
        sim.a[i][j]=pic.a[i+x1][j+y1];
    }
    if(dx) *dx=x1;
    if(dy) *dy=y1;
    return sim;
}

Picture read_picture(int* dx=nullptr, int* dy=nullptr) {
    int n, m; scanf("%d%d", &n,&m);
    Picture pic(n, m);
    repn(i, n) {
        static char buf[1010];
        scanf("%s", buf);
        repn(j, m) pic.a[i][j]=(buf[j]=='*');
    }
    return simplify(pic, dx, dy);
}

Picture intersect(const Picture& a, const Picture& b, int dx, int dy) {
    int x1=min(dx, 0), x2=max(dx+b.n, a.n);
    int y1=min(dy, 0), y2=max(dy+b.m, a.m);
    Picture pic(x2-x1, y2-y1);
    repn(i, a.n) {
        pic.a[i-x1]^=(a.a[i]<<(-y1));
    }
    repn(i, b.n) {
        pic.a[i+dx-x1]^=(b.a[i]<<(dy-y1));
    }
    return pic;
}

const pair<PII, PII> noans=mp(mp(1<<30, 1<<30), mp(1<<30, 1<<30));

pair<PII, PII> solve(const Picture& a, const Picture& b, const Picture& c) {
    rep(dx, -1000, 1000) rep(dy, -1000, 1000) {
        int x1=min(dx, 0), x2=max(dx+b.n, a.n);
        int y1=min(dy, 0), y2=max(dy+b.m, a.m);
        if(dx!=0 && dx+b.n!=a.n) {
            if(x2-x1!=c.n) continue;
        }
        if(dy!=0 && dy+b.m!=a.m) {
            if(y2-y1!=c.m) continue;
        }
        Picture d=intersect(a, b, dx, dy);
        int rx, ry;
        Picture sd=simplify(d, &rx, &ry);
        if(sd.n==c.n && sd.m==c.m && sd.a==c.a) {
            return mp(mp(dx, dy), mp(rx+x1, ry+y1));
        }
    }
    return noans;
}

int main() {
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);
    int ax, ay; Picture a=read_picture(&ax, &ay);
    int bx, by; Picture b=read_picture(&bx, &by);
    Picture c=read_picture();

    int dx, dy;
    if((a.n==c.n && a.n>b.n) || (a.m==c.m && a.m>b.m)) {
        auto r=solve(a, c, b);
        if(r==noans) { printf("NO\n"); return 0; }
        dx=r.se.fi, dy=r.se.se;
    } else if((b.n==c.n && b.n>a.n) || (b.m==c.m && b.m>a.m)) {
        auto r=solve(b, c, a);
        if(r==noans) { printf("NO\n"); return 0; }
        dx=-r.se.fi, dy=-r.se.se;
    } else {
        auto r=solve(a, b, c);
        if(r==noans) { printf("NO\n"); return 0; }
        dx=r.fi.fi, dy=r.fi.se;
    }
    printf("YES\n");
    printf("%d %d\n", dy+ay-by, dx+ax-bx);
    return 0;
}
