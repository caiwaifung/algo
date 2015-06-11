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

struct Level {
    LL L, P;
    int i;
} lev[1010];
int n;

void init() {
    cin>>n;
    forint(i, 1, n) cin>>lev[i].L;
    forint(i, 1, n) cin>>lev[i].P;
    forint(i, 1, n) {
        lev[i].P=100-lev[i].P;
        lev[i].i=i-1;
    }
}

void solve(int cs) {
    sort(lev+1, lev+n+1, [](const Level &a, const Level &b) -> bool 
            {
                LL p1=a.P, l1=a.L;
                LL p2=b.P, l2=b.L;
                LL c1=l1*100+p1*l2;
                LL c2=l2*100+p2*l1;
                if(c1!=c2) return c1<c2;
                return a.i<b.i;
            });

    printf("Case #%d: ", cs);
    forint(i, 1, n) printf("%d ", lev[i].i);
    printf("\n");
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
