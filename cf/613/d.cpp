#include <cassert>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
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

const int MAXN=100010;
const int MAXM=100010;

VI es[MAXN];
int ans[MAXM]; VI queries[MAXN];
int n, m, dep[MAXN];

void add(int i, int v) {
    if(ans[i]>=0) ans[i]+=v;
}

typedef map<int,int> Map;

Map* merge(Map* p, Map* q, map<int,set<int>>& box) {
    if(q->size()>p->size()) return merge(q, p, box);
    for(auto& kv: *q) {
        if(p->count(kv.fi)) {
            box[kv.fi].insert((*p)[kv.fi]);
            box[kv.fi].insert(kv.se);
            p->erase(kv.fi);
        } else if (box.count(kv.fi)) {
            box[kv.fi].insert(kv.se);
        } else {
            p->insert(kv);
        }
    }
    delete q;
    return p;
}

Map* dfs(int x, int fa) {
    dep[x]=dep[fa]+1;
    map<int,set<int>> box;
    Map* r=new Map;
    for(int y: es[x]) if(y!=fa) {
        Map* t=dfs(y, x);
        r=merge(r, t, box);
    }
    for(auto& is: box) {
        if(r->count(is.fi)) {
            is.se.insert((*r)[is.fi]);
            r->erase(is.fi);
        }
    }
    for(int i: queries[x]) {
        if(r->count(i)>0) {
            box[i].insert(r->find(i)->se);
            r->erase(i);
        }
        if(box.count(i)>0) {
            for(int y: box[i]) if(dep[y]==dep[x]+1) ans[i]=-1;
            add(i, (int)box[i].size());
            box.erase(i);
        }
        r->insert(mp(i, x));
    }
    for(auto& is: box) {
        add(is.fi, 1);
    }
    return r;
}

void read_data() {
    scanf("%d", &n); rep(i, 1, n) es[i].clear();
    rep(i, 1, n-1) { int x, y; scanf("%d%d",&x,&y); es[x].pb(y), es[y].pb(x); }
    scanf("%d", &m);
    rep(i, 1, n) queries[i].clear();
    rep(i, 1, m) {
        int k; scanf("%d", &k);
        while(k--) { int x; scanf("%d", &x); queries[x].pb(i); }
    }
}

void gen_data() {
    n=5; rep(i, 1, n) es[i].clear();
    rep(i, 2, n) { int j=rand()%(i-1)+1; es[i].pb(j), es[j].pb(i); }
    m=1;
    rep(i, 1, n) queries[i].clear();
    rep(i, 1, m) {
        rep(x, 1, n) if(rand()%3==0) queries[x].pb(i);
    }
}

void solve() {
    fillchar(ans, 0);
    dep[0]=0; dfs(1, 0);
}

void gg(int &v, int x) {
    v|=1<<(x-1);
    for(int y: es[x]) if((v&(1<<(y-1)))==0) gg(v, y);
}

int main() {
    read_data(); solve(); rep(i, 1, m) printf("%d\n", ans[i]); return 0;

    for(int cs=1; ; ++cs) {
        printf("Case #%d: ", cs);
        gen_data();
        solve();
        
        int mix=0;
        rep(q, 1, m) {
            int cur=1<<30;
            int want=0; rep(x, 1, n) if(count(all(queries[x]), q)>0) want|=(1<<(x-1));
            repn(st, 1<<n) if((st&want)==0) {
                int vis=st; bool ok=true;
                rep(x, 1, n) if(want&(1<<(x-1))) {
                    if(vis&(1<<(x-1))) { ok=false; break; }
                    gg(vis, x);
                }
                if(!ok) continue;
                setmin(cur, __builtin_popcount(st));
            }
            if(cur==1<<30) cur=-1;
            if(ans[q]==cur) mix+=cur;
            else {
                printf("error! ans=%d std=%d\n",ans[q],cur); 
                rep(x, 1, n) { printf("%d [%d]:", x,(int)queries[x].size()); for(int y: es[x]) printf(" %d", y); printf("\n"); }
                for(;;);
            }
            printf("ok.  %d\n",mix);
        }
    }
    return 0;
}