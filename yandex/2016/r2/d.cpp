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

struct Mat {
    LL a[100][100];
};
Mat mul(const Mat& a, const Mat& b) {
    Mat c; fillchar(c.a, 0);
    repn(k, 100) {
        repn(i, 100) repn(j, 100) (c.a[i][j]+=a.a[i][k]*b.a[k][j])%=MOD;
    }
    return c;
}
Mat pow(Mat a, LL b) {
    Mat c; fillchar(c.a, 0); repn(i, 100) c.a[i][i]=1;
    for(; b>0; b>>=1, a=mul(a,a))
        if(b&1) c=mul(c, a);
    return c;
}

LL f[100][100], s[100];
LL A, B, C;

int main() {
    cin>>A>>B>>C;

    repn(i, 100) f[i][0]=f[0][i]=1;
    rep(i, 1, 99) rep(j, 1, 99) f[i][j]=(f[i-1][j]+f[i][j-1])%MOD;
    fillchar(s, 0);
    repn(x, 100) repn(y, 100) {
        LL t=A*x+B*y;
        if(t<100) (s[t]+=f[x][y])%=MOD;
    }

    Mat T; fillchar(T.a, 0);
    repn(i, 99) T.a[i][i+1]=1;
    T.a[99][100-A]++, T.a[99][100-B]++;
    T=pow(T, C);

    LL ans=0;
    repn(i, 100) (ans+=T.a[0][i]*s[i])%=MOD;
    cout<<ans<<endl;
    
    return 0;
}
