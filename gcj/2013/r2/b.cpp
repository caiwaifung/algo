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

LL N, P;

void init() {
    cin>>N>>P;
    N=1LL<<N;
}

bool ok1(LL n, LL k, LL p) {
    if(k==0) return true;
    if(p<=n/2) return false;
    return ok1(n/2, (k-1)/2, p-n/2);
}

LL solve1() {
    LL le=0, ri=N-1;
    while(le<ri) {
        LL mid=(le+ri+1)/2;
        if(ok1(N, mid, P))
            le=mid;
        else
            ri=mid-1;
    }
    return le;
}

bool ok2(LL n, LL k, LL p) {
    //cout<<n<<" "<<k<<" "<<p<<endl;
    if(p==n) return true;
    LL r=n-k-1;
    if(r==0) return false;
    r=(r-1)/2;
    k=n/2-r-1; assert(k>=0 && k<n/2);
    p=min(p, n/2);
    return ok2(n/2, k, p);
}

LL solve2() {
    LL le=0, ri=N-1;
    while(le<ri) {
        LL mid=(le+ri+1)/2;
        //cout<<mid<<endl;
        if(ok2(N, mid, P))
            le=mid;
        else
            ri=mid-1;
    }
    return le;
}

void solve(int cs) {
    LL ans1=solve1();
    LL ans2=solve2();
    printf("Case #%d: ", cs);
    cout<<ans1<<" "<<ans2<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
