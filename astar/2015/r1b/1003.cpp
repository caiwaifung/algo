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

bool vis[555][555];
int n, m, g;

void init() {
    scanf("%d%d%d", &n,&m,&g);
    fillchar(vis, false);
    forint(i, 1, g) {
        int x, y; scanf("%d%d", &x,&y);
        vis[x][y]=true;
    }
}

int qx[555*555], qy[555*555], ss, tt;

void visit(int x, int y) {
    if(vis[x][y]) return;
    vis[x][y]=true;
    ++tt; qx[tt]=x, qy[tt]=y;
}

void solve(int cs) {
    ss=0, tt=0;
    forint(i, 1, n) forint(j, 1, m) if(vis[i][j]) {
        ++tt; qx[tt]=i, qy[tt]=j;
    }
    while(ss<tt) {
        int x=qx[++ss], y=qy[ss];
        for(int dx=-1; dx<=1; dx+=2) for(int dy=-1; dy<=1; dy+=2) {
            int x0=x+dx, y0=y+dy;
            if(x0<1 || x0>n || y0<1 || y0>m) continue;
            if(vis[x0][y0]) {
                visit(x, y0);
                visit(x0, y);
            }
        }
    }
    printf("Case #%d:\n", cs);
    printf("%d\n", tt);
}

int main() {
    int csn; scanf("%d", &csn);
    forint(cs, 1, csn) {
        init();
        solve(cs);
    }
    return 0;
}
