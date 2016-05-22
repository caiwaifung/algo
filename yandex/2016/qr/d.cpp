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

LL f[66][2][2], c[66][2][2];
int a[66], len;

int main() {
    LL N; cin>>N;
    len=0; while(N>0) {
        a[++len]=int(N%2), N/=2;
    }
    reverse(a+1, a+len+1);

    fillchar(f, 0); fillchar(c, 0);
    f[0][0][1]=f[0][1][1]=0;
    c[0][0][1]=1, c[0][1][1]=0;
    rep(i, 1, len) repn(end, 2) repn(same, 2) {
        int bound=same?a[i]:1;
        rep(cur, 0, bound) if(cur==end) {
            (f[i][cur][same&&cur==bound]+=f[i-1][end][same])%=MOD;
            (c[i][cur][same&&cur==bound]+=c[i-1][end][same])%=MOD;
        } else {
            (f[i][cur][same&&cur==bound]+=f[i-1][end][same]*2+c[i-1][end][same]*cur)%=MOD;
            (c[i][cur][same&&cur==bound]+=c[i-1][end][same])%=MOD;
        }
    }
    LL ans=0;
    repn(end, 2) repn(same, 2) (ans+=f[len][end][same])%=MOD;
    cout<<ans<<endl;

    return 0;
}
