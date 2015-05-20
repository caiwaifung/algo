/*
 * 22:38 - 22:50 - tle
 */
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

int g[2040], g_nxt[4040], g_cst[4040], g_lnk[4040];
LL f[2020][55], ans;
int n, k;

void dfs(int x, int fa) {
    fillchar(f[x], 50);
    setmin(f[x][1], 0LL);
    for(int e=g[x]; e; e=g_nxt[e]) {
        int y=g_lnk[e]; if(y==fa) continue;
        dfs(y, x);

        forint(j, 1, k) f[y][j]+=LL(g_cst[e])*LL(j)*LL(k-j);
        forintdown(i, k, 1) {
            LL tmp=f[x][i]; int _=k-i;
            forint(j, 1, _) setmin(f[x][i+j], tmp+f[y][j]);
        }
    }
    setmin(ans, f[x][k]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n,&k);
        int e=0; fillchar(g, 0);
        forint(i, 1, n-1) {
            int a,b,c; scanf("%d%d%d",&a,&b,&c);
            g_lnk[++e]=b, g_cst[e]=c, g_nxt[e]=g[a], g[a]=e;
            g_lnk[++e]=a, g_cst[e]=c, g_nxt[e]=g[b], g[b]=e;
        }
        ans=1LL<<60;
        dfs(1, 0);
        ans*=2;
        cout<<ans<<endl;
    }
    return 0;
}
