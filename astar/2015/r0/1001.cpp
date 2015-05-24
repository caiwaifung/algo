#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //
const int MOD=int(1e9)+7;
int inv(int x) {
    int y=MOD-2, ans=1;
    for(; y>0; y>>=1, x=int(LL(x)*LL(x)%MOD))
        ans=int(LL(ans)*LL(x)%MOD);
    return ans;
}

int main() {
    const int N=1000000;
    static int f[1001000];
    //fac[0]=1; forint(i, 1, N) fac[i]=int(LL(fac[i-1])*i%MOD);
    //forint(i, 0, N) ifac[i]=inv(fac[i]);

    f[0]=1;
    forint(i, 1, N) {
        f[i]=f[i-1];
        if(i>=2) {
            LL tmp=f[i-2];
            (tmp*=i-1)%=MOD;
            f[i]=int((f[i]+tmp)%MOD);
        }
    }

    int t; scanf("%d", &t);
    int cs=0;
    while(t--) {
        int n; scanf("%d", &n);
        printf("Case #%d:\n%d\n",++cs, f[n]);
    }
    return 0;
}
