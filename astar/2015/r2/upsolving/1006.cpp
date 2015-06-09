#include <algorithm>
#include <iostream>
#include <sstream>
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

void asse(bool b) {
    if(!b) {
    printf("asse fail\n"); //exit(1);
        asse(b);
    }
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
    //asse(g[x][y][k]>0);
    ++deg[y], --deg[x];
    tot+=(k==0?1:-1);
    g[x][y][k]--, g[x][y][k^1]++;
}

namespace SCC {
    int g[MAXN], g_lnk[MAXE], g_nxt[MAXE];
    int belong[MAXN], bn;
    bool head[MAXN];
    int e;
    void add(int a, int b) {
        ++e; g_lnk[e]=b, g_nxt[e]=g[a]; g[a]=e;
    }
    void init() {
        fillchar(g, 0);
        e=0;
    }

    int st[MAXN], top, low[MAXN], dfn[MAXN], cnt;
    void dfs(int x) {
        low[x]=dfn[x]=++cnt;
        st[++top]=x;
        belong[x]=-1;
        for(int e=g[x]; e; e=g_nxt[e]) {
            int y=g_lnk[e];
            if(belong[y]<0)
                setmin(low[x], dfn[y]);
            if(belong[y]==0) {
                dfs(y);
                setmin(low[x], low[y]);
            }
        }
        if(low[x]==dfn[x]) {
            head[x]=true;
            ++bn;
            do belong[st[top--]]=bn;
            while (st[top+1]!=x);
        }
    }
    void go() {
        fillchar(head, false);
        cnt=0; bn=0; top=0;
        fillchar(belong, 0);
        forint(i, 1, n) if(belong[i]==0)
            dfs(i);
    }
};

bool go_cycle() {
    static int ex[MAXE], ey[MAXE], ec[MAXE];
    int len=0;
    SCC::init();
    forint(i, 1, n) forint(j, 1, n)
        forn(k, 2) if(g[i][j][k]>0) {
            SCC::add(i, j);
            ++len;
            ex[len]=i, ey[len]=j, ec[len]=(k==0?1:-1);
            if(k==0) break;
        }
    SCC::go();

    static int d[MAXN][MAXN];
    static int pre[MAXN][MAXN];
    fillchar(d, 200);
    forint(i, 1, n) if(SCC::head[i])
        d[0][i]=0;
    forint(t, 0, n-1) {
        forint(k, 1, len) {
            int x=ex[k], y=ey[k], c=ec[k];
            if(SCC::belong[x]!=SCC::belong[y])
                continue;
            if(upt(d[t+1][y], d[t][x]+c))
                pre[t+1][y]=x;
                /*
            int &tar=d[t+1][y];
            int src=d[t][x]+c;
            if(tar<src || (tar==src && x<pre[t+1][y])) {
                tar=src;
                pre[t+1][y]=x;
            }
            */
        }
    }

    double maxv=0;
    int x0=0, k0=0;

    forint(i, 1, n) {
        double tmp=1e50;
        int ck=0;
        forint(k, 0, n-1) {
            double v=double(d[n][i]-d[k][i])/double(n-k);
            if(v<tmp) tmp=v, ck=k;
        }
        if(tmp>maxv) {
            maxv=tmp;
            x0=i; k0=ck;
        }
    }
    if(x0==0) return false;

    //printf("go circle: maxv=%.3lf x0=%d k0=%d\n",maxv,x0,k0);
    //printf(" d: %d %d\n",d[n][x0],d[k0][x0]);

    //int tot0=tot;
    static int path[MAXN];
    for(int k=n, x=x0; k>=0; ) {
        path[k]=x;
        x=pre[k][x], --k;
    }
    bool found=false;
    forint(i, 0, n) forint(j, i+1, n)
        if(path[i]==path[j]) {
            int s=0;
            forint(k, i+1, j)
                if(g[path[k-1]][path[k]][0]>0)
                    ++s;
                else --s;
            if(fabs(double(s)/double(j-i)-maxv)>1e-8)
                continue;

            int tot0=tot;
            forint(k, i+1, j)
                walk(path[k-1],path[k]);
            found=true;
            //asse(tot>tot0);
            double sum=(tot-tot0)/(double)(j-i);
        //forint(k, i, j) printf("%d ",path[k]); printf("\n");
        //forint(k, 0, n) printf("%d ",path[k]); printf("\n");
            //printf("%.4lf %.4lf\n",sum,maxv);
            asse(fabs(sum-maxv)<1e-8);
            return true;
        }
    /*
    if(!found) {
        forint(i, 0, n) printf("%d ",path[i]); printf("\n");
        exit(1);
    }
    */
    //asse(found);
    if(!found) return false;
    /*

    for(int k=n, x=x0, y=pre[k][x0];; ) {
        //asse(SCC::belong[x]==SCC::belong[y]);
        walk(y, x); //printf("%d %d\n",x,y);
        --k;
        x=y, y=pre[k][y];
        if(x==x0) {
        //printf("x=%d x0=%d\n", x,x0);
            //asse(x==x0);
            //asse(k==k0);
            break;
        }
    }
    */

    //asse(tot>tot0);

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

void solve(int cs) {
    fillchar(deg, 0);
    limit=0; tot=0;

    //*
    while(true) {
        while(1) {
            bool ok=false;
            while(go_cycle()) ok=true;
            while(go_path()) ok=true;
            if(!ok) break;
        }
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
