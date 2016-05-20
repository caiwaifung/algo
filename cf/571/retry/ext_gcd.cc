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
typedef pair<LL,LL> PL;
typedef vector<LL> VL;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

LL ext_gcd(LL a, LL b, LL* x, LL* y) {
    if(b==0) { *x=1, *y=0; return a; }
    LL nx, ny; LL d=ext_gcd(b, a%b, &nx, &ny);
    *x=ny, *y=nx-(a/b)*ny;
    printf("%lld %lld (%lld): %lld %lld\n", a,b,d,*x,*y);
    return d;
}

int main() {
    while(1) {
        LL a, b, x, y; cin>>a>>b;
        ext_gcd(a, b, &x,&y);
    }

    return 0;
}