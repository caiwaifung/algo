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

vector<string> a, b, c;
vector<int> va, vb, vc;
map<string, int> ma, mb, mc;

void init(vector<string> &s, vector<int> &v, map<string,int> &m) {
    int n; scanf("%d", &n);
    repn(i, n) {
        char buf[99]; scanf("%s", buf);
        int x; scanf("%d", &x);
        string cur(buf);
        m[cur]=i;
        s.pb(cur);
        v.pb(x);
    }
}

VPI pairs[3000010];

void preprocess() {
    repn(i, a.size()) {
        fprintf(stderr,"pre %d/%d\n",i,(int)a.size());
        repn(j, b.size()) {
            pairs[va[i]+vb[j]].pb(mp(i, j));
        }
    }
}

void go(int val, int ind) {
    repn(i, c.size()) {
        int v=val-vc[i]; if(v<0) continue;
        int size=(int)pairs[v].size();
        if(ind<size) {
            int x=pairs[v][ind].fi, y=pairs[v][ind].se, z=i;
            //cout<<va[x]+vb[y]+vc[z]<<endl;
            printf("%s %s %s\n", a[x].c_str(), b[y].c_str(), c[z].c_str());
            return;
        }
        ind-=size;
    }
    assert(false);
}

void solve() {
    static int ind[3000010];
    fillchar(ind, 0);
    int q; scanf("%d", &q);
    repn(i, q) {
        fprintf(stderr,"%d/%d\n",i,q);
        char ba[99], bb[99], bc[99];
        scanf("%s%s%s",ba,bb,bc);
        string sa(ba), sb(bb), sc(bc);
        int val=va[ma[sa]]+vb[mb[sb]]+vc[mc[sc]];
        go(val+1, ind[val+1]);
        ++ind[val+1];
    }
}

int main() {
    freopen("b2.out", "w", stdout);
    init(a, va, ma);
    init(b, vb, mb);
    init(c, vc, mc);
    preprocess();
    solve();
    return 0;
}
