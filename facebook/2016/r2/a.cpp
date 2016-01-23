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

const int MAXN=100010;

int a[MAXN], b[MAXN];
int n;

void read_input() {
    scanf("%d", &n);
    static char ba[MAXN], bb[MAXN];
    scanf("%s%s", ba+1,bb+1);
    rep(i, 1, n) a[i]=int(ba[i]-'A')+1, b[i]=int(bb[i]-'A')+1;
}

int l[MAXN][27], r[MAXN][27];

int solve() {
    fillchar(l, 0);
    rep(i, 1, n) {
        if(a[i]==b[i]) l[i][0]=l[i-1][0];
            else l[i][0]=1+l[i-1][b[i]];
        rep(c, 1, 26) {
            if(c==b[i]) l[i][c]=l[i-1][c];
                else l[i][c]=1+l[i-1][b[i]];
        }
    }
    fillchar(r, 0);
    irep(i, n, 1) {
        if(a[i]==b[i]) r[i][0]=r[i+1][0];
            else r[i][0]=1+r[i+1][b[i]];
        rep(c, 1, 26) {
            if(c==b[i]) r[i][c]=r[i+1][c];
                else r[i][c]=1+r[i+1][b[i]];
        }
    }

    int ans=1<<30;
    rep(i, 0, n) setmin(ans, max(l[i][0],r[i+1][0]));

    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/boomerang_decoration.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

