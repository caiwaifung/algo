#include <algorithm>
#include <functional>
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

PII go(int h, int a, int x, int y, int m) {
    static int p[1001000];
    fillchar(p, 0xff);
    int cur=0;
    while(p[h]<0) {
        p[h]=cur;
        h=int(((LL)x*(LL)h+y)%m);
        ++cur;
    }
    if(p[a]<0) return MP(-1, -1);
    if(p[a]>=p[h])
        return MP(p[a], cur-p[h]);
    else
        return MP(p[a], -1);
}

template<class T> T ext_gcd(T a, T b, T &x, T &y) {
    if(b==0) { x=1, y=0; return a; }
    LL nx, ny, d; d=ext_gcd(b, a%b, nx, ny);
    x=ny, y=nx-(a/b)*ny;
    return d;
}


LL solve(LL t1, LL p1, LL t2, LL p2, LL m) {
    if(t1<0) return -1;
    if(t2<0) return -1;
    if(p1<0 && p2<0) return t1==t2?t1:-1;
    if(p1<0) {
        if(t1>=t2 && (t1-t2)%p2==0)
            return t1;
        else
            return -1;
    }
    if(p2<0) return solve(t2, p2, t1, p1, m);

    //assert(m%p1==0 && m%p2==0);
    LL x, y, g=gcd(p1, p2);
    ext_gcd(p1, p2, x, y);
    assert(x*p1+y*p2==g);

    if((t2-t1)%g!=0) return -1;
    LL d=(t2-t1)/g;
    LL i=x*d, j=-y*d;
    assert(i*p1+t1==j*p2+t2);

    LL z1=p1/g, z2=p2/g;

    if(i<0) {
        LL z=(-i)/z2+1;
        i+=z*z2, j+=z*z1;
    }
    if(j<0) {
        LL z=(-j)/z1+1;
        i+=z*z2, j+=z*z1;
    }
    if(i>0 && j>0) {
        LL z=min(i/z2, j/z1);
        i-=z*z2, j-=z*z1;
    }
    assert(i>=0 && j>=0);
    assert(i*p1+t1==j*p2+t2);

    return i*p1+t1;
}

int main() {
    int m; cin>>m;
    PII t[2];
    forn(i, 2) {
        int h, a, x, y;
        cin>>h>>a>>x>>y;
        t[i]=go(h, a, x, y, m);
        //cout<<t[i].fi<<" "<<t[i].se<<endl;
    }
    LL ans=solve(t[0].fi, t[0].se, t[1].fi, t[1].se, m);
    cout<<ans<<endl;
    return 0;
}
