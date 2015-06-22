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

const int MAXN=1000010;
const int MAXNum=1010;
const int bsize=1000;

int lc[MAXN], rc[MAXN];
int n;

int lx[MAXN], ld[MAXN], st[MAXN], en[MAXN], tot;

void dfs(int x, int d) {
    lx[tot]=x, ld[tot]=d, st[x]=tot++;
    for(int y=lc[x]; y; y=rc[y])
        dfs(y, d+1);
    en[x]=tot;
}

struct Block {
    int c[bsize], d[bsize];
    PII p[bsize];
    int buf[bsize], buftime[bsize]; // at buftime[i] time, color [0,i] with buf[i]
    int n, curtime;

    void release() {
        int bestc=0, bestt=0;
        irepn(i, n) {
            if(setmax(bestt, buftime[i]))
                bestc=buf[i];
            buf[i]=buftime[i]=0;
            if(bestt>0)
                c[p[i].se]=bestc;
        }
    }

    void init(int *deps, int len) {
        n=len;
        repn(i, n) d[i]=deps[i], c[i]=1;
        repn(i, n) p[i]=mp(d[i], i);
        sort(p, p+n);
        curtime=0;
        fillchar(buf, 0);
        fillchar(buftime, 0);
    }

    // paint i in [l,r) if dep[i]<=dlimit
    void paint(int l, int r, int dlimit, int color) {
        if(l==0 && r==n) {
            int i=int(lower_bound(p, p+n, mp(dlimit+1,0))-p)-1;
            if(i>=0) {
                buftime[i]=++curtime;
                buf[i]=color;
            }
            return;
        }
        release();
        rep(i, l, r-1) if(d[i]<=dlimit) c[i]=color;
    }

    int get(int i) {
        release();
        return c[i];
    }
};
Block blocks[MAXNum];
int num;

void init() {
    tot=0; dfs(1, 1);
    assert(tot==n);

    num=(n-1)/bsize+1;
    repn(i, num) {
        int l=bsize*i, r=min(l+bsize, n);
        blocks[i].init(ld+l, r-l);
    }
}

int get_color(int x) {
    int p=st[x];
    int c=blocks[p/bsize].get(p%bsize);
    return c;
}

void set_color(int x, int d, int c) {
    int l=st[x], r=en[x], dlimit=ld[l]+d;
    repn(i, num) {
        int l0=max(l, 0), r0=min(r, bsize);
        if(l0<r0)
            blocks[i].paint(l0, r0, dlimit, c);
        l-=bsize, r-=bsize;
    }
}

int main() {
    freopen("g2.out", "w", stdout);
    int csn; scanf("%d", &csn);
    repn(cs, csn) {
        int q; scanf("%d%*d%d", &n,&q);

        fillchar(lc, 0);
        rep(i, 2, n) {
            int j; scanf("%d", &j);
            rc[i]=lc[j], lc[j]=i;
        }
        init();

        LL ans=0;
        rep(i, 1, q) {
            if(i%100000==0) fprintf(stderr,"cs=%d/%d i=%d/%d\n",cs+1,csn,i,q);
            int x, d, z; scanf("%d%d%d",&x,&d,&z);
            if(z==0) {
                ans=(ans+LL(get_color(x))*LL(i))%LL(1e9+7);
            }
            else {
                set_color(x, d, z);
            }
        }
        printf("%d\n", (int)ans);
    }
    return 0;
}
