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

class IntervalTree {
    struct Node {
        pair<LL, int> minp;
        LL buf;
    };
    const int n_;
    vector<Node> tr_;

    void release(int x) {
        if(tr_[x].buf!=0) {
            tr_[x*2+1].minp.fi+=tr_[x].buf;
            tr_[x*2+1].buf+=tr_[x].buf;
            tr_[x*2+2].minp.fi+=tr_[x].buf;
            tr_[x*2+2].buf+=tr_[x].buf;
            tr_[x].buf=0;
        }
    }

    void update(int x) {
        tr_[x].minp=min(tr_[x*2+1].minp, tr_[x*2+2].minp);
    }

    void build(int x, int l, int r) {
        tr_[x].minp=mp(0, l);
        tr_[x].buf=0;
        if(l+1==r) return;
        int m=(l+r)/2;
        build(x*2+1, l, m);
        build(x*2+2, m, r);
    }
    pair<LL, int> minval(int x, int l, int r, int s, int t) {
        if(s<=l && r<=t) {
            return tr_[x].minp;
        }
        release(x);
        const int m=(l+r)/2;
        pair<LL, int> ans{1LL<<60, -1};
        if(s<m) setmin(ans, minval(x*2+1, l, m, s, t));
        if(m<t) setmin(ans, minval(x*2+2, m, r, s, t));
        return ans;
    }
    void add(int x, int l, int r, int s, int t, LL val) {
        if(s<=l && r<=t) {
            tr_[x].minp.fi+=val;
            tr_[x].buf+=val;
            return;
        }
        release(x);
        const int m=(l+r)/2;
        if(s<m) add(x*2+1, l, m, s, t, val);
        if(m<t) add(x*2+2, m, r, s, t, val);
        update(x);
    }
public:
    IntervalTree(int n) : n_(n), tr_(n*4) {
        build(0, 0, n_);
    }
    pair<LL, int> minval(int s, int t) {
        return minval(0, 0, n_, s, t);
    }
    void add(int s, int t, LL val) {
        add(0, 0, n_, s, t, val);
    }
};

int main() {
    int n, m; scanf("%d%d", &n,&m);
    IntervalTree ta(n), ts(n);
    LL sum=0;
    repn(i, n) {
        int x; scanf("%d", &x);
        sum+=x;
        ta.add(i, i+1, x);
        ts.add(i, i+1, sum);
    }
    vector<pair<LL, int>> queries(m);
    repn(i, m) {
        scanf("%lld", &queries[i].fi);
        queries[i].se=i;
    }
    sort(all(queries), greater<pair<LL, int>>());

    VI ans(m); int cur=0;
    for(const auto& p: queries) {
        //cout<<endl<<"query: "<<p<<endl;
        while(1) {
            const auto minp=ts.minval(0, n);
            //cout<<"minp: "<<minp<<endl;
            if(p.fi+minp.fi>=0) break;
            const auto z=ta.minval(0, minp.se+1);
            //cout<<"z: "<<z<<endl;
            ta.add(z.se, z.se+1, -z.fi);
            ts.add(z.se, n, -z.fi);
            ++cur;
        }
        ans[p.se]=cur;
    }
    repn(i, m) printf("%d\n", ans[i]);


    return 0;
}
