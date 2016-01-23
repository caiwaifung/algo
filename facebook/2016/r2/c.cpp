#include <algorithm>
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

const int MAXN=200010;
const LL MOD=LL(1e9)+7;

int n, x[MAXN], h[MAXN];

void read_input() {
    static PII t[MAXN];
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d%d",&t[i].fi,&t[i].se);
    sort(t+1, t+n+1);
    rep(i, 1, n) x[i]=t[i].fi, h[i]=t[i].se;
}

struct T {
    LL h;
    LL num, sum, sum2;
    T(LL h0, LL x0) : h((LL)h0) {
        num=1; sum=x0; sum2=x0*x0%MOD;
    }
    LL push(LL x2) {
        LL r=LL(x2)*LL(x2)%MOD*num%MOD;
        (r+=sum2)%=MOD;
        (r-=2*x2*sum)%=MOD;
        (r+=MOD)%=MOD;
        ++num; (sum+=x2)%=MOD; (sum2+=LL(x2)*LL(x2))%=MOD;
        return r;
    }
};

int solve() {
    vector<T> st;
    LL ans=0;
    rep(i, 1, n) {
        while(!st.empty() && st.back().h<h[i])
            st.pop_back();
        if(!st.empty() && st.back().h==h[i]) {
            (ans+=st[st.size()-1].push(x[i]))%=MOD;
        } else {
            st.pb(T(h[i], x[i]));
        }
    }
    return int(ans);
}

int main() {
    freopen("/Users/fqw/Downloads/snakes_and_ladders.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

