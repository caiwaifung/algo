#include <random>
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

const LL V=LL(1e18)-10;

LL ran(LL l, LL r) {
    static default_random_engine generator;
    uniform_int_distribution<LL> distribution(l, r);
    return distribution(generator);
}

PLL query(LL x) {
    cout<<"? "<<x<<endl;
    string ch; cin>>ch;
    return mp(x, ch=="W"?1:0);
}

PLL find_boundary_with(PLL x, PLL y) {
    while(x.fi+1<y.fi) {
        PLL z=query((x.fi+y.fi)/2);
        if(x.se!=z.se) y=z;
            else x=z;
    }
    return x;
}

void go(PLL x, PLL y) {
    repn(t, 20) {
        PLL z=query(ran(x.fi, y.fi));
        if(z.se!=x.se) {
            if(z.fi-x.fi<y.fi-z.fi) {
                y=find_boundary_with(x, z);
            } else {
                z=find_boundary_with(z, y);
                x=mp(z.fi+1, z.se^1);
            }
            go(x, y); return;
        }
    }
    cout<<"! "<<(y.fi-x.fi+1)<<endl;
}


PLL find_boundary(LL l, LL r) {
    LL p[2]={0, 0};
    while(p[0]==0 || p[1]==0) {
        PLL x=query(ran(l, r));
        p[x.se]=x.fi;
    }
    PLL x=mp(p[0], 0), y=mp(p[1], 1);
    if(x.fi>y.fi) swap(x, y);
    return find_boundary_with(x, y);
}

int main() {
    PLL x=find_boundary(-V, -V/2);
    ++x.fi, x.se^=1;
    PLL y=find_boundary(V/2, V);
    while(x.se!=y.se) {
        PLL z=find_boundary_with(x, y);
        if(z.fi-x.fi<y.fi-z.fi)
            y=z;
        else
            x=mp(z.fi+1, z.se^1);
    }
    go(x, y);
    return 0;
}
