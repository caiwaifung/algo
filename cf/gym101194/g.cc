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
#include <unordered_map>
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

struct Node {
    int epoch=0;
    Node* up[20]={nullptr};
    int ans=0;
};

struct Set {
    unordered_map<int, int> m;
    PII ans;

    Set(int init) {
        ans=mp(-1, init);
        m[init]=1;
    }
    void insert(const Set& s) {
        for(const auto& kv: s.m) {
            int v=(m[kv.fi]+=kv.se);
            setmin(ans, mp(-v, kv.fi));
        }
    }
    int size() const { return sz(m); }
    int best() const { return ans.se; }
};

vector<Node*> build(int n, VI c, vector<pair<int, PII>> es) {
    vector<Node*> start(n), cur(n), all_nodes;
    repn(i, n) {
        start[i]=cur[i]=new Node();
        cur[i]->ans=c[i];
        all_nodes.pb(cur[i]);
    }
    vector<int> f(n, -1);
    const function<int(int)> get=[&](int x) {
        return f[x]<0 ? x : f[x]=get(f[x]);
    };
    vector<Set*> sets(n);
    repn(i, n) sets[i]=new Set(c[i]);

    sort(all(es));
    for(const auto& e: es) {
        const int epoch=e.fi;
        int a=e.se.fi, b=e.se.se;
        a=get(a), b=get(b);
        if(a==b) continue;

        if(sets[a]->size()<sets[b]->size()) {
            swap(a, b);
        }
        sets[a]->insert(*sets[b]);
        delete sets[b];
        f[b]=a;

        Node* p=new Node();
        p->epoch=epoch;
        p->ans=sets[a]->best();
        all_nodes.pb(p);
        cur[a]->up[0]=cur[b]->up[0]=p;
        cur[a]=p, cur[b]=nullptr;
    }

    reverse(all(all_nodes));
    for(Node* p: all_nodes) {
        for(int i=0; p->up[i]; ++i) {
            p->up[i+1]=p->up[i]->up[i];
        }
    }
    return start;
}

void solve() {
    int n, m; scanf("%d%d", &n,&m);
    VI c(n);
    repn(i, n) scanf("%d", &c[i]);
    vector<pair<int, PII>> es(m);
    repn(i, m) {
        scanf("%d%d%d", &es[i].se.fi, &es[i].se.se, &es[i].fi);
        --es[i].se.fi, --es[i].se.se;
    }
    vector<Node*> ns=build(n, c, es);

    int q; scanf("%d", &q);
    int ans=0;
    repn(i, q) {
        int x, w; scanf("%d%d", &x,&w);
        x^=ans, w^=ans;
        --x;
        Node* p=ns[x];
        irepn(k, 20) {
            if(p->up[k] && p->up[k]->epoch<=w) {
                p=p->up[k];
            }
        }
        ans=p->ans;
        printf("%d\n", ans);
    }
}

int main() {
    int cs; scanf("%d", &cs);
    rep(i, 1, cs) {
        printf("Case #%d:\n", i);
        solve();
    }
    return 0;
}
