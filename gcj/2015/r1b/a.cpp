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

LL n;

void init() {
    cin>>n;
}

LL rev(LL x) {
    LL y=0;
    while(x>0) y=y*10+x%10, x/=10;
    return y;
}

void solve(int cs) {
    LL cur=0, ans=0, z=0;
    while(cur<n) {
        ++cur, ++ans;
        z=z*10+9;
        LL target=min(z, n);

        LL tmp1=target-cur;

        LL tmp2=1;
        assert(rev(cur)==1);
        LL d=target-rev(cur);
        LL x=1, y=1; while(y*10<=z) y*=10;
        while(d>0) {
            LL t=d%10; d/=10;
            tmp2+=t*min(x, y);
            x*=10, y/=10;
        }
        ans+=min(tmp1, tmp2);
        cur=target;
    }

    printf("Case #%d: ", cs);
    cout<<ans<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
