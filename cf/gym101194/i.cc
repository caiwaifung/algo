#include <algorithm>
#include <complex>
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
typedef pair<LL,LL> pll;
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

typedef long long int64;
typedef vector<int64> vint64;
typedef long double LD;
typedef long double T;

const int N=1<<16;

void fft(complex<T>* a, int n, bool inv) {
    T arg=(T)acosl(-1.0);
    static complex<T> b[N];
    for(int t=n/2; t>=1; t/=2) {
        complex<T> w(cosl(arg), (inv?sinl(arg):-sinl(arg)));
        complex<T> p(1.0, 0.0);
        for(int j=0; j<n/2; j+=t, p*=w)
            for(int i=0; i<t; ++i) {
                complex<T> u=a[i+j*2];
                complex<T> v=p*a[i+t+j*2];
                b[i+j]=u+v;
                b[i+j+n/2]=u-v;
            }
        memcpy(a, b, sizeof(a[0])*n);
        arg/=2;
    }
}

const LL MOD=LL(1e9)+7;

vint64 convolute(vint64 a, vint64 b, int size) {
    int n=1; 
    while(n<sz(a)+sz(b)) n*=2;
    static complex<LD> x0[N], x1[N], y0[N], y1[N];
    repn(i, n) if(i<sz(a)) {
        x0[i]=complex<LD>(a[i]&((1<<15)-1), 0);
        x1[i]=complex<LD>(a[i]>>15, 0);
    } else {
        x0[i]=x1[i]=0;
    }
    repn(i, n) if(i<sz(b)) {
        y0[i]=complex<LD>(b[i]&((1<<15)-1), 0);
        y1[i]=complex<LD>(b[i]>>15, 0);
    } else {
        y0[i]=y1[i]=0;
    }
    fft(x0, n, false), fft(x1, n, false);
    fft(y0, n, false), fft(y1, n, false);
    static complex<LD> z0[N], z1[N], z2[N];
    repn(i, n) {
        z0[i]=x0[i]*y0[i];
        z1[i]=x0[i]*y1[i]+x1[i]*y0[i];
        z2[i]=x1[i]*y1[i];
    }
    fft(z0, n, true), fft(z1, n, true), fft(z2, n, true);
    vint64 r(min(n, size));
    repn(i, n) {
        r[i%size]+=LL(real(z0[i])/n+0.5);
        r[i%size]+=LL(real(z1[i])/n+0.5)%MOD<<15;
        r[i%size]+=LL(real(z2[i])/n+0.5)%MOD<<30;
        r[i%size]%=MOD;
    }
    return r;
}


LL compute(int n, int p, int d) {
    //printf("%d %d %d\n",n,p,d);
    VL a={1};
    VL b={100-p, p};
    for(; n>0; n>>=1, b=convolute(b, b, d)) {
        if(n&1) a=convolute(a, b, d);
    }
    //cout<<a<<endl;
    LL ans=0;
    replr(i, 1, d) {
        if(i>=sz(a)) break;
        (ans+=a[i]*(d-i))%=MOD;
    }
    return ans;
}

vector<bool> knapsack(VI a, int n) {
    vector<bool> f(n+1, false);
    f[0]=true;
    for(int x: a) {
        rep(i, x, n) f[i]=f[i]||f[i-x];
    }
    return f;
}

LL power(LL x, LL y) {
    LL r=1;
    for(; y>0; y>>=1, x=x*x%MOD)
        if(y&1) r=r*x%MOD;
    return r;
}

int solve(int n, int p, VI c) {
    sort(all(c));

    int d=c[0];
    for(int x: c) d=gcd(d, x);
    int lim=c.back();
    if(sz(c)>=2) lim*=c[sz(c)-2];
    VL inv(lim+2);
    rep(i, 1, lim+1) inv[i]=power(i, MOD-2);

    LL ans=compute(n, p, d);
    vector<bool> f=knapsack(c, lim);
    int cur=0;
    LL binom=1;
    rep(i, 0, min(n,lim)) {
        while(cur<i || !f[cur]) ++cur;
        int delta=cur-i;
        int fake_delta=(d-i%d)%d;
        //printf("%d %d %d\n",i,delta,fake_delta);
        LL val=power(p, i)*power(100-p, n-i)%MOD*binom%MOD;
        //cout<<"val: "<<val<<endl;
        //cout<<"binom: "<<binom<<endl;
        (ans+=(delta-fake_delta)*val)%=MOD;
        binom=binom*(n-i)%MOD*inv[i+1]%MOD;
    }
    ans=(ans%MOD+MOD)%MOD;
    return int(ans);
}

int main() {
    int csn; scanf("%d", &csn);
    repn(cs, csn) {
        int n, m, p; scanf("%d%d%d", &n,&m,&p);
        VI c(m); repn(i, m) scanf("%d", &c[i]);
        int ans=solve(n, p, c);
        printf("Case #%d: %d\n", cs+1,ans);
    }
    return 0;
}
