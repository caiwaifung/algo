#include <cassert>
#include <functional>
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

template<class T> class SegmentTree {
    std::vector<T> tr;
    int n; int v0;

    void release(int x) {
        if(tr[x]!=v0) {
            tr[x*2]=tr[x*2+1]=tr[x];
            tr[x]=v0;
        }
    }
    void _paint(int x, int s, int t, int st, int en, int val) {
        if(st<=s && t<=en) {
            tr[x]=val; return;
        }
        release(x);
        int mid=(s+t)/2;
        if(st<=mid) _paint(x*2, s, mid, st, en, val);
        if(mid<en) _paint(x*2+1, mid+1, t, st, en, val);
    }
    T _get(int x, int s, int t, int ind) {
        if(s==t || tr[x]!=v0)
            return tr[x];
        release(x);
        int mid=(s+t)/2;
        if(ind<=mid) return _get(x*2, s, mid, ind);
            else return _get(x*2+1, mid+1, t, ind);
    }
public:
    SegmentTree() { }
    SegmentTree(int _n, T _v) : tr(size_t(_n+1)*4, _v), n(_n), v0(_v) { }
    void paint(int l, int r, T v) { _paint(1, 1, n, l, r, v); }
    T get(int x) { return _get(1, 1, n, x); }
};

template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int _n, T _v) : a(size_t(_n+1), _v), n(_n), v0(_v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]+=v; }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r+=a[(size_t)x]; return r; }
};

const int MAXN=500050;

char op[MAXN]; int ox[MAXN], oy[MAXN];
int n, m;
int ind[MAXN], pos[MAXN], l[MAXN], r[MAXN];
int last_clear[MAXN]; VI to_clear[MAXN];
LL ans[MAXN];

void pre(int c1, int c2) {
    vector<bool> here(n+1, true);
    vector<VI> sons(n+1);
    rep(k, 1, m) if(op[k]==c1) {
        sons[ox[k]].pb(oy[k]);
        here[oy[k]]=false;
    }
    int cnt=0;
    function<void(int)> dfs=[&cnt, &dfs, &sons](int x) -> void {
        ++cnt;
        ind[cnt]=x, pos[x]=cnt;
        for(int y: sons[x]) dfs(y);
    };
    rep(i, 1, n) if(here[i]) dfs(i);

    static PII p[MAXN];
    rep(i, 1, n) p[i]=mp(pos[i], pos[i]);
    rep(k, 1, m) {
        auto merge=[](PII a, PII b) { return mp(min(a.fi, b.fi), max(a.se, b.se)); };
        if(op[k]==c1) { p[ox[k]]=merge(p[ox[k]], p[oy[k]]); }
        if(op[k]==c2) {
            l[k]=p[ox[k]].fi;
            r[k]=p[ox[k]].se;
        }
    }
}

int main() {
    scanf("%d%d", &n,&m);
    rep(i, 1, m) {
        scanf("%s", op+i);
        scanf("%d", &ox[i]);
        if(op[i]=='U' || op[i]=='M')
            scanf("%d", &oy[i]);
    }

    pre('M', 'Z');
    fillchar(last_clear, 0);
    SegmentTree<int> tmax(n, 0);
    rep(k, 1, m) {
        if(op[k]=='Z') { tmax.paint(l[k], r[k], k); }
        if(op[k]=='Q') last_clear[k]=tmax.get(pos[ox[k]]);
    }
    rep(k, 0, m) to_clear[k].clear();
    rep(k, 1, m) to_clear[last_clear[k]].pb(k);

    //rep(k, 1, m) if(op[k]=='Q') printf("last_clear[%d]=%d\n",k,last_clear[k]);

    pre('U', 'A');
    FenwickTree<LL> tsum(n, 0);
    rep(k, 1, m) {
        if(op[k]=='A') {
            int v=r[k]-l[k]+1;
            tsum.add(l[k], v);
            tsum.add(r[k]+1, -v);
        }
        if(op[k]=='Q') {
            ans[k]+=tsum.get(pos[ox[k]]);
        }
        for(int k2: to_clear[k])
            ans[k2]-=tsum.get(pos[ox[k2]]);
    }
    rep(k, 1, m) if(op[k]=='Q') printf("%lld\n", ans[k]);

    return 0;
}
