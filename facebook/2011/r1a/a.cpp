// 4:26 - 4:36 - WA sample
//      - 5:17 - ac
#include <cassert>
#include <cstring>
#include <set>
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

const LL MOD=LL(1e9)+7;

int main() {
    freopen("/Users/fqw/Downloads/diversity_number.txt", "r", stdin);
    freopen("a.out", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) {
        fprintf(stderr, "%d/%d\n", cs,csn);
        LL ans=0;
        int n; scanf("%d", &n);
        int a[111]; rep(i, 1, n) scanf("%d", &a[i]);
        static LL f[111][111][111];
        fillchar(f, 0);
        a[0]=a[n+1]=0; f[0][n+1][0]=1;
        ans=1;
        /*
        ans=1;
        rep(i, 1, n) (ans+=a[i])%=MOD;
        rep(i, 1, n) rep(j, i+1, n) {
            int x=a[i], y=a[j]; if(x>y) swap(x, y);
            if(y>=2) (f[i][j][y-2]+=x*(y-1))%=MOD;
            if(a[i]<a[j]) (ans+=x*(y-1))%=MOD;
        }
        */
        rep(i, 0, n) irep(j, n+1, i+1) rep(c, 0, n) {
            if(a[i]>a[j]) (ans+=f[i][j][c])%=MOD;
            set<int> t;
            rep(k, i+1, j-1) if(!t.count(a[k])) {
                t.insert(a[k]);
                if(a[k]>=a[i] && a[k]>a[j]) {
                    (f[k][j][c+1]+=f[i][j][c]*(a[k]-c))%=MOD;
                }
            }
            t.clear();
            irep(k, j-1, i+1) if(!t.count(a[k])) {
                t.insert(a[k]);
                if(a[k]>=a[i] && a[k]>=a[j]) {
                    (f[i][k][c+1]+=f[i][j][c]*(a[k]-c))%=MOD;
                }
            }
        }
        printf("Case #%d: %d\n", cs, (int)ans);
    }
    return 0;
}
