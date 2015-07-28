// 11:59
// 12:16 - 12:30 - wa
//       - 12:51 - tle
#include <cassert>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

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

VL ans;
bool ok[1000010], prime[1000010];

bool is_ok(LL x) {
    LL y=2;
    while(y*y<=x && x%y!=0) ++y;
    if(x%y==0) {
        while(x%y==0) x/=y;
        return x==1;
    }
    return true;
}

LL p[15], va[99999]; bool vok[99999];

void go(LL n, LL lb, LL cur) {
    if(n==1) { ans.pb(cur); return; }
    if(n-1>=lb && gcd(n-1, cur)==1 && is_ok(n-1)) 
        go(1, n, cur*(n-1));
    for(LL i=lb; (i+1)*(i+1)<=n; ++i)
        if(ok[i] && n%(i+1)==0 && gcd(i, cur)==1)
            go(n/(i+1), i+1, cur*i);
}

LL J(LL x) {
    LL n=1;
    for(LL y=2; y*y<=x; ++y)
        if(x%y==0) {
            LL t=1;
            while(x%y==0) t*=y, x/=y;
            n*=t+1;
        }
    if(x>1) n*=x+1;
    return n;
}

int main() {
    fillchar(prime, true);
    fillchar(ok, false);
    prime[1]=false;
    rep(i, 2, 1000000) if(prime[i]) {
        for(int t=1; t<=1000000; t=(int)min(LL(t)*LL(i), 1LL<<30))
            ok[t]=true;
        for(int j=i*2; j<=1000000; j+=i)
            prime[j]=false;
    }

    LL n; 
    cin>>n;
    ans.clear();
    go(n, 2, 1);

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    LL ret=(int)ans.size();
    cout<<ret<<endl;

    return 0;
}
