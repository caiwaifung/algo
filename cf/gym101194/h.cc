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

const int N=220;
const LL MOD=LL(1e9)+7;

LL binom[N][N], power[N][N*N], fac[N];

void precompute() {
    fillchar(binom, 0);
    repn(i, N) {
        binom[i][0]=binom[i][i]=1;
    }
    repn(i, N) rep(j, 1, i-1) {
        binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%MOD;
    }

    fillchar(power, 0);
    repn(i, N) {
        power[i][0]=1;
        replr(j, 1, N*N) {
            power[i][j]=power[i][j-1]*i%MOD;
        }
    }

    fac[0]=1;
    replr(i, 1, N) {
        fac[i]=fac[i-1]*i%MOD;
    }
}

void solve(int cs) {
    int n, m, k0; scanf("%d%d%d", &n, &m, &k0);

    static LL f[N][N];

    const auto T=[&](int p, int t, int k) {
        LL r=1;
        (r*=binom[n-p][t])%=MOD;
        (r*=binom[m-p][t])%=MOD;
        (r*=fac[t])%=MOD;
        (r*=power[k-1][(n-p)*(m-p)-(n-p-t)*(m-p-t)-t])%=MOD;
        return r;
    };

    fillchar(f, 0);
    f[0][0]=1;
    rep(k, 1, k0) rep(p, 0, min(n, m)) {
        f[k][p]=f[k-1][p];
        rep(t, 1, p) {
            (f[k][p]+=f[k-1][p-t]*T(p-t, t, k))%=MOD;
        }
    }

    static LL b[N], a[N];
    rep(g, 0, min(n, m)) {
        b[g]=(f[k0][g]*power[k0][(n-g)*(m-g)])%MOD;
        //printf("b[%d]=%d\n",g,(int)b[g]);
    }
    irep(g, min(n, m), 0) {
        LL s=b[g];
        rep(g2, g+1, min(n, m)) {
            (s-=a[g2]*binom[g2][g])%=MOD;
        }
        (s+=MOD)%=MOD;
        a[g]=s;
    }
    LL ans=0;
    rep(g, 0, min(n, m)) {
        (ans+=a[g]*(g+1))%=MOD;
    }
    printf("Case #%d: %d\n", cs, (int)ans);
}

int main() {
    precompute();
    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        solve(i);
    }
    return 0;
}
