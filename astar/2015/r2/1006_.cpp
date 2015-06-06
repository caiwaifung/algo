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

#define _ (size_t)
#define all(a) a.begin(), a.end()
#define forint(i, a, b) for(int i=int(a); i<=int(b); ++i)
#define forintdown(i, a, b) for(int i=int(a); i>=int(b); --i)
#define forn(i, n) forint(i, 0, (n)-1)
#define forndown(i, n) forintdown(i, (n)-1, 0)
#define fillchar(a, x) memset(a, x, sizeof(a))
#define fi first
#define se second
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;
typedef vector<LL> VL;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<string> VS;
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }

const int MAXN=52;
const int MAXE=MAXN*MAXN;

int g[MAXN][MAXN][2];
int n, m, need;
map<string,int> id_hash;

int get_id(string s) {
    if(id_hash.find(s)==id_hash.end())
        id_hash[s]=++n;
    return id_hash[s];
}

void init() {
    scanf("%d%d%d", &n,&m,&need);
    n=0; id_hash.clear();
    fillchar(g, 0);
    forint(i, 1, m) {
        char bx[99], by[99];
        scanf("%s%s", bx,by);
        int x=get_id(string(bx));
        int y=get_id(string(by));
        g[x][y][0]=1;
    }
}

int deg[MAXN];
int limit, tot;

bool upt(int &x, int y) {
    if(y>x) { x=y; return true; }
    return false;
}

void walk(int x, int y) {
    int k=0;
    if(g[x][y][k]==0) ++k;
    assert(g[x][y][k]>0);
    ++deg[y], --deg[x];
    tot+=(k==0?1:-1);
    g[x][y][k]--, g[x][y][k^1]++;
}

int dis[MAXN], pre[MAXN];
int que[MAXN], ss, tt;
VPI es[MAXN];

int spfa() {
}

bool go_cycle() {
    static int ex[MAXE], ey[MAXE], ec[MAXE];
    int len=0;
    forint(i, 1, n) forint(j, 1, n)
        forn(k, 2) if(g[i][j][k]>0) {
            ++len;
            ex[len]=i, ey[len]=j, ec[len]=(k==0?1:-1);
        }
    forint(i, 1, len) {
        int j=rand()%i+1;
        swap(ex[i], ex[j]);
        swap(ey[i], ey[j]);
        swap(ec[i], ec[j]);
    }
    
    static int d[MAXN]; fillchar(d, 0);
    bool found=false;
    forn(_, n) {
        found=false;
        forint(k, 1, len) {
            int x=ex[k], y=ey[k], c=ec[k];
            if(upt(d[y], d[x]+c)) found=true;
        }
        if(!found) break;
    }
    if(!found) return false;

    static int pre[MAXN]; fillchar(pre, 0);
    forn(_, n) {
        forint(k, 1, len) {
            int x=ex[k], y=ey[k], c=ec[k];
            if(upt(d[y], d[x]+c)) pre[y]=x;
        }
    }

//printf("found circle:\n");
//forint(i, 1, n) printf("  pre[%d]=%d d=%d\n",i,pre[i],d[i]);
    int tot0=tot;

    static bool vis[MAXN]; fillchar(vis, false);
    int ti=0;
    forint(z, 1, n) if(pre[z]>0) {
        int x=z;
        forn(_, n) x=pre[x];
        if(vis[x]) continue;
        int x0=x, y=pre[x];
        ++ti;
        while(1) {
            vis[x]=true;
            walk(y, x);
            if(y==x0) break;
            x=y, y=pre[y];
        }
    }
    //printf("ti=%d\n",ti);


    assert(tot>tot0);

    return true;
}

bool go_path() {
    static int ex[MAXE], ey[MAXE], ec[MAXE];
    int len=0;
    forint(i, 1, n) forint(j, 1, n)
        forn(k, 2) if(g[i][j][k]>0) {
            ++len;
            ex[len]=i, ey[len]=j, ec[len]=(k==0?1:-1);
        }
    
    static int d[MAXN], pre[MAXN]; 
    forint(x, 1, n) {
        if(deg[x]-1>=-limit)
            d[x]=0;
        else
            d[x]=-(1<<30);
    }
    fillchar(pre, 0);
    forn(_, n) {
        bool found=false;
        forint(k, 1, len) {
            int x=ex[k], y=ey[k], c=ec[k];
            if(upt(d[y], d[x]+c)) pre[y]=x, found=true;
        }
        if(!found) break;
    }

    forint(x, 1, n)
        if(deg[x]+1<=limit && d[x]>0) {
//printf("found path:\n");
            int y=pre[x];
            while(y!=0) {
        //printf("  %d->%d\n",y,x);
                walk(y, x);
                x=y, y=pre[y];
            }
            return true;
        }
    return false;
}

void go() {
//printf("go lim=%d\n", limit);
    bool good=true;
    while(good) {
        good=false;


        while(1) {
            if(go_path()) {
                good=true;
            }
            else
                break;
        }
    }
}

void solve(int cs) {


    fillchar(deg, 0);
    limit=0; tot=0;

            while(go_cycle());

            //*
    while(true) {
        go();
        if(tot>=need)
            break;
        ++limit;
    }
    //*/
    printf("Case #%d:\n", cs);
    printf("%d\n", limit);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
