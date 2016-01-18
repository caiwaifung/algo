// 10:13
// 10:15 - 10:24 - ac
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#define _ (size_t)

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

VI a, b;

void read_input() {
    int n;
    scanf("%d", &n); a.resize((size_t)n+1); for(int& x: a) scanf("%d", &x);
    scanf("%d", &n); b.resize((size_t)n+1); for(int& x: b) scanf("%d", &x);
}

void add(VI& x, int i, int v) {
    if(x.size()<=(size_t)i)
        x.resize((size_t)i+1);
    x[(size_t)i]+=v;
}

VI solve() {
    VI ans;
    while(a.size()>0) {
        if(a.back()==0) {
            a.pop_back(); continue;
        }
        if(a.size()<b.size()) return VI();
        if(a.back()%b.back()!=0) return VI();
        int c=a.back()/b.back();
        rep(i, 1, b.size())
            a[a.size()- _ i]-=b[b.size()- _ i]*c;
        add(ans, int(a.size()-b.size()), c);
    }
    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/polynomial_factoring.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        VI ans=solve();
        printf("Case #%d: ", cs);
        if(ans.size()) { for(int x: ans) printf("%d ", x); printf("\n"); }
            else printf("no solution\n");
    }
    return 0;
}

