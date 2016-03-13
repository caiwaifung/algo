#include <cassert>
#include <queue>
#include <functional>
#include <set>
#include <map>
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

vector<int> a, belong;
int n, m, num;

void build_groups() {
    vector<VI> g(n*m);
    auto add=[&](int i1, int j1, int i2, int j2) {
        int x=i1*m+j1, y=i2*m+j2;
        g[x].pb(y), g[y].pb(x);
    };
    repn(i, n) {
        map<int, VI> p;
        repn(j, m) p[a[i*m+j]].pb(j);
        for(const auto& kv: p) {
            int h=kv.se[0];
            for(int j: kv.se) if(j!=h) add(i, h, i, j);
        }
    }
    repn(j, m) {
        map<int, VI> p;
        repn(i, n) p[a[i*m+j]].pb(i);
        for(const auto& kv: p) {
            int h=kv.se[0];
            for(int i: kv.se) if(i!=h) add(h, j, i, j);
        }
    }

    belong.resize(n*m); fill(all(belong), -1);
    num=0;
    function<void(int)> dfs=[&](int k) {
        if(belong[k]>=0) return;
        belong[k]=num;
        for(int y: g[k]) dfs(y);
    };
    repn(k, n*m) if(belong[k]<0) {
        dfs(k); ++num;
    }
}

void build_graph(vector<VI>& g) {
    g.resize(num); fill(all(g), VI());
    auto add=[&](int x, int y) {
        g[x].pb(y);
    };
    auto add_edges=[&](const set<PII>& s) {
        int o=-1;
        for(auto& p: s) {
            if(o>=0) add(o, p.se);
            o=p.se;
        }
    };
    repn(i, n) {
        set<PII> s;
        repn(j, m) s.insert(mp(a[i*m+j], belong[i*m+j]));
        add_edges(s);
    }
    repn(j, m) {
        set<PII> s;
        repn(i, n) s.insert(mp(a[i*m+j], belong[i*m+j]));
        add_edges(s);
    }
}

int main() {
    scanf("%d%d", &n,&m);
    a.resize(n*m); repn(k, n*m) scanf("%d", &a[k]);

    build_groups();

    vector<VI> g;
    build_graph(g);

    vector<int> ans(num);
    vector<int> cnt(num, 0);
    repn(i, num) for(int j: g[i]) ++cnt[j];
    vector<int> que;
    repn(i, num) if(cnt[i]==0) que.pb(i);
    for(int lab=1; !que.empty(); ++lab) {
        for(int i: que) ans[i]=lab;
        VI q;
        for(int i: que) for(int j: g[i]) if(--cnt[j]==0) q.pb(j);
        que=q;
    }
    repn(i, n) {
        repn(j, m) printf("%d ", ans[belong[i*m+j]]);
        printf("\n");
    }

    return 0;
}
