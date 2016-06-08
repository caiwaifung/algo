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

const LL MOD=LL(1e9)+7;
const int n=2000000;
const int N=n+10;

LL fac[N], inv_fac[N];

void pre() {
    auto pow=[](LL a, LL b, LL m) {
        LL c=1;
        for(; b>0; b>>=1, a=a*a%m)
            if(b&1) c=c*a%m;
        return c;
    };
    fac[0]=1; rep(i, 1, n) fac[i]=fac[i-1]*i%MOD;
    inv_fac[n]=pow(fac[n], MOD-2, MOD);
    irep(i, n, 1) inv_fac[i-1]=inv_fac[i]*i%MOD;
}

LL solve() {
    int m, w, p; cin>>m>>w>>p;
    if(m==0) return fac[w];
    if(w==0) return fac[m];
    if(p==0) return 0;
    LL ans=0;
    rep(i, 1, p) {
        int m0=m-i, w0=w-i;
        int x=(i+1)/2, y=(i+1)-x;
        repn(tt, 2) {
            LL tmp=(fac[p]*inv_fac[p-i]%MOD);
            (tmp*=(fac[x+m0-1]*inv_fac[x-1]%MOD))%=MOD;
            (tmp*=(fac[y+w0-1]*inv_fac[y-1]%MOD))%=MOD;
            (ans+=tmp)%=MOD;
            swap(x, y);
        }
    }
    return ans;
}

int main() {
    pre();
    LL ans=solve();
    cout<<ans<<endl;
    return 0;
}
