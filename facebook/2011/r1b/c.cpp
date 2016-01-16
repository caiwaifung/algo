// 9:24
// 9:27 - 9:36 - ac
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

int g(int x) {
    x = int((LL(x) * 5402147 + 54321) % 10000001);
    return x;
}

void solve(int cs) {
    int n; scanf("%d", &n);
    VI a((size_t)n); for(int& x: a) scanf("%d", &x);
    VI ans, tmp;
    printf("Case #%d: ", cs);
    for(int first=a[0]; first<10000001; first+=1000) {
        bool ok=true;
        int secret=first;
        for(int x: a) {
            if(secret%1000 != x) { ok=false; break; }
            secret=g(secret);
        }
        if(ok) {
            tmp.clear();
            repn(i, 10) {
                tmp.pb(secret%1000);
                secret=g(secret);
            }
            if(ans.size()==0) ans=tmp;
            else {
                if(ans!=tmp) {
                    printf("Not enough observations\n");
                    return;
                }
            }
        }
    }
    if(ans.size()>0) {
        for(int x: ans) printf("%d ", x); printf("\n");
    } else {
        printf("Wrong machine\n");
    }
}

int main() {
    freopen("/Users/fqw/Downloads/slot_machine_hacker.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) {
        fprintf(stderr, "[%d/%d]\n",cs,csn);
        solve(cs);
    }
    return 0;
}
