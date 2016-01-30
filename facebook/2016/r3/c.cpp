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

LL px[MAXN], py[MAXN];
int n;

void read_input() {
    int s; scanf("%d%d", &n,&s);
    static PII a[MAXN];
    rep(i, 1, n) {
        int x, k; scanf("%d%d", &x,&k);
        a[i]=mp(k, x);
    }
    sort(a+1, a+n+1);
    rep(i, 1, n) {
        int x=a[i].se, k=a[i].fi;
        px[i]=x, py[i]=LL(s)*LL(k);
    }
}

LL fv0[MAXN], gv0[MAXN], dv0[MAXN];
int fv[MAXN], gv[MAXN], dv[MAXN];

void dis(LL a[], int ai[]) {
    vector<LL> lst;
    rep(i, 1, n) lst.pb(a[i]);
    sort(all(lst));
    lst.erase(unique(all(lst)), lst.end());
    rep(i, 1, n) {
        ai[i]=int(lower_bound(all(lst), a[i])-lst.begin())+1;
    }
}

template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int _n, T _v) : a(size_t(_n+1), _v), n(_n), v0(_v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]=max(a[(size_t)x], v); }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r=max(r, a[(size_t)x]); return r; }
};

int f[MAXN], g[MAXN], f1[MAXN], g1[MAXN], df[MAXN], dg[MAXN];

int solve() {
    rep(i, 1, n) {
        fv0[i]=py[i]-px[i]; 
        gv0[i]=py[i]+px[i];
        dv0[i]=px[i];
    }
    dis(fv0, fv);
    dis(gv0, gv);
    dis(dv0, dv);

    static int bf[MAXN], bg[MAXN], bf1[MAXN], bg1[MAXN], bdf[MAXN], bdg[MAXN];
    FenwickTree<int> tf1(n,0), tg1(n,0), tdf(n,0), tdg(n,0);
    static PII lst[MAXN];
    int ans=0;

    fillchar(bf1, 0); fillchar(bg1, 0);
    irep(i, n, 1) {
        f1[i]=bf1[fv[i]]+1;
        g1[i]=bg1[gv[i]]+1;
        setmax(bf1[fv[i]], f1[i]);
        setmax(bg1[gv[i]], g1[i]);
    }

    fillchar(bdf, 0); tf1=FenwickTree<int>(n,0);
    rep(i, 1, n) lst[i]=mp(-fv[i], i); sort(lst+1, lst+n+1);
    rep(k, 1, n) { int i=lst[k].se;
        df[i]=max(bdf[dv[i]], tf1.get(n-dv[i]+1))+1;
        setmax(df[i], f1[i]);
        tf1.add(n-dv[i]+1, f1[i]);
        setmax(bdf[dv[i]], df[i]);
    }
    fillchar(bdg, 0); tg1=FenwickTree<int>(n,0);
    rep(i, 1, n) lst[i]=mp(-gv[i], i); sort(lst+1, lst+n+1);
    rep(k, 1, n) { int i=lst[k].se;
        dg[i]=max(bdg[dv[i]], tg1.get(dv[i]))+1;
        setmax(dg[i], g1[i]);
        tg1.add(dv[i], g1[i]);
        setmax(bdg[dv[i]], dg[i]);
    }

    fillchar(bf, 0); tdg=FenwickTree<int>(n,0); tg1=FenwickTree<int>(n,0);
    rep(i, 1, n) lst[i]=mp(-fv[i], -i); sort(lst+1, lst+n+1);
    rep(k, 1, n) { int i=-lst[k].se;
        f[i]=max(bf[fv[i]], (tdg.get(n-dv[i]+1)))+1;
        setmax(f[i], dg[i]);
        tdg.add(n-dv[i]+1, dg[i]);
        //printf("dv[%d]=%d f=%d fv=%d tdg.get=%d\n",i,dv[i], f[i],fv[i],tdg.get(n-dv[i]+1));
        //tg1.add(n-gv[i]+1, g1[i]);
        setmax(bf[fv[i]], f[i]);
        setmax(ans, f[i]);
    }
    fillchar(bg, 0); tdf=FenwickTree<int>(n,0); tf1=FenwickTree<int>(n,0);
    rep(i, 1, n) lst[i]=mp(-gv[i], -i); sort(lst+1, lst+n+1);
    rep(k, 1, n) { int i=-lst[k].se;
        g[i]=max(bg[gv[i]], (tdf.get(dv[i])))+1;
        setmax(g[i], df[i]);
        tdf.add(dv[i], f[i]);
        //tf1.add(n-fv[i]+1, f1[i]);
        setmax(bg[gv[i]], g[i]);
        setmax(ans, g[i]);
    }
    //rep(i, 1, n) printf("%d %d %d %d %d %d\n", f1[i],g1[i],df[i],dg[i],f[i],g[i]);
    
    /*
    fillchar(bf, 0); fillchar(bg, 0);
    fillchar(bf1, 0); fillchar(bg1, 0);
    fillchar(bdf, 0); fillchar(bdg, 0);
    int ans=0;
    irep(i, n, 1) {
        //printf("%d %d %d\n", fv[i],gv[i],dv[i]);
        f1[i]=bf1[fv[i]]+1;
        g1[i]=bg1[gv[i]]+1;
        f[i]=max(bf[fv[i]], max(tg1.get(fv[i]), tdg.get(fv[i])))+1;
        g[i]=max(bg[gv[i]], max(tf1.get(fv[i]), tdf.get(gv[i])))+1;
        df[i]=max(bdf[dv[i]], tf1.get(gv[i]))+1;
        dg[i]=max(bdg[dv[i]], tg1.get(fv[i]))+1;

        setmax(bf1[fv[i]], f1[i]);
        setmax(bg1[gv[i]], g1[i]);
        setmax(bf[fv[i]], f[i]);
        setmax(bg[gv[i]], g[i]);
        setmax(bdf[dv[i]], df[dv[i]]);
        setmax(bdg[dv[i]], dg[dv[i]]);
        tf1.add(gv[i], f1[i]);
        tg1.add(fv[i], g1[i]);
        tdf.add(fv[i], df[i]);
        tdg.add(gv[i], dg[i]);

        setmax(ans, max(f[i], f1[i]));
        setmax(ans, max(g[i], g1[i]));
        setmax(ans, max(df[i], dg[i]));
    }
    */

    return ans;
}

int main() {
    freopen("/Users/fqw/Downloads/umbrella.txt", "r", stdin); freopen("out.txt", "w", stdout);
    int csn; scanf("%d", &csn);
    rep(cs, 1, csn) { fprintf(stderr, "\033[0;31m### [%d/%d]\033[0m\n",cs,csn);
        read_input();
        int ans=solve();
        printf("Case #%d: %d\n", cs, ans);
    }
    return 0;
}

