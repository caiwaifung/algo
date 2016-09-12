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

const LL MOD=LL(1e9)+7;
const int N=300010;

LL m2[N], m3[N], inv[N], fac[N], inv_fac[N];

void pre() {
    m2[0]=m3[0]=1;
    rep(i, 1, N-1) {
        m2[i]=m2[i-1]*2%MOD;
        m3[i]=m3[i-1]*3%MOD;
    }
    inv[1]=1;
    rep(i, 2, N-1) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
    fac[0]=inv_fac[0]=1;
    rep(i, 1, N-1) {
        fac[i]=fac[i-1]*i%MOD;
        inv_fac[i]=inv_fac[i-1]*inv[i]%MOD;
    }
}

LL binom(int n, int r) {
    if(r<0 || r>n) return 0;
    LL ans=fac[n]*inv_fac[r]%MOD*inv_fac[n-r]%MOD;
    return ans;
}

int cn, cs, ct;
LL cans;

LL query(int n, int s, int t) {
    while(cn<n) {
        cans=(cans*2+binom(cn, cs-1)-binom(cn, ct))%MOD;
        ++cn;
    }
    while(cs<s) cans=(cans-binom(cn, cs++))%MOD;
    while(cs>s) cans=(cans+binom(cn, --cs))%MOD;
    while(ct<t) cans=(cans+binom(cn, ++ct))%MOD;
    while(ct>t) cans=(cans-binom(cn, ct--))%MOD;
    cans=(cans+MOD)%MOD;
    return cans;
}

int main() {
    ios_base::sync_with_stdio(false);

    pre();
    int n, m, k; cin>>n>>m>>k; --n;

    cn=cs=ct=0, cans=1;
    LL ans=0;
    rep(p, 0, m+k) {
        LL cur=m3[m+k-p];
        (cur*=binom(n+p, n))%=MOD;
        (cur*=query(p, max(0,p-k), min(p,m)))%=MOD;
        (ans+=cur)%=MOD;
    }
    cout<<ans<<endl;

    return 0;
}
