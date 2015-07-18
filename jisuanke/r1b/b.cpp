#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <set>
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

const int MAXN=200020;

VI es[MAXN]; LL val[MAXN];
int le[MAXN], ri[MAXN], who[MAXN], tot;
int np[MAXN];
int n;

void dfs(int x, int fa) {
    le[x]=++tot; who[tot]=x;
    for(int y: es[x]) if(y!=fa)
        dfs(y, x);
    ri[x]=tot;
}

int get_np(int x) {
    VI vec;
    while(np[x]!=0) {
        vec.pb(x); x=np[x];
    }
    for(int y: vec) np[y]=x;
    return x;
}

bool chosen[MAXN];
int num[MAXN];
void choose(int x) {
    chosen[x]=true; np[le[x]]=le[x]+1;
}

bool go(int x, int fa) {
    LL pairs=0;
    num[x]=0;
    multiset<PII> options;
    options.insert(mp(0, -1));
    for(int y: es[x]) if(y!=fa) {
        if(!go(y, x)) return false;
        pairs+=LL(num[y])*LL(num[x]);
        num[x]+=num[y];
        options.insert(mp(num[y], y));
    }
    while(pairs<val[x]) {
        if(options.empty()) return false;
        PII o=*options.begin();
        options.erase(options.begin());
        int y=o.se, yv=o.fi;
        if(y==-1) {
            pairs+=num[x];
            choose(x);
        } else {
            int k=get_np(le[y]);
            if(k>ri[y]) continue;
            choose(who[k]);
            pairs+=num[x]-yv;
            options.insert(mp(yv+1, y));
        }
        ++num[x];
    }
    return true;
}

int main() {
    scanf("%d", &n);
    rep(i, 1, n) cin>>val[i];
    rep(i, 1, n) es[i].clear();
    rep(i, 1, n-1) {
        int x, y; scanf("%d%d", &x,&y);
        es[x].pb(y), es[y].pb(x);
    }

    tot=0; dfs(1, 0);
    fillchar(np, 0);
    fillchar(chosen, false);

    if(!go(1, 0)) printf("-1\n");
    else {
        int cnt=0;
        rep(i, 1, n) if(chosen[i]) ++cnt;
        assert(cnt==num[1]);
        printf("%d\n", cnt);
        if(cnt>0) {
            bool fi=false;
            rep(i, 1, n) if(chosen[i]) {
                if(fi) printf(" "); printf("%d", i); 
                fi=true;
            }
            printf("\n");
        }
    }

    return 0;
}
