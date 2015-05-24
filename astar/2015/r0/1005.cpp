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
template<class T> void setmax(T &a, T b) { if(b>a) a=b; }
template<class T> void setmin(T &a, T b) { if(b<a) a=b; }
template<class T> T gcd(T a, T b) { return b==0?a:gcd(b,a%b); }


// ------------------------ template ends here ------------------------ //

const int MAXN=1010;

namespace mine {
bool vis[MAXN][MAXN];
int qx[MAXN*MAXN], qy[MAXN*MAXN], ss, tt;
int n, m, lim;
int x1, y1, x2, y2;
int ans;

int dis(int x, int y) {
    x-=x1; if(x<0) x=-x;
    y-=y1; if(y<0) y=-y;
    int ans=max(x, y);
    if(ans==0) ans=2;
    return ans;
}

void visit(int t, int x, int y) {
    if(vis[x][y]) return;
    vis[x][y]=true;
    qx[++tt]=x, qy[tt]=y;

    int t2=max(t, dis(x,y));
    if((t2&1)!=(t&1)) ++t2;
    setmin(ans, t2);
}

const int dx[8]={-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[8]={-1, 1, -2, 2, -2, 2, -1, 1};

void bfs(int t) {
    int tt0=tt;
    while(ss<tt0) {
        int x=qx[++ss], y=qy[ss];
        forn(k, 8) {
            int x0=x+dx[k], y0=y+dy[k];
            if(x0<1 || x0>n || y0<1 || y0>m) continue;
            visit(t,x0, y0);
        }
    }
}

int go() {
    int ncs; scanf("%d", &ncs);
    forint(cs, 1, ncs) {
        printf("Case #%d:\n", cs);
        scanf("%d%d%d", &n,&m,&lim);
        scanf("%d%d",&x1,&y1);
        scanf("%d%d",&x2,&y2);
        ss=0, tt=0; ans=lim+1;
        fillchar(vis, false);
        visit(0, x2, y2);
        forint(i, 1, lim) {
            bfs(i);
        }
        if(ans>lim) printf("OH,NO!\n");
            else printf("%d\n", ans);
    }
    return 0;
}
};


int main() {
    return mine::go();
}
