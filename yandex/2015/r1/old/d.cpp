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

LL solve(LL n, LL r) {
    if(r<0) return 0;
    const int len=66;
    LL f[len+1][2][2]; fillchar(f, 0);
    f[0][0][0]=1;
    repn(i, len) {
        int n0=int(n%2), r0=int(r%2); n/=2, r/=2;
        repn(carry, 2) repn(gt, 2) {
            bool ok[2]; fillchar(ok, false);
            repn(x, 2) ok[(n0+carry+x)/2]=true;
            repn(carry2, 2) if(ok[carry2]) {
                int cur=n0^carry;
                int gt2=(cur==r0)?gt:(cur>r0);
                f[i+1][carry2][gt2]+=f[i][carry][gt];
            }
        }
    }
    return f[len][0][0];
}

int main() {
    LL n, l, r; cin>>n>>l>>r;
    LL ans=solve(n, r)-solve(n, l-1);
    cout<<ans<<endl;
    return 0;
}
