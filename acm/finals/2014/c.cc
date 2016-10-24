// 2:28 - 3:09
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

typedef long double LD;

int sgn(LD x, LD e=1e-10) { return x<-e ? -1 : x>e; }
bool le(LD x, LD y) { return sgn(x-y)<=0; }

void output(LD x, LD y) {
    printf("%.0lf .. %.0lf\n", floor((double)x), ceil((double)y));
}

void output_inf(LD x) {
    printf("%.0lf .. inf\n", floor((double)x));
}

void solve(LD l, LD r, LD c, LD p, LD w) {
    if(le(l, c) && le(c, r)) {
        if(le(l, p) && le(p, r)) {
            output_inf(0);
        } else if(le(r, p)) {
            output(0, w*(r-c)/(p-r));
        } else {
            output(0, w*(c-l)/(l-p));
        }
    } else {
        if(le(r, c)) {
            l=-l, r=-r, swap(l, r);
            c=-c, p=-p;
        }
        if(le(p, l)) {
            printf("unstable\n");
        } else if(le(p, r)) {
            output_inf(w*(l-c)/(p-l));
        } else {
            output(w*(l-c)/(p-l), w*(r-c)/(p-r));
        }
    }
}

struct Line { LD a, b, c; };

Line make_line(LD x1, LD y1, LD x2, LD y2) {
    Line l;
    l.a=y2-y1;
    l.b=x1-x2;
    l.c=-(x1*l.a+y1*l.b);
    return l;
}

LD centroid_x(LD x1, LD y1, LD x2, LD y2) {
    Line l1=make_line(x1, y1, x2/2, y2/2);
    Line l2=make_line(x2, y2, x1/2, y1/2);
    LD t=l1.a*l2.b-l1.b*l2.a;
    return (l1.b*l2.c-l1.c*l2.b)/t;
}

int main() {
    int n; scanf("%d", &n);
    vector<PII> a(n);
    repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se);

    LD c=0, sum=0, l=1e50, r=-1e50;
    repn(i, n) {
        const int j=(i+1)%n;
        LD cur=LD(a[i].fi)*LD(a[j].se)-LD(a[j].fi)*LD(a[i].se);
        if(cur!=0) {
            c+=centroid_x(a[i].fi, a[i].se, a[j].fi, a[j].se)*cur;
        }
        sum+=cur;
        if(a[i].se==0) {
            setmin(l, LD(a[i].fi));
            setmax(r, LD(a[i].fi));
        }
    }
    c/=sum;
    solve(l, r, c, a[0].fi, abs(sum)/2.0);

    return 0;
}
