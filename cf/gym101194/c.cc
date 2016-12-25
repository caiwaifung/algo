#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define sz(a) static_cast<int>((a).size())
#define fillchar(a, x) memset(a, x, sizeof(a))
#define rep(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define irep(i, a, b) for(int i=int(a); i>=int(b); --i)
#define replr(i, a, b) rep(i, a, (b)-1)
#define reprl(i, a, b) irep(i, (b)-1, a)
#define repn(i, n) rep(i, 0, (n)-1)
#define irepn(i, n) irep(i, (n)-1, 0)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T, class S> ostream& operator<<(ostream& os, const pair<T, S>& v) { return os<<"("<<v.first<<", "<<v.second<<")"; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& v) { os<<"["; repn(i, sz(v)) { if(i) os<<", "; os<<v[i]; } return os<<"]"; }
template<class T> bool setmax(T &_a, T _b) { if(_b>_a) { _a=_b; return true; } return false; }
template<class T> bool setmin(T &_a, T _b) { if(_b<_a) { _a=_b; return true; } return false; }
template<class T> T gcd(T _a, T _b) { return _b==0?_a:gcd(_b,_a%_b); }

const int none=1<<30;

class Tree {
    struct Node {
        int buf=none;
        int val=0, lp=-1;
    };
    const int n;
    vector<Node> tr;

    void update(int x) {
        tr[x].val=max(tr[x*2+1].val, tr[x*2+2].val);
        tr[x].lp=tr[x*2+1].lp;
    }

    void build(int x, int l, int r, const VI& ps) {
        tr[x].buf=none;
        if(l+1==r) {
            tr[x].val=l-ps[l];
            tr[x].lp=ps[l];
            return;
        }
        const int m=(l+r)/2;
        build(x*2+1, l, m, ps);
        build(x*2+2, m, r, ps);
        update(x);
    }

    void push(int x, int, int r, int buf) {
        tr[x].buf=buf;
        tr[x].val=r-1-buf;
        tr[x].lp=buf;
    }

    void release(int x, int l, int r) {
        if(tr[x].buf!=none) {
            const int m=(l+r)/2;
            push(x*2+1, l, m, tr[x].buf);
            push(x*2+2, m, r, tr[x].buf);
            tr[x].buf=none;
        }
    }

    void set(int x, int l, int r, int st, int en, int p) {
        if(st<=l && r<=en) {
            push(x, l, r, p);
            return;
        }
        release(x, l, r);
        const int m=(l+r)/2;
        if(st<m) set(x*2+1, l, m, st, en, p);
        if(m<en) set(x*2+2, m, r, st, en, p);
        update(x);
    }

    int find(int x, int l, int r, int p) {
        if(l+1==r) {
            return l;
        }
        release(x, l, r);
        const int m=(l+r)/2;
        if(tr[x*2+2].lp<=p) {
            return find(x*2+2, m, r, p);
        } else {
            return find(x*2+1, l, m, p);
        }
    }

public:

    Tree(int _n) : n(_n), tr(n*4) {}

    void init(const VI& ps) {
        build(0, 0, n, ps);
    }

    int maxv() const {
        return tr[0].val;
    }

    int find(int p) {
        return find(0, 0, n, p);
    }

    void set(int st, int en, int p) {
        set(0, 0, n, st, en, p);
    }
};

void solve() {
    int n; scanf("%d", &n);
    VI c(n); repn(i, n) scanf("%d", &c[i]);

    vector<VI> inds(100010);
    VI pre(n);
    repn(i, n) {
        pre[i]=(inds[c[i]].empty() ? -1 : inds[c[i]].back());
        if(i>0) setmax(pre[i], pre[i-1]);
        inds[c[i]].pb(i);
    }

    //cout<<pre<<endl;

    vector<bool> used(100010);
    Tree tr(n);
    int ans=0;
    repn(start, n) {
        //printf("initing \n");
        tr.init(pre);
        //printf("init ok\n");
        int j=start;
        while(j<n && !used[c[j]]) {
            used[c[j]]=true;
            for(int i: inds[c[j]]) {
        //printf("finding \n");
                int k=tr.find(i);
                //printf("eliminate [%d,%d]\n", i,k);
                tr.set(i, k+1, i);
            }
            ++j;
            setmax(ans, tr.maxv()+j-start);
        }
        while(j>start) {
            --j; used[c[j]]=false;
        }
    }
    printf("%d\n", ans);
}

int main() {
    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
