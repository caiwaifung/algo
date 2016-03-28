#include <algorithm>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//{{{
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
#ifdef DEBUG
    #define _debug(args...) { fprintf(stderr, args); fflush(stderr); }
#else
    #define _debug(args...) {}
#endif
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
template<class T> T absv(T _x) { return _x>0?_x:-_x; }
//}}}

// string x (in base 2)'s value in base i
LL resp(LL x, LL i) {
    LL y=0;
    for(LL tmp=x, b=1; tmp>0; tmp/=2, b*=i) {
        y+=(tmp&1)*b;
    }
    return y;
}

// returns -1 if none
LL factor(LL x) {
    LL z=2;
    while(z*z<=x) {
        if(x%z==0) return z;
        ++z;
    }
    return -1;
}

pair<bool, VL> check_jamcoin(LL x) {
    VL r;
    rep(i, 2, 10) {
        LL y=resp(x, i);
        LL z=factor(y);
        if(z>=0) r.pb(z);
        else return mp(false, VL());
    }
    return mp(true, r);
}

void print(LL x, VL factors) {
    string s;
    for(LL t=x; t>0; t/=2) s+=char(t%2+'0');
    reverse(all(s));
    printf("%s", s.c_str());
    for(LL y: factors) printf(" %lld", y);
    printf("\n");
}

void solve(int n, int num) {
    int l=n/2;
    if(l>=2 && (1<<(l-2))>=num) {
        repn(k, num) {
            LL x=(1<<(l-1))+(k<<1)+1;
            LL y=(x<<(n-l)) + x;
            VL rs;
            rep(i, 2, 10) rs.pb(resp((1<<(n-l))+1, i));
            print(y, rs);
        }
    } else {
        rep(x, 1<<(n-1), (1<<n)-1) if(x&1) {
            auto r=check_jamcoin(x);
            if(r.fi) { print(x, r.se); if(--num==0) break; }
        }
    }
}

int main() {
    scanf("%*d");
    int n, x; scanf("%d%d", &n,&x);
    printf("Case #1:\n");
    solve(n, x);
    return 0;
}

