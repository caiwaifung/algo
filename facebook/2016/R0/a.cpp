// 6:30 - 6:46
#include <cassert>
#include <cstring>
#include <map>
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

void solve(int cs) {
    int ans=0;
    int n; scanf("%d", &n);
    VPI a(n); repn(i, n) scanf("%d%d", &a[i].fi,&a[i].se);
    repn(i, n) {
        map<int, int> cnt;
        repn(j, n) {
            auto sqr=[](int x) { return x*x; };
            int d=sqr(a[i].fi-a[j].fi)+sqr(a[i].se-a[j].se);
            cnt[d]++;
        }
        for(auto& c: cnt) ans+=c.se*(c.se-1)/2;
    }
    printf("Case #%d: %d\n", cs,ans);
}

int main() {
    int t; scanf("%d", &t);
    rep(cs, 1, t) solve(cs);
    return 0;
}
