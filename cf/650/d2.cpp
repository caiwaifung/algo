// 14:20 - 15:00
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

struct Val {
    static const LL MOD=LL(1e9)+7;

    int val; LL cnt;
    Val() : val(0), cnt(0) {}
    Val(int v, LL c) : val(v), cnt(c) {}
    Val advance() const {
        return Val(val+1, cnt);
    }

    friend Val operator+(const Val& a, const Val& b) {
        if(a.val>b.val) return a;
        if(a.val<b.val) return b;
        return Val(a.val, (a.cnt+b.cnt)%MOD);
    }
    void operator +=(const Val& b) {
        *this = *this + b;
    }
    friend Val operator*(const Val& a, const Val& b) {
        return Val(a.val+b.val, (a.cnt*b.cnt)%MOD);
    }
};

struct FenwickTree {
    Val tr[MAXNUM];

    void clear() {
        fill(tr, tr+MAXNUM, Val());
    }
    void add(int x, Val v) {
        for(; x<MAXNUM; x+=x&-x) tr[x]+=v;
    }
    Val get(int x) const {
        Val r;
        for(; x>=1; x-=x&-x) r+=tr[x];
        return r;
    }
};

struct Query {
    int i, new_val;
    int f[2];
};

struct Pos {
    int val;
    vector<Query*> qs;
    Val f[2];
};

int discretize(vector<Pos>* as, vector<Query>* qs) {
    VI vs;
    for(const auto& a: *as) vs.pb(a.val);
    for(const auto& q: *qs) vs.pb(q.new_val);
    sort(all(vs));
    vs.erase(unique(all(vs)), vs.end());
    auto get=[&vs](int v) { return int(lower_bound(all(vs), v)-vs.begin())+1; };
    for(auto& a: *as) a.val=get(a.val);
    for(auto& q: *qs) q.new_val=get(q.new_val);
    return int(vs.size());
}

Val go(vector<Pos>* as, int o) {
    static FenwickTree tr;
    tr.clear();

    Val ans;
    for(auto& a: *as) {
        a.f[o]=Val(0,1)+tr.get(a.val-1);
        for(auto& q: a.qs) {
            q->f[o]=tr.get(q->new_val-1).val;
        }
        ans+=a.f[o].advance();
        tr.add(a.val, a.f[o].advance());
    }
    return ans;
}

int main() {
    int n, m; scanf("%d%d", &n,&m);
    vector<Pos> as(n);
    vector<Query> qs(m);
    for(auto& a: as) scanf("%d", &a.val);
    for(auto& q: qs) {
        scanf("%d%d", &q.i, &q.new_val);
        --q.i; as[q.i].qs.pb(&q);
    }
    int maxval=discretize(&as, &qs);

    Val ans1=go(&as, 0);

    reverse(all(as));
    for(auto& a: as) a.val=maxval-a.val+1;
    for(auto& q: qs) q.new_val=maxval-q.new_val+1;
    Val ans2=go(&as, 1);
    reverse(all(as));

    assert(ans1.val==ans2.val && ans1.cnt==ans2.cnt);
    for(const auto& q: qs) {
        int cur=q.f[0]+q.f[1]+1;
        if(cur>=ans1.val) printf("%d\n", cur);
        else {
            int i=q.i;
            Val tmp=(as[i].f[0]*as[i].f[1]).advance();
            if(tmp.val==ans1.val && tmp.cnt==ans1.cnt)
                printf("%d\n", ans1.val-1);
            else
                printf("%d\n", ans1.val);
        }
    }

    return 0;
}
