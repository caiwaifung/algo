// 12:43
// 12:47 - 12:57
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

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

const int N=100010;

int a[N], f[N];
int n; 

void init() {
    scanf("%d", &n); rep(i, 1, n) scanf("%d", &a[i]);
}

bool ok(int i, int j) {
    int cnt=0;
    rep(k, i+1, j) {
        if(a[k-1]>=a[k]) return false;
        cnt+=(a[k]-a[k-1]-1)/10;
    }
    return (j-i+1)+cnt<=4;
}

int solve() {
    fillchar(f, 50); f[0]=0;
    rep(i, 1, n) {
        rep(j, 1, 4) if(i-j>=0)
            if(ok(i-j+1, i)) {
                setmin(f[i], f[i-j]+4-j);
            }
    }
    return f[n];
}

void do_tests();
int main() {
    freopen("/Users/fqw/Downloads/coding_contest_creation.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) {
        fprintf(stderr, "[%d/%d]\n",cs,csn);
        init();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

// ----------------------------------------------
// Tests
// ----------------------------------------------
void gen() {
    n=10+rand()%5;
    rep(i, 1, n) a[i]=rand()%100+1;
}

int solve_vio() {
}

void do_tests() {
    gen();
    int ans=solve();
    int std=solve_vio();
}
