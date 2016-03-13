#include <cassert>
#include <algorithm>
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

const int MAXN=400010;
const int MAXQ=400010;
const int MAXNUM=MAXN+MAXQ;

int a[MAXN], qpos[MAXQ], qv[MAXQ];
VI qs[MAXN];
int n, qn, num;

void discretize() {
    VI vs;
    rep(i, 1, n) vs.pb(a[i]);
    rep(i, 1, qn) vs.pb(qv[i]);
    sort(all(vs));
    vs.erase(unique(all(vs)), vs.end());
    num=(int)vs.size();
    auto get=[&vs](int x) { return int(lower_bound(all(vs), x)-vs.begin())+1; };
    rep(i, 1, n) a[i]=get(a[i]);
    rep(i, 1, qn) qv[i]=get(qv[i]);
}

struct Val {
    static const LL MOD=LL(1e9)+7;
    int v; LL c;
    Val() : v(0), c(0) {}
    void update(const Val &b) {
        if(b.v>v) v=b.v, c=0;
        if(b.v==v) (c+=b.c)%=MOD;
    }
    Val add(int x) const {
        Val b; b.v=v+x; b.c=c;
        return b;
    }
    Val times(const Val &b) const {
        Val r;
        r.v=v+b.v;
        r.c=(c*b.c)%MOD;
        return r;
    }
    void print() const { printf("%d %lld\n", v,c); }
};

Val tr[MAXNUM];
Val get(int x) {
    Val r; r.c=1;
    for(; x>=1; x-=x&-x) r.update(tr[x]);
    return r;
}
void add(int x, Val v) {
    for(; x<=num; x+=x&-x) tr[x].update(v);
}

void go(Val l[], int ql[], Val& ans) {
    fill(tr, tr+MAXNUM, Val());
    ans=Val();
    rep(i, 1, n) {
        l[i]=get(a[i]-1);
        for(int k: qs[i]) ql[k]=get(qv[k]-1).v;
        ans.update(l[i].add(1));
        add(a[i], l[i].add(1));
    }
}

Val l[MAXN], r[MAXN], ansl, ansr;
int ql[MAXQ], qr[MAXQ];

int main() {
    scanf("%d%d", &n,&qn);
    rep(i, 1, n) scanf("%d", &a[i]), qs[i].clear();
    rep(k, 1, qn) scanf("%d%d", &qpos[k], &qv[k]), qs[qpos[k]].pb(k);
    discretize();

    go(l, ql, ansl);

    rep(i, 1, n) a[i]=num-a[i]+1;
    rep(k, 1, qn) qv[k]=num-qv[k]+1;
    reverse(a+1, a+n+1);
    reverse(qs+1, qs+n+1);
    go(r, qr, ansr);
    reverse(r+1, r+n+1);

    assert(ansl.v==ansr.v && ansl.c==ansr.c);
    rep(k, 1, qn) {
        int cur=ql[k]+qr[k]+1;
        if(cur>=ansl.v) printf("%d\n", cur);
        else {
            int i=qpos[k];
            Val tmp=l[i].times(r[i]).add(1);
            if(tmp.v!=ansl.v || tmp.c!=ansl.c)
                printf("%d\n", ansl.v);
            else
                printf("%d\n", ansl.v-1);
        }
    }

    return 0;
}
