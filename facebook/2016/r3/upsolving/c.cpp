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

template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int _n, T _v) : a(size_t(_n+1), _v), n(_n), v0(_v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]=max(a[(size_t)x], v); }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r=max(r, a[(size_t)x]); return r; }
};

const int MAXN=100010;

PLL a[MAXN];
int n;

void read_input() {
    int s; scanf("%d%d", &n,&s);
    rep(i, 1, n) scanf("%lld%lld", &a[i].fi,&a[i].se);
    rep(i, 1, n) a[i].se*=s;
}

LL fv0[MAXN], gv0[MAXN];
int fv[MAXN], gv[MAXN];

void discretize(LL p[], int pi[]) {
    VL tmp;
    rep(i, 1, n) tmp.pb(p[i]);
    sort(all(tmp));
    tmp.erase(unique(all(tmp)), tmp.end());
    rep(i, 1, n) pi[i]=int(lower_bound(all(tmp), p[i])-tmp.begin())+1;
}

int solve() {
    sort(a+1, a+n+1);
    rep(i, 1, n) {
        fv0[i]=a[i].se-a[i].fi;
        gv0[i]=a[i].se+a[i].fi;
    }
    discretize(fv0, fv);
    discretize(gv0, gv);

    FenwickTree<int> tf(n, 0), tg(n, 0);
    vector<int> bf(n+1, 0), bg(n+1, 0);
    int ans=0;
    for(int l=1, r; l<=n; l=r+1) {
        for(r=l; r<n && a[r+1].fi==a[l].fi; ++r);
        int best=0;
        rep(i, l, r) {
            int zf=tf.get(fv[i]);
            int zg=tg.get(n-gv[i]+1);
            setmax(best, zf); ++best;
            setmax(ans, zg+best);
        }
        
        rep(i, l, r) {
            int f=++bf[fv[i]], g=++bg[gv[i]];
            tf.add(fv[i], f);
            tg.add(n-gv[i]+1, g);
        }
    }
    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/umbrella.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) {
        fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        rep(i, 1, n) a[i].fi=-a[i].fi;
        setmax(ans, solve());
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

