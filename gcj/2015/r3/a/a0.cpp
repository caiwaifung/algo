#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
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

template<class T> class FenwickTree {
    std::vector<T> a;
    int n; T v0;
public:
    FenwickTree() { }
    FenwickTree(int n, T v) : a(size_t(n+1), v), n(n), v0(v) { }
    void add(int x, T v) { for(; x<=n; x+=(x&-x)) a[(size_t)x]+=v; }
    T get(int x) const { T r=v0; for(; x>=1; x-=(x&-x)) r+=a[(size_t)x]; return r; }
};

const int MAXN=1000010;

LL s[MAXN]; int fa[MAXN], lc[MAXN], rc[MAXN];
int n; LL limit;

int st[MAXN], en[MAXN], tot;
void dfs(int x) {
    st[x]=++tot;
    for(int y=lc[x]; y; y=rc[y])
        dfs(y);
    en[x]=tot;
}

void init() {
    cin>>n>>limit;
    LL s0, as, cs, rs; cin>>s0>>as>>cs>>rs;
    s[1]=s0;
    forint(i, 2, n) s[i]=(s[i-1]*as+cs)%rs;

    LL m0, am, cm, rm; cin>>m0>>am>>cm>>rm;
    static LL m[MAXN];
    m[1]=m0;
    forint(i, 2, n) m[i]=(m[i-1]*am+cm)%rm;
    fa[1]=-1;
    forint(i, 2, n) {
        fa[i]=int(m[i]%(i-1));
    }

    fillchar(lc, 0);
    fillchar(rc, 0);
    forint(i, 2, n) {
        rc[i]=lc[fa[i]];
        lc[fa[i]]=i;
    }

    tot=0;
    dfs(1);
}

int ans, delta;
bool ok_head;

int f[MAXN], fs[MAXN]; 
int gf(int x) {
    return f[x]==0 ? x : (f[x]=gf(f[x]));
}
void unite(int x, int y) {
    x=gf(x), y=gf(y);
    if(x!=y) f[x]=y, fs[y]+=fs[x];
}

FenwickTree<int> disabled;
FenwickTree<int> dsum;

void add(int i) {
    if(i==1) ok_head=true;
    if(disabled.get(st[i])>0) return;
    if(fa[i]>0) unite(i, fa[i]);

    if(ok_head) {
        int tmp=fs[gf(1)]+delta;
        setmax(ans, tmp);
    }
}

void del(int i) {
    if(i==1) ok_head=false;
    if(disabled.get(st[i])>0) return;
    disabled.add(st[i], 1);
    disabled.add(en[i]+1, -1);


}

void solve(int cs) {
    vector<pair<LL,int> > full;
    forint(i, 1, n) full.PB(MP(s[i], i));
    sort(all(full));

    disabled=FenwickTree<int>(n, 0);
    dsum=FenwickTree<int>(n, 0);
    fillchar(f, 0);
    forint(i, 1, n) fs[i]=1;
    ok_head=false;

    ans=0;
    size_t la=0;
    forn(i, full.size()) {
        while(full[la].fi+limit<full[i].fi)
            del(full[la].se), ++la;
        add(full[i].se);
    }

    printf("Case #%d: ", cs);
    cout<<ans<<endl;
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
