// 22:34 - 22:20
// 23:51 - pass sample - pass small
// time improvement - 24:04 - ac
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


// ------------------------ template ends here ------------------------ //

const int MAXN=4010;
const int MAXK=MAXN*3;
const int EMPTY=2147483647;

int g[MAXN], g_src[MAXK], g_lnk[MAXK], g_nxt[MAXK];
int p0[MAXN];
int c[MAXN];
int n, k;

int f[MAXK][MAXK], h[MAXK][MAXN];
int longest[MAXN][4], longest_y[MAXN][4];
int toward[MAXN][MAXN], toward_e[MAXN][MAXN];
int sum_c[MAXN][MAXN];
bool longest_lab[MAXN];

void pre() {
    forint(i, 1, k) forint(j, 1, k) f[i][j]=EMPTY;
    forint(i, 1, k) forint(j, 1, n) h[i][j]=EMPTY;
    fillchar(longest_lab, true);

    static int d[MAXN], prev[MAXN], q[MAXN];
    forint(x, 1, n) {
        fillchar(d, 0xff);
        int ss=0, tt=0;
        d[x]=0, q[++tt]=x;
        while(ss<tt) {
            int i=q[++ss];
            for(int e=g[i]; e; e=g_nxt[e]) {
                int j=g_lnk[e];
                if(d[j]<0) {
                    prev[j]=i; d[j]=d[i]+c[j];
                    q[++tt]=j;
                }
            }
        }
        forint(y, 1, n) sum_c[x][y]=d[y];
        //if(x==7) { forint(i, 1, tt) printf("q[%d]=%d d=%d prev=%d\n",i,q[i],d[q[i]],prev[q[i]]); }
        forintdown(i, tt, 2) {
            setmax(d[prev[q[i]]],d[q[i]]);
        }
        //if(x==7) { forint(i, 1, tt) printf("q[%d]=%d d=%d\n",i,q[i],d[q[i]]); }
        fillchar(longest[x], 0);
        fillchar(longest_y[x], 0);
        for(int e=g[x]; e; e=g_nxt[e]) {
            int y=g_lnk[e];
            toward[x][y]=y; toward_e[x][y]=e;
            if(d[y]>longest[x][3]) {
                longest[x][3]=d[y];
                longest_y[x][3]=y;
                int i=3;
                while(i>0 && longest[x][i]>longest[x][i-1]) {
                    swap(longest[x][i], longest[x][i-1]);
                    swap(longest_y[x][i], longest_y[x][i-1]);
                    --i;
                }
            }
        }

        toward[x][x]=toward_e[x][x]=0;
        forint(i, 1, tt) {
            int y=q[i];
            if(y==x || prev[y]==x) continue;
            toward[x][y]=toward[x][prev[y]];
            toward_e[x][y]=toward_e[x][prev[y]];
        }
    }

    //forint(x, 1, n) forint(y, 1, n) printf("toward[%d][%d]=%d | %d\n",x,y,toward[x][y],toward_e[x][y]);
    //forint(x, 1, n) forint(y, 1, n) printf("sum[%d][%d]=%d\n",x,y,sum_c[x][y]);
    //forint(x, 7, n) {
        //forn(i, 4) printf("longest[%d][%d]=%d, y=%d\n", x,i,longest[x][i],longest_y[x][i]);
    //}
}

PII get_longest(int x) { return MP(longest[x][0], longest_y[x][0]); }
PII get_longest(int x, int e1) { 
    longest_lab[e1]=false; longest_lab[0]=true;
    int j=0; while(!longest_lab[longest_y[x][j]]) ++j;
    longest_lab[e1]=true;
    return MP(longest[x][j], longest_y[x][j]);
}
PII get_longest(int x, int e1, int e2) {
    longest_lab[e1]=longest_lab[e2]=false; longest_lab[0]=true;
    int j=0; while(!longest_lab[longest_y[x][j]]) ++j;
    longest_lab[e1]=longest_lab[e2]=true;
    return MP(longest[x][j], longest_y[x][j]);
}
PII get_longest(int x, int e1, int e2, int e3) {
    longest_lab[e1]=longest_lab[e2]=longest_lab[e3]=false; longest_lab[0]=true;
    int j=0; while(!longest_lab[longest_y[x][j]]) ++j;
    longest_lab[e1]=longest_lab[e2]=longest_lab[e3]=true;
    return MP(longest[x][j], longest_y[x][j]);
}

int cal_h(int p, int y) {
    int &ans=h[p][y];
    if(ans!=EMPTY) return ans;
    int x=g_lnk[p], x0=g_src[p];
    assert(x!=y);

    ans=-(1<<30);

    int x2=toward[x][y], x2e=toward_e[x][y];
    if(x2!=y) setmax(ans, cal_h(x2e, y)+c[x2]);

    PII z=get_longest(x, x0, x2);
    setmax(ans, z.fi);
    
    return ans;
}

int cal_f(int p, int q) {
    int &ans=f[p][q];
    if(ans!=EMPTY) return ans;

    int x=g_lnk[p], x0=g_src[p];
    int y=g_lnk[q], y0=g_src[q];
    if(x==y) {
        PII zx=get_longest(x, x0, y0);
        PII zy=get_longest(x, x0, y0, zx.se);
        //if(x==y && x==7 && x0==0 && y0==8) {
            //printf("x=%d x0=%d y0=%d zx.se=%d\n",x,x0,y0,zx.se);
            //printf("zx: %d %d\n",zx.fi,zx.se);
            //printf("zy: %d %d\n",zy.fi,zy.se);
        //}
        return ans=zx.fi-zy.fi;
    }

    // option 1: walk toward y
    int x2=toward[x][y], x2e=toward_e[x][y];
    ans=(x2!=y?c[x2]:0) - cal_f(q, x2e);

    // option 2: walk away
    PII z1=get_longest(x, x0, x2); int x3=z1.se;
    int tmp=z1.fi;
    int tmp1=sum_c[y][x]-c[x]+get_longest(x, x0, x2, x3).fi;
    int tmp2=cal_h(q, x);
    setmax(ans, tmp-max(tmp1, tmp2));

    return ans;
}

void solve() {
    scanf("%d", &n);
    forint(i, 1, n) scanf("%d", &c[i]);

    fillchar(g, 0);
    k=0;
    forint(i, 1, n-1) {
        int j; scanf("%d", &j);
        ++k; g_src[k]=i, g_lnk[k]=j, g_nxt[k]=g[i], g[i]=k;
        ++k; g_src[k]=j, g_lnk[k]=i, g_nxt[k]=g[j], g[j]=k;
    }
    forint(i, 1, n) {
        p0[i]=++k;
        g_src[k]=0, g_lnk[k]=i;
    }

    pre();
    int ans=-(1<<30);
    forint(i, 1, n) {
        if (i%100==0) fprintf(stderr, "   i=%d/%d\n",i,n), fflush(stderr);
        int tmp=(1<<30);
        forint(j, 1, n) {
            int z=cal_f(p0[i], p0[j]);
            z+=c[i]; if(i!=j) z-=c[j];
            setmin(tmp, z);
            //printf("f[%d,%d]=%d\n", i,j,z);
        }
        setmax(ans, tmp);
    }
    printf("%d\n", ans);
}

int main() {
    freopen("a.txt", "w", stdout);
    int cases;
    scanf("%d", &cases);
    forint(cs, 1, cases) {
        fprintf(stderr, "cs=%d/%d\n", cs, cases); fflush(stderr);
        printf("Case #%d: ", cs);
        solve();
        //if(cs==2) break;
        //return 0;
    }
    return 0;
}
