// 10:18
// 10:22 - 10:26 - ac
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//{{{
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
template<class T> T absv(T _x) { return _x>0?_x:-_x; }
//}}}

const int N=50050;

int a[N];
int n;

void read_input() {
    scanf("%d", &n); rep(i, 1, n) scanf("%d", &a[i]);
}

bool solve0(int le, int ri, int p) {
    int x=p, y=p;
    while(le<=ri) {
        if(a[le]==x-1) { --x; ++le; continue; }
        if(a[le]==y+1) { ++y; ++le; continue; }
        if(a[ri]==x-1) { --x; --ri; continue; }
        if(a[ri]==y+1) { ++y; --ri; continue; }
        return false;
    }
    return true;
}

int solve() {
    if(solve0(2, n, a[1])) return 1;
    if(solve0(1, n-1, a[n])) return 1;
    return 0;
}

int main() {
    freopen("/Users/fqw/Downloads/lazy_sort.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %s\n", cs, ans?"yes":"no");
    }
    return 0;
}

