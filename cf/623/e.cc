#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <set>
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
typedef vector<PLL> VPL;
typedef vector<string> VS;
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const LL MOD=LL(1e9)+7;
const LL CAP=LL(8e18);
const int K=1<<16;

void add(LL* a, const LL* b, int n) { repn(i, n) { a[i]+=b[i]; if(a[i]>=MOD) a[i]-=MOD; } }
void dec(LL* a, const LL* b, int n) { repn(i, n) { a[i]-=b[i]; if(a[i]<0) a[i]+=MOD; } }

LL mem[10*K]; int cur=0;

//int cnt[99999]={0};
void convolute(const LL* a, const LL* b, LL* c, int n) {
    //++cnt[n];
    if(n<=32) {
        repn(i, n) repn(j, n) {
            c[i+j]+=a[i]*b[j];
            if(c[i+j]>CAP) c[i+j]%=MOD;
        }
        repn(i, n*2) c[i]%=MOD;
        return;
    }
    convolute(a, b, c, n/2);
    convolute(a+n/2, b+n/2, c+n, n/2);

    LL* x=mem+cur; cur+=n/2; repn(i, n/2) { x[i]=a[i]+a[i+n/2]; if(x[i]>=MOD) x[i]-=MOD; }
    LL* y=mem+cur; cur+=n/2; repn(i, n/2) { y[i]=b[i]+b[i+n/2]; if(y[i]>=MOD) y[i]-=MOD; }
    LL* z=mem+cur; cur+=n; memset(z, 0, sizeof(LL)*n);
    convolute(x, y, z, n/2);
    repn(i, n) z[i]-=c[i]+c[i+n];
    
    repn(i, n) {
        (c[i+n/2]+=z[i])%=MOD;
        if(c[i+n/2]<0) c[i+n/2]+=MOD;
    }
    cur-=n*2;
}

int k, kn, k2;
LL fac[30030], inv_fac[30030], m2[30030];

void prepare() {
    m2[0]=1; rep(i, 1, k) m2[i]=m2[i-1]*2%MOD;
    fac[0]=1; rep(i, 1, k) fac[i]=fac[i-1]*i%MOD;
    auto pow=[](LL a, LL b, LL m) {
        LL c=1;
        for(; b>=1; b>>=1, a=a*a%m)
            if(b&1) c=c*a%m;
        return c;
    };
    rep(i, 0, k) inv_fac[i]=pow(fac[i], MOD-2, MOD);
}

struct F {
    LL f[30030];
    int n;
    F(int _n) : n(_n) {
        assert(n==0 || n==1);
        if(n==0) {
            fillchar(f, 0); f[0]=1;
        } else {
            fill(f, f+k2+1, 1);
        }
    }
    void merge(const F& b) {
        static LL x[K], y[K], z[K];
        fillchar(x, 0); fillchar(y, 0); fillchar(z, 0);

        LL m=1;
        rep(i, 0, k2+n) {
            if(i>=n) x[i-n]=f[i-n]*inv_fac[i]%MOD*m%MOD;
            m=m*m2[b.n]%MOD;
        }
        rep(i, 0, k2+b.n) {
            if(i>=b.n) y[i-b.n]=b.f[i-b.n]*inv_fac[i]%MOD;
        }

        convolute(x, y, z, kn);
        n+=b.n;
        rep(i, 0, k2+n) if(i>=n) f[i-n]=z[i-n]%MOD*fac[i]%MOD;
    }
};

LL solve(int n) {
    F f(0), z(1);
    for(; n>=1; n>>=1, z.merge(z))
        if(n&1) f.merge(z);

    LL ans=0;
    auto binom=[](int x, int y) { return fac[x]*inv_fac[y]%MOD*inv_fac[x-y]%MOD; };
    rep(i, f.n, f.n+k2) (ans+=f.f[i-f.n]*binom(k, i))%=MOD;

    return ans;
}

int main() {
    LL n; cin>>n>>k;
    if(n>k) { cout<<0<<endl; return 0; }
    k2=k-(int)n; kn=1; while(kn<=k2+1) kn*=2;
    prepare();
    cout<<solve((int)n)<<endl;
    //cout<<cnt<<endl;
    //for(int i=0; i<99999; ++i) if(cnt[i]>0) printf("cnt[%d]=%d\n", i,cnt[i]);
    return 0;
}
